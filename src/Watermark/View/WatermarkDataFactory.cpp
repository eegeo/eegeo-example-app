// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkDataFactory.h"


namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkDataFactory::WatermarkDataFactory(const std::string& appName,
                                                       const std::string& googleAnalyticsReferrerToken)
            : m_appName(appName)
            , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
            {
                
            }
            
            WatermarkData WatermarkDataFactory::Create(const std::string& imageAssetUrl,
                                                       const std::string& popupTitle,
                                                       const std::string& popupBody,
                                                       const std::string& webUrl,
                                                       const bool shouldShowShadow)
            {
                return WatermarkData(imageAssetUrl,
                                     popupTitle,
                                     popupBody,
                                     webUrl,
                                     shouldShowShadow);
            }
                
            WatermarkData WatermarkDataFactory::CreateDefaultEegeo()
            {
                std::string imageAssetName = "eegeo_logo";
                std::string popupTitle = "Maps by eeGeo";
                std::string popupBody = "The " + m_appName + " app is open source. It's built using the eeGeo maps SDK, a cross platform API for building engaging, customizable apps.";
                std::string webUrl = "http://eegeo.com/?utm_source=" + m_googleAnalyticsReferrerToken + "&utm_medium=referral&utm_campaign=eegeo";
                
                return Create(imageAssetName,
                              popupTitle,
                              popupBody,
                              webUrl);
            }
        }
    }
}