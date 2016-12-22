// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include "Web.h"
#include "CameraTransitions.h"
#include "ApplicationConfiguration.h"
#include "WebLoadRequestCompletionCallback.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "CoverageTrees.h"
#include "CityThemes.h"
#include "InteriorMenuObserver.h"
#include "AboutPageViewModel.h"
#include "IAlertBoxFactory.h"
#include "Location.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkConfigHandler: public IDeepLinkHandler, private Eegeo::NonCopyable
            {
            public:
                DeepLinkConfigHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                      Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                      Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                      ExampleApp::ApplicationConfig::ApplicationConfiguration& defaultConfig,
                                      Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& manifestLoader,
                                      Eegeo::Resources::CityThemes::CityThemeLoader& cityThemeLoader,
                                      Search::SdkModel::InteriorMenuObserver& interiorMenuObserver,
                                      AboutPage::View::IAboutPageViewModel& aboutPageViewModule,
                                      Eegeo::Location::NavigationService& navigationService,
                                      Eegeo::Web::ApiTokenService& apiTokenService);
                void HandleDeepLink(const AppInterface::UrlData& data);
            private:
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                ApplicationConfig::ApplicationConfiguration& m_defaultConfig;
                Eegeo::Web::TWebLoadRequestCompletionCallback<DeepLinkConfigHandler> m_configRequestCompleteCallback;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<DeepLinkConfigHandler> m_failAlertHandler;
                Eegeo::Streaming::CoverageTrees::ICoverageTreeManifestLoader& m_manifestLoader;
                Eegeo::Resources::CityThemes::CityThemeLoader& m_cityThemeLoader;
                Search::SdkModel::InteriorMenuObserver& m_interiorMenuObserver;
                AboutPage::View::IAboutPageViewModel& m_aboutPageViewModule;
                Eegeo::Location::NavigationService& m_navigationService;
                Eegeo::Web::ApiTokenService& m_apiTokenService;

                std::string GenerateConfigUrl(const AppInterface::UrlData& data) const;
                void HandleConfigResponse(Eegeo::Web::IWebResponse& webResponse);
                void OnFailAlertBoxDismissed();
            };
        
            const std::string CONFIG_FILES_HOME = "http://mapscene.eegeo.com";
        }
    }
}
