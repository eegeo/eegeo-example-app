// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorsLocationServiceProvider.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            InteriorsLocationServiceProvider::InteriorsLocationServiceProvider(const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                                                               InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                               Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                               Eegeo::Location::ILocationService& defaultLocationService,
                                                                               Eegeo::Location::ILocationService& indoorAtlasLocationService,
                                                                               Eegeo::Location::ILocationService& senionLabLocationService)
            : m_applicationConfiguration(applicationConfiguration)
            , m_currentLocationService(currentLocationService)
            , m_defaultLocationService(defaultLocationService)
            , m_indoorAtlasLocationService(indoorAtlasLocationService)
            , m_senionLabLocationService(senionLabLocationService)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorExplorerEnteredCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerExit)
            , m_trackingInfoMap(m_applicationConfiguration.InteriorTrackingInfo())
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            InteriorsLocationServiceProvider::~InteriorsLocationServiceProvider()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerEntered()
            {
                Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = m_trackingInfoMap.find(interiorId.Value());
                if(it != m_trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo& trackingInfo = it->second;

                    if(trackingInfo.GetType() == "IndoorAtlas")
                    {
                        Eegeo_TTY("using IndoorAtlas location service");
                        m_currentLocationService.SetLocationService(m_indoorAtlasLocationService);
                    }
                    else if(trackingInfo.GetType() == "Senion")
                    {
                        Eegeo_TTY("using SenionLab location service");
                        m_currentLocationService.SetLocationService(m_senionLabLocationService);
                    }
                }
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerExit()
            {
                Eegeo_TTY("using default location service");
                m_currentLocationService.SetLocationService(m_defaultLocationService);
            }
        }
    }
}
