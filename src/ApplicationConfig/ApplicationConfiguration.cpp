// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(
            const std::string& name,
            const std::string& eegeoApiKey,
            const std::string& productVersion,
            const std::string& buildNumber,
            const std::string& combinedVersionString,
            const std::string& coverageTreeManifestURL,
            const std::string& themeManifestURL,
            const std::string& embeddedThemeTexturePath,
            const Eegeo::Space::LatLongAltitude& interestLocation,
            float distanceToInterestMetres,
            float orientationDegrees,
            bool tryStartAtGpsLocation,
            bool startFullscreen,
            const std::string& googleAnalyticsReferrerToken,
            const std::string& flurryAppKey,
            const std::string& yelpConsumerKey,
            const std::string& yelpConsumerSecret,
            const std::string& yelpOAuthToken,
            const std::string& yelpOAuthTokenSecret,
            const std::string& geoNamesUserName,
            const std::string& eegeoSearchServiceUrl,
            const std::string& myPinsWebServiceUrl,
            const std::string& myPinsWebServiceAuthToken,
            const std::string& twitterAuthCode,
            const bool isKioskTouchInputEnabled,
            const bool isInKioskMode,
            const bool useLabels,
            const bool useJapaneseFont,
            const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo,
            const std::string& rawConfig,
            const Eegeo::Space::LatLong fixedLatlong,
            const std::string& fixedInteriorId,
            const int fixedFloorIndex,
            const double fixedHeadingDegrees,
            const std::vector<Eegeo::Space::LatLongAltitude>& attractModeTargetSplinePoints,
            const std::vector<Eegeo::Space::LatLongAltitude>& attractModePositionSplinePoints,
            const long long attractModeTimeoutMs
            )
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        , m_embeddedThemeTexturePath(embeddedThemeTexturePath)
        , m_interestLocation(interestLocation)
        , m_distanceToInterestMetres(distanceToInterestMetres)
        , m_orientationDegrees(orientationDegrees)
        , m_tryStartAtGpsLocation(tryStartAtGpsLocation)
        , m_shouldStartFullscreen(startFullscreen)
        , m_googleAnalyticsReferrerToken(googleAnalyticsReferrerToken)
        , m_flurryAppKey(flurryAppKey)
        , m_yelpConsumerKey(yelpConsumerKey)
        , m_yelpConsumerSecret(yelpConsumerSecret)
        , m_yelpOAuthToken(yelpOAuthToken)
        , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
        , m_geoNamesUserName(geoNamesUserName)
        , m_eegeoSearchServiceUrl(eegeoSearchServiceUrl)
        , m_myPinsWebServiceUrl(myPinsWebServiceUrl)
        , m_myPinsWebServiceAuthToken(myPinsWebServiceAuthToken)
        , m_twitterAuthCode(twitterAuthCode)
        , m_isKioskTouchInputEnabled(isKioskTouchInputEnabled)
        , m_isInKioskMode(isInKioskMode)
        , m_useLabels(useLabels)
        , m_useJapaneseFont(useJapaneseFont)
        , m_interiorTrackingInfo(interiorTrackingInfo)
        , m_rawConfig(rawConfig)
        , m_fixedInteriorId(Eegeo::Resources::Interiors::InteriorId(fixedInteriorId))
        , m_fixedLatlong(fixedLatlong)
        , m_fixedFloorIndex(fixedFloorIndex)
        , m_fixedHeadingDegrees(fixedHeadingDegrees)
        , m_attractModeTargetSplinePoints(attractModeTargetSplinePoints)
        , m_attractModePositionSplinePoints(attractModePositionSplinePoints)
        , m_attractModeTimeoutMs(attractModeTimeoutMs)
        {
        }
        
        std::string ApplicationConfiguration::Name() const
        {
            return m_name;
        }

        std::string ApplicationConfiguration::EegeoApiKey() const
        {
            return m_eegeoApiKey;
        }

        std::string ApplicationConfiguration::ProductVersion() const
        {
            return m_productVersion;
        }

        std::string ApplicationConfiguration::BuildNumber() const
        {
            return m_buildNumber;
        }

        std::string ApplicationConfiguration::CombinedVersionString() const
        {
            return m_combinedVersionString;
        }

        std::string ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }

        std::string ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }

        std::string ApplicationConfiguration::EmbeddedThemeTexturePath() const
        {
            return m_embeddedThemeTexturePath;
        }

        Eegeo::Space::LatLongAltitude ApplicationConfiguration::InterestLocation() const
        {
            return m_interestLocation;
        }
        
        float ApplicationConfiguration::DistanceToInterestMetres() const
        {
            return m_distanceToInterestMetres;
        }
        
        float ApplicationConfiguration::OrientationDegrees() const
        {
            return m_orientationDegrees;
        }
        
        bool ApplicationConfiguration::TryStartAtGpsLocation() const
        {
            return m_tryStartAtGpsLocation;
        }
        
        std::string ApplicationConfiguration::GoogleAnalyticsReferrerToken() const
        {
            return m_googleAnalyticsReferrerToken;
        }

        std::string ApplicationConfiguration::FlurryAppKey() const
        {
            return m_flurryAppKey;
        }

        std::string ApplicationConfiguration::YelpConsumerKey() const
        {
            return m_yelpConsumerKey;
        }

        std::string ApplicationConfiguration::YelpConsumerSecret() const
        {
            return m_yelpConsumerSecret;
        }

        std::string ApplicationConfiguration::YelpOAuthToken() const
        {
            return m_yelpOAuthToken;
        }

        std::string ApplicationConfiguration::YelpOAuthTokenSecret() const
        {
            return m_yelpOAuthTokenSecret;
        }

        std::string ApplicationConfiguration::GeoNamesUserName() const
        {
            return m_geoNamesUserName;
        }

        std::string ApplicationConfiguration::EegeoSearchServiceUrl() const
        {
            return m_eegeoSearchServiceUrl;
        }

        std::string ApplicationConfiguration::MyPinsWebServiceUrl() const
        {
            return m_myPinsWebServiceUrl;
        }

        std::string ApplicationConfiguration::MyPinsWebServiceAuthToken() const
        {
            return m_myPinsWebServiceAuthToken;
        }

        std::string ApplicationConfiguration::TwitterAuthCode() const
        {
            return m_twitterAuthCode;
        }

        bool ApplicationConfiguration::IsKioskTouchInputEnabled() const
        {
            return m_isKioskTouchInputEnabled;
        }

        bool ApplicationConfiguration::IsInKioskMode() const
        {
            return m_isInKioskMode;
        }

        bool ApplicationConfiguration::ShouldStartFullscreen() const
        {
            return m_shouldStartFullscreen;
        }
        
        bool ApplicationConfiguration::UseLabels() const
        {
            return m_useLabels;
        }
        
        bool ApplicationConfiguration::UseJapaneseFont() const
        {
            return m_useJapaneseFont;
        }
        
        const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& ApplicationConfiguration::InteriorTrackingInfo() const
        {
            return m_interiorTrackingInfo;
        }
        
        std::string ApplicationConfiguration::RawConfig() const
        {
            return m_rawConfig;
        }

        bool ApplicationConfiguration::FixedIndoorLocation(Eegeo::Space::LatLong& latlong, Eegeo::Resources::Interiors::InteriorId& interiorId, int& floorIndex, double& headingDegrees) const
        {
            if (!m_fixedInteriorId.IsValid())
            {
                return false;
            }

            latlong = m_fixedLatlong;
            interiorId = m_fixedInteriorId;
            floorIndex = m_fixedFloorIndex;
            headingDegrees = m_fixedHeadingDegrees;

            return true;
        }

        const std::vector<Eegeo::Space::LatLongAltitude>& ApplicationConfiguration::GetAttractModeTargetSplinePoints() const
        {
            return m_attractModeTargetSplinePoints;
        }

        const std::vector<Eegeo::Space::LatLongAltitude>& ApplicationConfiguration::GetAttractModePositionSplinePoints() const
        {
            return m_attractModePositionSplinePoints;
        }

        const long long ApplicationConfiguration::GetAttractModeTimeoutMs() const
        {
            return m_attractModeTimeoutMs;
        }

        const bool ApplicationConfiguration::IsAttractModeEnabled() const
        {
            return m_attractModeTimeoutMs > 0 &&
                   m_attractModeTargetSplinePoints.size() > 0 &&
                   m_attractModePositionSplinePoints.size() >= 2;
        }
    }
}
