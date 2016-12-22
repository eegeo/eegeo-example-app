// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkConfigHandler.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"
#include "ICameraTransitionController.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ICoverageTreeManifestLoader.h"
#include "ApiTokenService.h"
#include "CityThemeLoader.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkConfigHandler::DeepLinkConfigHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                         Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                         Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                         ApplicationConfig::ApplicationConfiguration& defaultConfig,
                                                         Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifestLoader,
                                                         Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                                                         Search::SdkModel::InteriorMenuObserver& interiorMenuObserver,
                                                         AboutPage::View::IAboutPageViewModel& aboutPageViewModule,
                                                         Eegeo::Location::NavigationService& navigationService,
                                                         Eegeo::Web::ApiTokenService& apiTokenService)
            :m_webRequestFactory(webRequestFactory)
            ,m_configRequestCompleteCallback(this, &DeepLinkConfigHandler::HandleConfigResponse)
            ,m_failAlertHandler(this, &DeepLinkConfigHandler::OnFailAlertBoxDismissed)
            ,m_cameraTransitionController(cameraTransitionController)
            ,m_alertBoxFactory(alertBoxFactory)
            ,m_defaultConfig(defaultConfig)
            ,m_manifestLoader(manifestLoader)
            ,m_cityThemeLoader(cityThemeLoader)
            ,m_interiorMenuObserver(interiorMenuObserver)
            ,m_aboutPageViewModule(aboutPageViewModule)
            ,m_navigationService(navigationService)
            ,m_apiTokenService(apiTokenService)
            {
            }

            void DeepLinkConfigHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                const std::string url = GenerateConfigUrl(data);
                Eegeo::Web::IWebLoadRequest* webRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_configRequestCompleteCallback).Build();
                webRequest->Load();
            }

            std::string DeepLinkConfigHandler::GenerateConfigUrl(const AppInterface::UrlData& data) const
            {
                return CONFIG_FILES_HOME + data.path + "/manifest";
            }

            void DeepLinkConfigHandler::HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse)
            {
                if(webResponse.IsSucceeded())
                {
                    ApplicationConfig::SdkModel::ApplicationConfigurationJsonParser parser(m_defaultConfig);
                    size_t resultSize = webResponse.GetBodyData().size();
                    std::string resultString = std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);

                    if(parser.IsValidConfig(resultString))
                    {
                        ApplicationConfig::ApplicationConfiguration applicationConfig = parser.ParseConfiguration(resultString);
                        m_apiTokenService.ApiKeyChanged(applicationConfig.EegeoApiKey());
                        m_manifestLoader.LoadCoverageTreeManifest(applicationConfig.CoverageTreeManifestURL());

                        const std::string themeNameContains = "Summer";
                        const std::string themeStateName = "DayDefault";
                        m_cityThemeLoader.LoadThemes(applicationConfig.ThemeManifestURL(), themeNameContains, themeStateName);

                        const float newHeading = Eegeo::Math::Deg2Rad(applicationConfig.OrientationDegrees());
                        m_cameraTransitionController.StartTransitionTo(applicationConfig.InterestLocation().ToECEF(), applicationConfig.DistanceToInterestMetres(), newHeading);
                        m_interiorMenuObserver.UpdateDefaultOutdoorSearchMenuItems(applicationConfig.RawConfig());
                        m_aboutPageViewModule.UpdateApplicationName(applicationConfig.Name());
                        
                        const bool useGps = applicationConfig.TryStartAtGpsLocation();
                        if (useGps)
                        {
                            m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeFollow);
                        }
                        else
                        {
                            m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
                        }
                    }
                    else
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("User config file invalid", "Reverting to default config",m_failAlertHandler);
                    }
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("User config load failed", "Reverting to default config",m_failAlertHandler);
                }
            }

            void DeepLinkConfigHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}
