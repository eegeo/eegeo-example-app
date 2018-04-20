// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include "CameraTransitions.h"
#include "IAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkLocationHandler: public IDeepLinkHandler
            {
            public:
                DeepLinkLocationHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);
                void HandleDeepLink(const AppInterface::UrlData& data);
            private:
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<DeepLinkLocationHandler> m_failAlertHandler;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                void OnFailAlertBoxDismissed();
                constexpr static const char* URL_FORMAT_MESSAGE = "Please use deep link with format bway://location/lat/long[/distance/bearing/indoorid/floorindex]";
            };
        }
    }
}
