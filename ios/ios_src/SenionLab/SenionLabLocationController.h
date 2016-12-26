// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "SenionLabLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationController
        {
        public:
            SenionLabLocationController(SenionLabLocationManager& locationManager,
                                        ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                        const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                        Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
            ~SenionLabLocationController();
            
        private:
            SenionLabLocationManager& m_locationManager;
            
            ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            
            Eegeo::Helpers::TCallback0<SenionLabLocationController> m_appModeChangedCallback;
            
            void OnAppModeChanged();
            
            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
        };
    }
}