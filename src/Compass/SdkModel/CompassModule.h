// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassModule.h"
#include "Rendering.h"
#include "IIdentity.h"
#include "Location.h"
#include "CompassModeObserver.h"
#include "FixedIndoorLocationCompassModeObserver.h"
#include "CompassViewCycledObserver.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "AppModes.h"
#include "AlertBox.h"
#include "Interiors.h"
#include "AppCamera.h"
#include "InteriorsExplorer.h"
#include "CameraTransitionService.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassModule : public ICompassModule, private Eegeo::NonCopyable
            {
            private:
                View::CompassViewModel* m_pViewModel;
                ICompassModel* m_pModel;
                ICompassUpdateController* m_pCompassUpdateController;
                CompassModeObserver* m_pCompassModeObserver;
                CompassViewCycledObserver* m_pCompassViewCycledObserver;

            public:
                CompassModule(Eegeo::Location::NavigationService& navigationService,
                              Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                              Eegeo::Location::ILocationService& locationService,
                              ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                              Eegeo::Helpers::IIdentityProvider& identityProvider,
                              ExampleAppMessaging::TMessageBus& messageBus,
                              Metrics::IMetricsService& metricsService,
                              InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorExplorerModel,
                              AppModes::SdkModel::IAppModeModel& appModeModel,
                              Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                              Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                              CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService,
                              const Eegeo::Space::LatLong fixedLatlong,
                              const Eegeo::Resources::Interiors::InteriorId& fixedInteriorId,
                              const int fixedFloorIndex,
                              const double fixedHeadingRadians);

                ~CompassModule();

                ICompassModel& GetCompassModel() const;

                View::ICompassViewModel& GetCompassViewModel() const;

                ICompassUpdateController& GetCompassUpdateController() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
            };
        }
    }
}
