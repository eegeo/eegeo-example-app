// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "SenionLabLocationController.h"
#include "SenionLabLocationManager.h"
#include "SenionLabLocationService.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationModule
        {
        public:
            SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                    const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                    const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                    Eegeo::Location::ILocationService& defaultLocationService,
                                    Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                    ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
									AndroidNativeState& nativeState);
            ~SenionLabLocationModule();

            SenionLabLocationService& GetLocationService() { return *m_pLocationService; }
            
        private:
            SenionLabLocationController* m_pLocationController;
            SenionLabLocationService* m_pLocationService;
            View::SenionLabLocationManager* m_pLocationManager;
        };
    }
}
