// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <algorithm>

#include "WorldState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsCameraController.h"
#include "AttractState.h"
#include "AppCameraSplinePlaybackWrapper.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                namespace
                {
                    const float PLAYBACK_SPEED = 0.03f;
                }

                AttractState::AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                           AppCamera::SdkModel::IAppCameraController& cameraController,
                                           Eegeo::ITouchController& touchController,
                                           Eegeo::Input::IUserIdleService& userIdleService,
                                           Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                           const long long attractModeTimeout,
                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                           const Eegeo::Rendering::ScreenProperties& screenProperties)
                : m_appModeModel(appModeModel)
                , m_cameraController(cameraController)
                , m_userIdleService(userIdleService)
                , m_startTimeMs(Eegeo::Helpers::Time::MillisecondsSinceEpoch())
                , m_cameraSplinePlaybackController(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController(resourceCeilingProvider))
                , m_appCamera(m_cameraSplinePlaybackController, touchController)
                , m_cameraHandle(0)
                {
                    std::for_each(cameraPositionSplinePoints.begin(), cameraPositionSplinePoints.end(),
                                  [this](const Eegeo::Space::LatLongAltitude& p) { m_cameraPositionSpline.AddPoint(p.ToECEF()); });
                    std::for_each(cameraTargetSplinePoints.begin(), cameraTargetSplinePoints.end(),
                                  [this](const Eegeo::Space::LatLongAltitude& p) { m_cameraTargetSpline.AddPoint(p.ToECEF()); });

                    m_cameraSplinePlaybackController.SetSplines(&m_cameraPositionSpline, &m_cameraTargetSpline);
                    m_cameraSplinePlaybackController.SetPlaybackSpeed(PLAYBACK_SPEED);
                    m_cameraSplinePlaybackController.SetLooped(true);
                    m_cameraSplinePlaybackController.UpdateScreenProperties(screenProperties);
                    m_cameraHandle = m_cameraController.CreateCameraHandleFromController(m_appCamera);
                }

                AttractState::~AttractState()
                {
                    m_cameraController.RemoveCameraHandle(m_cameraHandle);
                }

                void AttractState::Enter(int previousState)
                {
                    m_startTimeMs = m_userIdleService.GetUserIdleTimeMs();
                    m_cameraSplinePlaybackController.Play();
                    m_cameraController.TransitionToCameraWithHandle(m_cameraHandle);
                }

                void AttractState::Update(float dt)
                {
                    if (m_userIdleService.GetUserIdleTimeMs() < m_startTimeMs)
                    {
                        m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
                    }
                    m_cameraSplinePlaybackController.Update(dt);
                }

                void AttractState::Exit(int nextState)
                {
                    m_cameraSplinePlaybackController.Stop();
                }
            }
        }
    }
}
