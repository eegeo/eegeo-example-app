// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "IAppModeModel.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "Tours.h"
#include "ICallback.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "AttractModeTimer.h"
#include "IUserIdleService.h"
#include "IVisualMapService.h"
#include "IMyPinCreationModel.h"
#include "InteriorsCameraController.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace AppModes
    {
        class GlobalAppModeTransitionRules : public Helpers::IStateMachineState 
        {
        private:
            AppCamera::SdkModel::IAppCameraController& m_cameraController;
            AppModes::SdkModel::IAppModeModel& m_appModeModel;
            AppCamera::SdkModel::AppGlobeCameraWrapper& m_worldCameraController;
            AppCamera::SdkModel::AppInteriorCameraWrapper& m_interiorCameraController;
            Eegeo::Helpers::TCallback0<GlobalAppModeTransitionRules> m_tourStartedCallback;
            Tours::SdkModel::ITourService& m_tourService;
            ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
            Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            Eegeo::Helpers::TCallback1<GlobalAppModeTransitionRules, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedCallback;
            const AttractModeTimer m_attractModeTimer;
            MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;
            VisualMap::SdkModel::IVisualMapService& m_visualMapService;
            const int m_worldCameraHandle;
            const int m_interiorCameraHandle;
            const int m_toursCameraHandle;
            SdkModel::AppMode m_currentState;

            void OnTourStarted();
            void OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
            void SetupCameraForNextMode(const SdkModel::AppMode currentState, const SdkModel::AppMode nextState);
            void SetupInteriorCamera();
            void SetupWorldCamera();
            
        public:
            GlobalAppModeTransitionRules(AppCamera::SdkModel::IAppCameraController& cameraController,
                                         Tours::SdkModel::ITourService& tourService,
                                         ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel,
                                         AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                         AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                         Tours::SdkModel::Camera::IToursCameraController& toursCameraController,
                                         Eegeo::Input::IUserIdleService& userIdleService,
                                         const bool attractModeEnabled,
                                         const long long attractModeTimeout,
                                         MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                         VisualMap::SdkModel::IVisualMapService& visualMapService);
            ~GlobalAppModeTransitionRules();

            void Enter(int previousState);
            void Update(float dt);
            void Exit(int nextState);

            const int GetWorldCameraHandle() const;
            const int GetInteriorsCameraHandle() const;
            const int GetToursCameraHandle() const;
        };
    }
}
