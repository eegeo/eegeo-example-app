// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraController.h"
#include "InteriorsCameraController.h"
#include "InteriorsExplorerModel.h"
#include "MathFunc.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationStage.h"
#include "IVisualMapService.h"
#include "VisualMapState.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                TourState::TourState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                     int tourCameraHandle,
                                     Tours::SdkModel::ITourService& tourService,
                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                     AppModes::SdkModel::IAppModeModel& appModeModel,
                                     VisualMap::SdkModel::IVisualMapService& visualMapService)
                : m_cameraController(cameraController)
                , m_tourCameraHandle(tourCameraHandle)
                , m_tourService(tourService)
                , m_tourStartedCallback(this, &TourState::OnTourEnded)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeModel(appModeModel)
                , m_visualMapService(visualMapService)
                {
                }
                
                TourState::~TourState()
                {
                }
                
                void TourState::Enter(int previousState)
                {
                    m_cameraController.TransitionToCameraWithHandle(m_tourCameraHandle);
                    m_tourService.RegisterTourEndedCallback(m_tourStartedCallback);
                    m_visualMapService.StoreCurrentMapState();
                }
                
                void TourState::Update(float dt)
                {
                }
                
                void TourState::Exit(int nextState)
                {
                    m_tourService.UnregisterTourEndedCallback(m_tourStartedCallback);
                    m_visualMapService.RestorePreviousMapState();
                }

                
                void TourState::OnTourEnded()
                {
                    const ExampleApp::AppModes::SdkModel::AppMode mode = m_interiorSelectionModel.IsInteriorSelected() ?
                                ExampleApp::AppModes::SdkModel::InteriorMode : ExampleApp::AppModes::SdkModel::WorldMode;
                    
                    m_appModeModel.SetAppMode(mode);
                }
                
            }
        }
    }
}
