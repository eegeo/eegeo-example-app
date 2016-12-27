// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationModule.h"
#include "ApplicationConfigurationService.h"
#include "ApplicationConfigurationJsonParser.h"
#include "ApplicationConfigurationReader.h"
#include "IApplicationConfigurationVersionProvider.h"
#include "ConfigSections.h"
#include "IPlatformConfigBuilder.h"
#include "ApiKey.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                ApplicationConfiguration BuildDefaultConfig(const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider)
                {
                    // please see ./README.md and comments in ./src/ApiKey.h for instructions on how to obtain an EegeoApiKey and set via the app config file
                    const std::string emptyEegeoApiKey;
                    const std::string& productVersion = applicationConfigurationVersionProvider.GetProductVersionString();
                    const std::string& buildNumber = applicationConfigurationVersionProvider.GetProductVersionString();
                    const std::string& combinedVersionString = productVersion + "." + buildNumber;
                    const std::string emptyGoogleAnalyticsReferrerToken;
                    const std::string emptyFlurryApiKey;
                    const std::string emptyYelpConsumerKey;
                    const std::string emptyYelpConsumerSecret;
                    const std::string emptyYelpOAuthToken;
                    const std::string emptyYelpOAuthTokenSecret;
                    const std::string emptyGeoNamesUserName;
                    const std::string eegeoSearchServiceUrl = "https://poi.eegeo.com/v1.1";
                    const std::string emptyMyPinsWebServiceUrl;
                    const std::string emptyMyPinsWebServiceAuthToken;
                    const std::string emptyTwitterAuthCode;
                    
                    const std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfo;
                    
                    const bool tryStartAtGpsLocation = false;
                    const bool shouldStartFullscreen = false;
                    const bool isKioskTouchInputEnabled = false;
                    const bool isInKioskMode = false;
                    const bool useLabels = true;
                    const bool useJapaneseFont = false;
                    std::string outdoorSearchMenuItems;

                    const Eegeo::Space::LatLong fixedLocation(Eegeo::Space::LatLong(0.0, 0.0));
                    const std::string fixedInteriorId("");
                    const int fixedFloorIndex = 0;
                    const double fixedOrientationDegrees = 180.0;

                    const std::vector<Eegeo::Space::LatLongAltitude> attractModeTargetSplinePoints;
                    const std::vector<Eegeo::Space::LatLongAltitude> attractModePositionSplinePoints;
                    const long long attractModeTimeoutDisabled = 0;
                    
                    return ApplicationConfiguration ("Eegeo Example App",
                        emptyEegeoApiKey,
                        productVersion,
                        buildNumber,
                        combinedVersionString,
                        Eegeo::Config::CoverageTreeManifestUrlDefault,
                        Eegeo::Config::CityThemesManifestUrlDefault,
                        "EmbeddedTheme",
                        Eegeo::Space::LatLongAltitude(37.7858f, -122.401f, 2.7),
                        1781.0f,
                        0.f,
                        tryStartAtGpsLocation,
                        shouldStartFullscreen,
                        emptyGoogleAnalyticsReferrerToken,
                        emptyFlurryApiKey,
                        emptyYelpConsumerKey,
                        emptyYelpConsumerSecret,
                        emptyYelpOAuthToken,
                        emptyYelpOAuthTokenSecret,
                        emptyGeoNamesUserName,
                        eegeoSearchServiceUrl,
                        emptyMyPinsWebServiceUrl,
                        emptyMyPinsWebServiceAuthToken,
                        emptyTwitterAuthCode,
                        isKioskTouchInputEnabled,
                        isInKioskMode,
                        useLabels,
                        useJapaneseFont,
                        interiorTrackingInfo,
                        outdoorSearchMenuItems,
                        fixedLocation,
                        fixedInteriorId,
                        fixedFloorIndex,
                        fixedOrientationDegrees,
                        attractModeTargetSplinePoints,
                        attractModePositionSplinePoints,
                        attractModeTimeoutDisabled);
                }
            }
            
            ApplicationConfig::ApplicationConfiguration LoadAppConfig(Eegeo::Helpers::IFileIO& fileIO,
                                                                      ApplicationConfig::SdkModel::IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider,
                                                                      const std::string& configFilePath
                                                                      )
            {
        
                ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationModule applicationConfigurationModule(fileIO,
                                                                                                                       applicationConfigurationVersionProvider
                                                                                                                       );
                return applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration(configFilePath);
            }
            
            Eegeo::Config::PlatformConfig BuildPlatformConfig(Eegeo::Config::IPlatformConfigBuilder& platformConfigBuilder,
                                                              const ApplicationConfiguration& appConfig)
            {
                Eegeo::Config::PlatformConfig platformConfig = platformConfigBuilder.Build();
                platformConfig.CoverageTreeConfig.ManifestUrl = appConfig.CoverageTreeManifestURL();
                platformConfig.CityThemesConfig.StreamedManifestUrl = appConfig.ThemeManifestURL();
                platformConfig.CityThemesConfig.EmbeddedThemeTexturePath = appConfig.EmbeddedThemeTexturePath();

                if (appConfig.UseLabels())
                {
                    platformConfig.OptionsConfig.EnableLabels = true;
                    platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = appConfig.UseJapaneseFont() ? "IPAexGothic_sdf.fnt" : "opensans_semibold_sdf.fnt";
                    platformConfig.MapLayersConfig.Interiors.UseLegacyLabels = false;
                    platformConfig.MapLayersConfig.Interiors.UseLegacyEntryMarkers = false;
                    platformConfig.MapLayersConfig.Interiors.LabelCategoryMapPath = "Interiors/label_category_mapping.json";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.StyleSheetPath = "Labels/label_style_sheet.json";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.CategoryIconMapPath = "Labels/label_category_icon_map.json";
                    platformConfig.MapLayersConfig.IconsModuleConfig.IconsEnabled = true;
                    platformConfig.MapLayersConfig.IconsModuleConfig.IconSetManifestPath = "SearchResultOnMap/pin_sheet.json";
                }
                else
                {
                    platformConfig.OptionsConfig.EnableLabels = false;
                    platformConfig.MapLayersConfig.FontsModuleConfig.EnvironmentFontFilename = appConfig.UseJapaneseFont() ? "IPAexGothic32_A8_icons.fnt" : "FrankBold50_A8_icons.fnt";
                    platformConfig.MapLayersConfig.Interiors.UseLegacyLabels = true;
                    platformConfig.MapLayersConfig.Interiors.LabelCategoryMapPath = "";
                    platformConfig.MapLayersConfig.LabelsModuleConfig.StyleSheetPath = "";
                    
                }
                return platformConfig;
            }
            
            ApplicationConfigurationModule::ApplicationConfigurationModule(
                Eegeo::Helpers::IFileIO& fileIO,
                const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider)
            {
                const ApplicationConfiguration& defaultConfig = BuildDefaultConfig(applicationConfigurationVersionProvider);

                m_pApplicationConfigurationReader = Eegeo_NEW(ApplicationConfigurationReader)(fileIO);
                m_pApplicationConfigurationParser = Eegeo_NEW(ApplicationConfigurationJsonParser)(defaultConfig);
                m_pApplicationConfigurationService = Eegeo_NEW(ApplicationConfigurationService)(*m_pApplicationConfigurationParser,
																								*m_pApplicationConfigurationReader);                    
            }
            
            ApplicationConfigurationModule::~ApplicationConfigurationModule()
            {
                Eegeo_DELETE m_pApplicationConfigurationService;
                Eegeo_DELETE m_pApplicationConfigurationParser;
                Eegeo_DELETE m_pApplicationConfigurationReader;
            }
            
            IApplicationConfigurationService& ApplicationConfigurationModule::GetApplicationConfigurationService()
            {
                return *m_pApplicationConfigurationService;
            }
        }
    }
}
