// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "document.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration
        {
            std::string m_name;
            std::string m_eegeoApiKey;
            std::string m_productVersion;
            std::string m_buildNumber;
            std::string m_combinedVersionString;
            std::string m_coverageTreeManifestURL;
            std::string m_themeManifestURL;
            std::string m_embeddedThemeTexturePath;

            Eegeo::Space::LatLongAltitude m_interestLocation;
            float m_distanceToInterestMetres;
            float m_orientationDegrees;
            bool m_tryStartAtGpsLocation;
            bool m_shouldStartFullscreen;
            std::string m_googleAnalyticsReferrerToken;
            std::string m_flurryAppKey;
            std::string m_yelpConsumerKey;
            std::string m_yelpConsumerSecret;
            std::string m_yelpOAuthToken;
            std::string m_yelpOAuthTokenSecret;
            std::string m_geoNamesUserName;
            std::string m_eegeoSearchServiceUrl;
            std::string m_myPinsWebServiceUrl;
            std::string m_myPinsWebServiceAuthToken;
            std::string m_twitterAuthCode;
            bool m_isKioskTouchInputEnabled;
            bool m_isInKioskMode;
            bool m_useLabels;
            bool m_useJapaneseFont;

            Eegeo::Space::LatLong m_fixedLatlong;
            Eegeo::Resources::Interiors::InteriorId m_fixedInteriorId;
            int m_fixedFloorIndex;
            double m_fixedHeadingDegrees;
            
            std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> m_interiorTrackingInfo;
            std::string m_rawConfig;

            std::vector<Eegeo::Space::LatLongAltitude> m_attractModeTargetSplinePoints;
            std::vector<Eegeo::Space::LatLongAltitude> m_attractModePositionSplinePoints;

            long long m_attractModeTimeoutMs;

        public:
            
            ApplicationConfiguration(
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
                bool useLabels,
                bool useJapaneseFont,
                const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfo,
                const std::string& rawConfig,
                const Eegeo::Space::LatLong fixedLatlong,
                const std::string& fixedInteriorId,
                const int fixedFloorIndex,
                const double fixedHeadingDegrees,
                const std::vector<Eegeo::Space::LatLongAltitude>& attractModeTargetSplinePoints,
                const std::vector<Eegeo::Space::LatLongAltitude>& attractModePositionSplinePoints,
                const long long attractModeTimeoutMs
            );
            
            std::string Name() const;

            std::string EegeoApiKey() const;

            std::string ProductVersion() const;

            std::string BuildNumber() const;

            std::string CombinedVersionString() const;

            std::string ThemeManifestURL() const;

            std::string CoverageTreeManifestURL() const;

            std::string EmbeddedThemeTexturePath() const;
            
            Eegeo::Space::LatLongAltitude InterestLocation() const;
            
            float DistanceToInterestMetres() const;
            
            float OrientationDegrees() const;
            
            bool TryStartAtGpsLocation() const;

            bool ShouldStartFullscreen() const;
            
            std::string GoogleAnalyticsReferrerToken() const;

            std::string FlurryAppKey() const;

            std::string YelpConsumerKey() const;

            std::string YelpConsumerSecret() const;

            std::string YelpOAuthToken() const;

            std::string YelpOAuthTokenSecret() const;

            std::string GeoNamesUserName() const;

            std::string EegeoSearchServiceUrl() const;

            std::string MyPinsWebServiceUrl() const;

            std::string MyPinsWebServiceAuthToken() const;

            std::string TwitterAuthCode() const;

            bool IsKioskTouchInputEnabled() const;

            bool IsInKioskMode() const;
            
            bool UseLabels() const;
            
            bool UseJapaneseFont() const;
            
            const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& InteriorTrackingInfo() const;
            
            std::string RawConfig() const;

            bool FixedIndoorLocation(Eegeo::Space::LatLong& latlong, Eegeo::Resources::Interiors::InteriorId& interiorId, int& floorIndex, double& headingDegrees) const;

            const std::vector<Eegeo::Space::LatLongAltitude>& GetAttractModeTargetSplinePoints() const;
            const std::vector<Eegeo::Space::LatLongAltitude>& GetAttractModePositionSplinePoints() const;
            const long long GetAttractModeTimeoutMs() const;
            const bool IsAttractModeEnabled() const;
        };
    }
}
