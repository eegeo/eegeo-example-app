// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeStatesFactory.h"
#include "IStateMachineState.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "Tours.h"
#include "EegeoUI.h"
#include "MyPinCreation.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"
#include "ScreenProperties.h"
#include "GlobalAppModeTransitionRules.h"

#include "VisualMap.h"

#include <vector>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                class AppModeStatesFactory : public AppModes::SdkModel::IAppModeStatesFactory
                {
                private:
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    AppCamera::SdkModel::AppGlobeCameraWrapper& m_worldCameraController;
                    AppCamera::SdkModel::AppInteriorCameraWrapper& m_interiorCameraController;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdate;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                    Tours::SdkModel::ITourService& m_tourService;
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    VisualMap::SdkModel::IVisualMapService& m_visualMapService;

                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    Eegeo::Streaming::ResourceCeilingProvider& m_resourceCeilingProvider;
                    const std::vector<Eegeo::Space::LatLongAltitude>& m_cameraPositionSplinePoints;
                    const std::vector<Eegeo::Space::LatLongAltitude>& m_cameraTargetSplinePoints;
                    const bool m_attractModeEnabled;
                    const long long m_attractModeTimeoutMs;
                    const Eegeo::Rendering::ScreenProperties& m_screenProperties;
                    
                public:
                    
                    AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                         AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                         AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel,
                                         Tours::SdkModel::ITourService& tourService,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                         Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                         VisualMap::SdkModel::IVisualMapService& visualMapService,
                                         Eegeo::Input::IUserIdleService& userIdleService,
                                         Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                         const bool attractModeEnabled,
                                         const long long attractModeTimeout,
                                         const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                         const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                         const Eegeo::Rendering::ScreenProperties& screenProperties);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates(GlobalAppModeTransitionRules& globalAppModeTransitionRules);
                };
            }
        }
    }
}
