// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MobileExampleApp.h"
#include "GlobeCameraTouchController.h"
#include "RenderCamera.h"
#include "GpsGlobeCameraController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "CameraHelpers.h"
#include "LatLongAltitude.h"
#include "IWorldPinsService.h"
#include "ISearchRefreshService.h"
#include "GpsGlobeCameraControllerFactory.h"
#include "GlobeCameraControllerFactory.h"
#include "GlobeCameraTouchSettings.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraComponentConfiguration.h"
#include "InteriorsCameraController.h"
#include "InteriorsCameraControllerFactory.h"
#include "InteriorsGpsCameraController.h"
#include "InteriorsGpsCameraControllerFactory.h"
#include "ITextureFileLoader.h"
#include "SettingsMenuModule.h"
#include "SearchMenuModule.h"
#include "CompassUpdateController.h"
#include "CameraTransitionController.h"
#include "WorldAreaLoaderModule.h"
#include "IInitialExperienceModel.h"
#include "IInitialExperienceController.h"
#include "TagSearchModule.h"
#include "AboutPageModule.h"
#include "RenderContext.h"
#include "ScreenProperties.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "CityThemesModule.h"
#include "RenderingModule.h"
#include "StreamingModule.h"
#include "EnvironmentCharacterSet.h"
#include "IPoiRingTouchController.h"
#include "MyPinCreationModule.h"
#include "SearchResultSectionModule.h"
#include "PoiRingModule.h"
#include "IPoiRingController.h"
#include "MyPinCreationDetailsModule.h"
#include "MyPinsModule.h"
#include "IWorldPinsInFocusController.h"
#include "IWorldPinsScaleController.h"
#include "IWorldPinsFloorHeightController.h"
#include "MyPinDetailsModule.h"
#include "QuadTreeCube.h"
#include "LodRefinementConfig.h"
#include "StreamingVolumeController.h"
#include "GpsMarkerModule.h"
#include "IGpsMarkerController.h"
#include "INetworkCapabilities.h"
#include "ISearchServiceModule.h"
#include "IMyPinsService.h"
#include "IEegeoErrorHandler.h"
#include "OptionsMenuOption.h"
#include "AboutPageMenuOption.h"
#include "ImagePathHelpers.h"
#include "WatermarkModule.h"
#include "InteriorsPresentationModule.h"
#include "InteriorsModelModule.h"
#include "InteriorsExplorerModule.h"
#include "InteriorsEntitiesPinsModule.h"
#include "InteriorsEntitiesPinsController.h"
#include "PinsModule.h"
#include "MapModeModule.h"
#include "AppModeModel.h"
#include "ICompassViewModel.h"
#include "CombinedSearchServiceModule.h"
#include "GeoNamesSearchServiceModule.h"
#include "EegeoSearchServiceModule.h"
#include "SearchVendorNames.h"
#include "SwallowPoiDbModule.h"
#include "SwallowPoiDbWebLoader.h"
#include "SQLiteModule.h"
#include "SwallowSearchServiceModule.h"
#include "SwallowSearchMenuModule.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchTransitionPinController.h"
#include "SwallowPoiDbServiceProvider.h"
#include "YelpSearchConstants.h"
#include "YelpSearchServiceModule.h"
#include "AppCameraModule.h"
#include "AppCameraController.h"
#include "AppModeStatesFactory.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "EnvironmentRayCaster.h"
#include "NativeUIFactories.h"
#include "UserInteractionModule.h"
#include "ReportPinsVisibilityMaskingModule.h"
#include "EnvironmentFlatteningService.h"
#include "UserInteractionModel.h"
#include "EnvironmentFlatteningService.h"
#include "TwitterFeedModule.h"
#include "ITwitterFeedService.h"
#include "SceneModelsModule.h"
#include "VisualMapModule.h"
#include "ConnectivityChangedObserver.h"
#include "InteriorsResourceCounts.h"
#include "HttpAsyncTextureLoader.h"
#include "HttpAsyncCubeTextureLoader.h"
#include "InteriorsMaterialsModule.h"
#include "IInteriorsTextureResourceService.h"
#include "InteriorMaterialSemantics.h"
#include "IInteriorsMaterialDtoRepository.h"
#include "InteriorsMaterialDto.h"
#include "InteriorsMaterialParser.h"
#include "InteriorsMaterialDescriptorLoader.h"
#include "ModalityIgnoredReactionModel.h"
#include "ReactorIgnoredReactionModel.h"
#include "WorldPinIconMappingFactory.h"
#include "IWorldPinIconMapping.h"
#include "DoubleTapIndoorInteractionController.h"
#include "IDoubleTapIndoorInteractionController.h"
#include "AggregateCollisionBvhProvider.h"
#include "TagSearchModelFactory.h"
#include "SearchTagsFactory.h"
#include "ITagSearchRepository.h"
#include "InteriorsHighlightVisibilityController.h"
#include "InteriorsEntityIdHighlightController.h"
#include "Colors.h"
#include "HighlightColorMapper.h"
#include "InteriorInteractionModel.h"
#include "AggregateCollisionBvhProvider.h"
#include "InteriorsHighlightVisibilityController.h"
#include "InteriorsHighlightPickingController.h"
#include "InteriorsModelModule.h"
#include "ModalityIgnoredReactionModel.h"
#include "ReactorIgnoredReactionModel.h"
#include "InteriorsEntityIdHighlightController.h"
#include "IWebProxySettings.h"

#include "RenderingTransformMesh.h"
#include "RenderingTransformMeshModule.h"
#include "DoubleTapIndoorInteractionController.h"
#include "IDoubleTapIndoorInteractionController.h"
#include "AggregateCollisionBvhProvider.h"
#include "WorldPinIconMappingFactory.h"
#include "IWorldPinIconMapping.h"

#include "RestrictedBuildingService.h"
#include "InteriorsStreamingModule.h"
#include "GlobalAppModeTransitionRules.h"
#include "CameraSplinePlaybackController.h"
#include "document.h"

namespace ExampleApp
{
    namespace
    {
        float PanToUnlockThreshold = 0.03f;
        
        Eegeo::Rendering::LoadingScreen* CreateLoadingScreen(const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                             const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule)
        {
            Eegeo::Rendering::LoadingScreenConfig loadingScreenConfig;
            loadingScreenConfig.layout = Eegeo::Rendering::LoadingScreenLayout::Centred;
            loadingScreenConfig.backgroundColor = Eegeo::v4::One();
            loadingScreenConfig.loadingBarColor = Eegeo::v4::One();
            loadingScreenConfig.loadingBarBackgroundColor = Eegeo::v4(32.0f / 255.0f, 121.0f / 255.0f, 192.0f / 255.0f, 1.0f);
            loadingScreenConfig.fadeOutDurationSeconds = 1.5f;
            loadingScreenConfig.screenWidth = screenProperties.GetScreenWidth();
            loadingScreenConfig.screenHeight = screenProperties.GetScreenHeight();
            loadingScreenConfig.screenOversampleScaling = screenProperties.GetOversampleScale();
            loadingScreenConfig.loadingBarOffset = Eegeo::v2(0.5f, 0.1f);
            
            Eegeo::Rendering::LoadingScreen* loadingScreen = Eegeo::Rendering::LoadingScreen::Create(
                                                                                                     Helpers::ImageHelpers::GetImageNameForDevice("SplashScreen", ".png"),
                                                                                                     loadingScreenConfig,
                                                                                                     renderingModule.GetShaderIdGenerator(),
                                                                                                     renderingModule.GetMaterialIdGenerator(),
                                                                                                     renderingModule.GetGlBufferPool(),
                                                                                                     renderingModule.GetVertexLayoutPool(),
                                                                                                     renderingModule.GetVertexBindingPool(),
                                                                                                     platformAbstractionModule.GetTextureFileLoader());
            return loadingScreen;
        }
        
        void AddLocalMaterials(
                               Eegeo::Helpers::IFileIO& fileIO,
                               Eegeo::Resources::Interiors::IInteriorsTextureResourceService& interiorsTextureResourceService,
                               Eegeo::Resources::Interiors::Materials::IInteriorsMaterialDtoRepository& interiorsMaterialDtoRepository)
        {
            std::fstream stream;
            size_t size;
            
            if(fileIO.OpenFile(stream, size, "Interiors/Custom/custom_material_definitions.json"))
            {
                std::string materialsJson((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
                
                rapidjson::Document document;
                if (document.Parse<0>(materialsJson.c_str()).HasParseError())
                {
                    Eegeo_ASSERT(false, "Error parsing local materials JSON file.\n");
                }
                
                for (rapidjson::Value::ConstMemberIterator iter = document.MemberBegin();
                     iter != document.MemberEnd();
                     ++iter)
                {
                    std::string interiorName(iter->name.GetString());
                    const rapidjson::Value& materials(iter->value);
                    
                    size_t materialsCount(materials.Size());
                    for(size_t i = 0; i < materialsCount; ++ i)
                    {
                        const rapidjson::Value& materialJson(materials[static_cast<int>(i)]);
                        Eegeo::Resources::Interiors::Materials::InteriorsMaterialDto dto(Eegeo::Resources::Interiors::Materials::ParseMaterial(materialJson));
                        Eegeo_ASSERT(!interiorsMaterialDtoRepository.Contains(interiorName, dto.materialName));
                        interiorsMaterialDtoRepository.Add(interiorName, dto);
                        
                        const bool localTexture = true;
                        Eegeo::Resources::Interiors::Materials::CreateAndRegisterTextures(dto, interiorsTextureResourceService, localTexture);
                        Eegeo::Resources::Interiors::Materials::CreateAndRegisterCubeMapTextures(dto, interiorsTextureResourceService, localTexture);
                    }
                }
            }
        }
        
        void AddTagSearchModels(
                                Eegeo::Helpers::IFileIO& fileIO,
                                TagSearch::View::ITagSearchRepository& repository)
        {
            const auto& tagSearchModels = TagSearch::View::CreateTagSearchModelsFromFile(
                                                                                         fileIO,
                                                                                         "search_menu_items.json");
            
            for (const auto& t : tagSearchModels)
            {
                repository.AddItem(t);
            }
        }
        
        void SetWebProxySettings(Eegeo::Web::IWebProxySettings& webProxySettings, const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration)
        {
            if (applicationConfiguration.WebProxyEnabled())
            {
                webProxySettings.EnableProxy(applicationConfiguration.WebProxyIpAddress(), applicationConfiguration.WebProxyPort());
                webProxySettings.AddProxyIgnorePattern(applicationConfiguration.WebProxyIgnorePattern());
            }
        }
    }
    
    MobileExampleApp::MobileExampleApp(
                                       const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                       Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                       Eegeo::Rendering::ScreenProperties& screenProperties,
                                       Eegeo::Location::ILocationService& locationService,
                                       Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                       const Eegeo::Config::PlatformConfig& platformConfig,
                                       Eegeo::Helpers::Jpeg::IJpegLoader& jpegLoader,
                                       ExampleApp::InitialExperience::SdkModel::IInitialExperienceModule& initialExperienceModule,
                                       ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                       Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                       ExampleApp::Metrics::IMetricsService& metricsService,
                                       Eegeo::IEegeoErrorHandler& errorHandler,
                                       Menu::View::IMenuReactionModel& menuReaction,
                                       Eegeo::Input::IUserIdleService& userIdleService)
    : m_pGlobeCameraController(NULL)
    , m_pCameraTouchController(NULL)
    , m_pCurrentTouchController(NULL)
    , m_pNavigationService(NULL)
    , m_pWorld(NULL)
    , m_platformAbstractions(platformAbstractions, networkCapabilities)
    , m_pLoadingScreen(NULL)
    , m_pinDiameter(28.f)
    , m_initialisedApplicationViewState(false)
    , m_pCameraTransitionController(NULL)
    , m_pSettingsMenuModule(NULL)
    , m_pSearchMenuModule(NULL)
    , m_pSearchResultSectionModule(NULL)
    , m_pModalityModule(NULL)
    , m_pTagSearchModule(NULL)
    , m_pMapModeModule(NULL)
    , m_pFlattenButtonModule(NULL)
    , m_pSearchModule(NULL)
    , m_pPinsModule(NULL)
    , m_pWorldPinsModule(NULL)
    , m_pWorldPinsIconMapping(NULL)
    , m_pSearchResultOnMapModule(NULL)
    , m_pReactionModelModule(NULL)
    , m_pReactionControllerModule(NULL)
    , m_pSearchResultPoiModule(NULL)
    , m_pPlaceJumpsModule(NULL)
    , m_pCompassModule(NULL)
    , m_pGpsMarkerModule(NULL)
    , m_pWorldAreaLoaderModule(NULL)
    , m_pAboutPageModule(NULL)
    , m_initialExperienceModule(initialExperienceModule)
    , m_messageBus(messageBus)
    , m_sdkDomainEventBus(sdkModelDomainEventBus)
    , m_persistentSettings(persistentSettings)
    , m_pMyPinCreationModule(NULL)
    , m_pPoiRingModule(NULL)
    , m_pMyPinCreationDetailsModule(NULL)
    , m_pMyPinsModule(NULL)
    , m_pMyPinDetailsModule(NULL)
    , m_pOptionsModule(NULL)
    , m_pWatermarkModule(NULL)
    , m_pInteriorsExplorerModule(NULL)
    , m_pInteriorsEntitiesPinsModule(NULL)
    , m_screenProperties(screenProperties)
    , m_networkCapabilities(networkCapabilities)
    , m_setMetricsLocation(false)
    , m_pSearchServiceModule(NULL)
    , m_metricsService(metricsService)
    , m_applicationConfiguration(applicationConfiguration)
    , m_interiorsEnabled(platformConfig.OptionsConfig.EnableInteriors)
    , m_usingLegacyInteriorLabels(!platformConfig.OptionsConfig.EnableLabels || platformConfig.MapLayersConfig.Interiors.UseLegacyLabels)
    , m_pGlobeCameraWrapper(NULL)
    , m_pCameraSplinePlaybackController(NULL)
    , m_pTwitterFeedModule(NULL)
    , m_pVisualMapModule(NULL)
    , m_pConnectivityChangedObserver(NULL)
    , m_toursPinDiameter(48.f)
    , m_pSQLiteModule(NULL)
    , m_pSwallowPoiDbModule(NULL)
    , m_menuReaction(menuReaction)
    , m_pModalityIgnoredReactionModel(NULL)
    , m_pReactorIgnoredReactionModel(NULL)
    , m_pRayCaster(NULL)
    , m_pInteriorsHighlightVisibilityController(NULL)
    , m_pHighlightColorMapper(NULL)
    , m_pInteriorsEntityIdHighlightVisibilityController(NULL)
    , m_userIdleService(userIdleService)
    , m_pGlobalAppModeTransitionRules(NULL)
    {
        if (m_applicationConfiguration.IsInKioskMode())
        {
            PanToUnlockThreshold = 0.0001f;
        }

        m_metricsService.BeginSession(m_applicationConfiguration.FlurryAppKey(), EEGEO_PLATFORM_VERSION_NUMBER);
        
        SetWebProxySettings(m_platformAbstractions.GetProxySettings(), applicationConfiguration);
        
        m_pWorld = Eegeo_NEW(Eegeo::EegeoWorld)(applicationConfiguration.EegeoApiKey(),
                                                m_platformAbstractions,
                                                jpegLoader,
                                                screenProperties,
                                                locationService,
                                                nativeUIFactories,
                                                Eegeo::EnvironmentCharacterSet::UseFontModuleConfig,
                                                platformConfig,
                                                NULL,
                                                &errorHandler
                                                );

        
        m_pWorld->GetMapModule().GetEnvironmentFlatteningService().SetFlattenedScale(0.1f);
        m_pWorld->GetMapModule().GetEnvironmentFlatteningService().SetEasingType(Eegeo::Rendering::EnvironmentFlatteningService::SmoothStep);
        m_pWorld->GetMapModule().GetEnvironmentFlatteningService().SetEaseDuration(0.5f);

        AddLocalMaterials(m_platformAbstractions.GetFileIO(),
                          m_pWorld->GetMapModule().GetInteriorsMaterialsModule().GetInteriorsTextureResourceService(),
                          m_pWorld->GetMapModule().GetInteriorsMaterialsModule().GetInteriorsMaterialDtoRepository());
        
        m_pConnectivityChangedObserver = Eegeo_NEW(Net::SdkModel::ConnectivityChangedObserver)(m_pWorld->GetWebConnectivityValidator(), messageBus);
        
        Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_pWorld->GetTerrainModelModule();
        Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();
        
        m_pNavigationService = Eegeo_NEW(Eegeo::Location::NavigationService)(&m_pWorld->GetLocationService(),
                                                                             &terrainModelModule.GetTerrainHeightProvider());
        
        Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory cameraControllerFactory(terrainModelModule.GetTerrainHeightProvider(),
                                                                                            mapModule.GetEnvironmentFlatteningService(),
                                                                                            mapModule.GetResourceCeilingProvider(),
                                                                                            *m_pNavigationService);
        
        m_pAppModeModel = Eegeo_NEW(AppModes::SdkModel::AppModeModel)(m_messageBus);
        
        const bool useLowSpecSettings = false;
        
        Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsGlobeCameraConfig = Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration::CreateDefault();
        gpsGlobeCameraConfig.panToUnlockThreshold = PanToUnlockThreshold;

        if(m_applicationConfiguration.IsInKioskMode() && m_applicationConfiguration.IsFixedIndoorLocationEnabled())
        {
            Eegeo::Space::LatLong latlong(0.0, 0.0);
            Eegeo::Resources::Interiors::InteriorId interiorId;
            int floorIndex;
            double headingDegrees;
            m_applicationConfiguration.FixedIndoorLocation(latlong, interiorId, floorIndex, headingDegrees);
            gpsGlobeCameraConfig.defaultGpsBearing = headingDegrees;
        }

        Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
        Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);
        
        m_pGlobeCameraController = cameraControllerFactory.Create(gpsGlobeCameraConfig, touchControllerConfig, globeCameraConfig, m_screenProperties);
        
        m_pRayCaster = Eegeo_NEW(Eegeo::Collision::EnvironmentRayCaster)(mapModule.GetAggregateCollisionBvhProvider(),mapModule.GetEnvironmentFlatteningService());
        
        m_pGlobeCameraWrapper = Eegeo_NEW(AppCamera::SdkModel::AppGlobeCameraWrapper)(*m_pGlobeCameraController);

        m_pCameraSplinePlaybackController = Eegeo_NEW(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController)(mapModule.GetResourceCeilingProvider());
        
        m_pCameraTouchController = &m_pGlobeCameraController->GetTouchController();
        
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = m_pGlobeCameraController->GetGlobeCameraController().GetTouchSettings();
        touchSettings.TiltEnabled = true;
        m_pGlobeCameraController->GetGlobeCameraController().SetTouchSettings(touchSettings);
        
        Eegeo::Space::LatLongAltitude location = m_applicationConfiguration.InterestLocation();
        float cameraControllerOrientationDegrees = m_applicationConfiguration.OrientationDegrees();
        float cameraControllerDistanceFromInterestPointMeters = m_applicationConfiguration.DistanceToInterestMetres();
        
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);
        
        m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);
        
        m_pRayCaster = Eegeo_NEW(Eegeo::Collision::EnvironmentRayCaster)(mapModule.GetAggregateCollisionBvhProvider(),mapModule.GetEnvironmentFlatteningService());
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        m_pCameraTransitionService = Eegeo_NEW(ExampleApp::CameraTransitions::SdkModel::CameraTransitionService)();
        
        
        m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(mapModule.GetResourceCeilingProvider(),
                                                                                       Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(platformConfig.PerformanceConfig.DeviceSpecification),
                                                                                       Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
                                                                                       mapModule.GetEnvironmentFlatteningService());

        CreateSQLiteModule(nativeUIFactories);
        
        CreateApplicationModelModules(nativeUIFactories, platformConfig.OptionsConfig.InteriorsAffectedByFlattening);
        
        namespace IntHighlights = InteriorsExplorer::SdkModel::Highlights;
        
        m_pHighlightColorMapper = Eegeo_NEW(InteriorsExplorer::SdkModel::Highlights::HighlightColorMapper)(Eegeo::v4(0.0, 1.0, 0.0, 1.0));
        
        m_pInteriorsHighlightVisibilityController = Eegeo_NEW(IntHighlights::InteriorsHighlightVisibilityController)(
                                                                                                                     mapModule.GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                                                                     mapModule.GetInteriorsModelModule().GetInteriorsCellResourceObserver(),
                                                                                                                     m_searchServiceModules[Search::EegeoVendorName]->GetSearchService(),
                                                                                                                     m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                                     m_pSearchModule->GetSearchResultRepository(),
                                                                                                                     mapModule.GetInteriorsPresentationModule().GetInteriorsLabelsController(),
                                                                                                                     mapModule.GetLabelsModule().GetLabelHiddenFilterModel(),
                                                                                                                     mapModule.GetInteriorsStreamingModule().GetLabelLayerId(),
                                                                                                                     m_messageBus,
                                                                                                                     *m_pHighlightColorMapper,
                                                                                                                     m_persistentSettings,
                                                                                                                     m_usingLegacyInteriorLabels);
        
        Eegeo::Modules::Map::Layers::InteriorsModelModule& interiorsModelModule = mapModule.GetInteriorsModelModule();
        
        Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController& interiorsEntityIdHighlightController = interiorsModelModule.GetInteriorsEntityIdHighlightController();
        interiorsEntityIdHighlightController.SetDefaultHighlightColour(Eegeo::v4(0.0f, 1.0f, 0.0f, 1.0f));

        m_pInteriorsEntityIdHighlightVisibilityController = Eegeo_NEW(InteriorsExplorer::SdkModel::Highlights::InteriorsEntityIdHighlightVisibilityController)(interiorsEntityIdHighlightController,
                                                                                                                                                               m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                                                                               m_pSearchModule->GetSearchResultRepository(),
                                                                                                                                                               m_messageBus,
                                                                                                                                                               interiorsModelModule.GetInteriorsInstanceRepository(),
                                                                                                                                                               *m_pHighlightColorMapper);
        m_pInteriorsPickingController = Eegeo_NEW(IntHighlights::InteriorsHighlightPickingController)(*m_pRayCaster,
                                                                                                      mapModule.GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                                                      mapModule.GetEnvironmentFlatteningService()
                                                                                                      );
        
        m_pCameraTransitionController = Eegeo_NEW(ExampleApp::CameraTransitions::SdkModel::CameraTransitionController)(*m_pGlobeCameraController,
                                                                                                                       m_pInteriorsExplorerModule->GetInteriorsCameraController(),
                                                                                                                       *m_pNavigationService,
                                                                                                                       terrainModelModule.GetTerrainHeightProvider(),
                                                                                                                       *m_pAppModeModel,
                                                                                                                       m_pAppCameraModule->GetController(),
                                                                                                                       interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                                       interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                                       interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                                                       m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                                                       interiorsModelModule.GetInteriorsModelRepository(),
                                                                                                                       m_messageBus);
        m_pCameraTransitionService->SetTransitionController(*m_pCameraTransitionController);
        
        m_pDoubleTapIndoorInteractionController = Eegeo_NEW(ExampleApp::DoubleTapIndoorInteraction::SdkModel::DoubleTapIndoorInteractionController)(m_pInteriorsExplorerModule->GetInteriorsCameraController(),*m_pCameraTransitionController,interiorsPresentationModule.GetInteriorInteractionModel(),*m_pAppModeModel,interiorsPresentationModule.GetInteriorTransitionModel(),m_pWorld->GetTerrainModelModule(),m_pAppCameraModule->GetController());
        
        m_pLoadingScreen = CreateLoadingScreen(screenProperties, m_pWorld->GetRenderingModule(), m_pWorld->GetPlatformAbstractionModule());
        
        if(m_applicationConfiguration.TryStartAtGpsLocation())
        {
            m_pNavigationService->SetGpsMode(Eegeo::Location::NavigationService::GpsModeFollow);
        }
        
        m_pGlobalAppModeTransitionRules = Eegeo_NEW(AppModes::GlobalAppModeTransitionRules)(m_pAppCameraModule->GetController(),
                                                                                            m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                            interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                            GetAppModeModel(),
                                                                                            *m_pGlobeCameraWrapper,
                                                                                            *m_pInteriorCameraWrapper,
                                                                                            m_userIdleService,
                                                                                            m_applicationConfiguration.IsAttractModeEnabled(),
                                                                                            m_applicationConfiguration.GetAttractModeTimeoutMs(),
                                                                                            m_pMyPinCreationModule->GetMyPinCreationModel(),
                                                                                            m_pVisualMapModule->GetVisualMapService());
        InitialiseAppState(nativeUIFactories);
        
        m_pUserInteractionModule = Eegeo_NEW(UserInteraction::SdkModel::UserInteractionModule)(m_pAppCameraModule->GetController(), *m_pCameraTransitionService, m_pInteriorsExplorerModule->GetInteriorsExplorerUserInteractionModel(), m_messageBus);
    }
    
    MobileExampleApp::~MobileExampleApp()
    {
        OnPause();

		m_pAppModeModel->DestroyStateMachine();
        
        Eegeo_DELETE m_pUserInteractionModule;

        Eegeo_DELETE m_pGlobalAppModeTransitionRules;
        
        Eegeo_DELETE m_pStreamingVolume;
        
        Eegeo_DELETE m_pInteriorsHighlightVisibilityController;
        Eegeo_DELETE m_pInteriorsEntityIdHighlightVisibilityController;

        Eegeo_DELETE m_pHighlightColorMapper;
        Eegeo_DELETE m_pInteriorsPickingController;

        DestroyApplicationModelModules();
        
        Eegeo_DELETE m_pRayCaster;

        Eegeo_DELETE m_pSQLiteModule;

        Eegeo_DELETE m_pCameraTransitionService;
        Eegeo_DELETE m_pCameraTransitionController;
        Eegeo_DELETE m_pDoubleTapIndoorInteractionController;
        Eegeo_DELETE m_pNavigationService;
        Eegeo_DELETE m_pCameraSplinePlaybackController;
        Eegeo_DELETE m_pGlobeCameraWrapper;
        Eegeo_DELETE m_pGlobeCameraController;
        Eegeo_DELETE m_pLoadingScreen;
        
        Eegeo_DELETE m_pAppModeModel;
        
        Eegeo_DELETE m_pConnectivityChangedObserver;
        
        Eegeo_DELETE m_pWorld;
    }
    
    void MobileExampleApp::CreateSQLiteModule(Eegeo::UI::NativeUIFactories& nativeUIFactories)
    {
        Eegeo_ASSERT(m_pSQLiteModule == NULL);
        
        Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_platformAbstractions;
        
        const Eegeo::Modules::SQLiteModuleConfig& config = Eegeo::Modules::SQLiteModuleConfig::CreateDefault();
        
        m_pSQLiteModule = Eegeo::Modules::SQLiteModule::Create(config, platformAbstractionModule, nativeUIFactories.AlertBoxFactory());
    }
    void MobileExampleApp::CreateApplicationModelModules(Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                         const bool interiorsAffectedByFlattening)
    {
        Eegeo::EegeoWorld& world = *m_pWorld;
        
        Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
        
        InitialisePinsModules(mapModule, world, interiorsAffectedByFlattening, m_screenProperties.GetOversampleScale());
        
        m_pReportPinsVisibilityMaskingModule = Eegeo_NEW(ReportPinsVisibilityMasking::SdkModel::ReportPinsVisibilityMaskingModule)(m_pWorldPinsModule->GetWorldPinsScaleController(),
                                                                                                                                   mapModule.GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                                                                                   m_messageBus);
        
        Eegeo_ASSERT(m_pSwallowPoiDbModule == NULL);
        Eegeo_ASSERT(m_pSQLiteModule != NULL);

        m_pReactorIgnoredReactionModel = Eegeo_NEW(Menu::View::ReactorIgnoredReactionModel)();
        m_pModalityIgnoredReactionModel = Eegeo_NEW(Menu::View::ModalityIgnoredReactionModel)();
        
        m_pReactionControllerModule = Eegeo_NEW(Reaction::View::ReactionControllerModule)(*m_pReactorIgnoredReactionModel);
        
        m_pAboutPageModule = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageModule)(m_identityProvider,
                                                                                     m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                     m_applicationConfiguration.ProductVersion());
        
        m_pOptionsModule = Eegeo_NEW(ExampleApp::Options::OptionsModule)(m_identityProvider,
                                                                         m_pReactionControllerModule->GetReactionControllerModel(),
                                                                         m_messageBus,
                                                                         m_networkCapabilities);

        // TODO: Check if this module is still relevant
        m_pAppCameraModule = Eegeo_NEW(AppCamera::SdkModel::AppCameraModule)();
        
        const bool useGeoName = true;
        if(useGeoName)
        {
            m_searchServiceModules[Search::GeoNamesVendorName] = Eegeo_NEW(Search::GeoNames::SdkModel::GeoNamesSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                                                    m_platformAbstractions.GetUrlEncoder(),
                                                                                                                                    m_networkCapabilities,
                                                                                                                                    m_applicationConfiguration.GeoNamesUserName());
        }
        
        const bool useEegeoPois = true;
        const auto& searchTags = Search::SdkModel::CreateSearchTagsFromFile(m_platformAbstractions.GetFileIO(), "swallow_search_tags.json");
        const auto& handledTags = Search::Swallow::SearchConstants::GetAllTags();
        
        if(useEegeoPois)
        {
            
            m_searchServiceModules[Search::EegeoVendorName] = Eegeo_NEW(Search::EegeoPois::SdkModel::EegeoSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                                               m_platformAbstractions.GetUrlEncoder(),
                                                                                                                               m_networkCapabilities,
                                                                                                                               searchTags,
                                                                                                                               handledTags,
                                                                                                                               m_applicationConfiguration.EegeoSearchServiceUrl(),
                                                                                                                               m_applicationConfiguration.EegeoApiKey(),
                                                                                                                               world.GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                                                                               m_persistentSettings);
        }
        
        m_pTransitionPoiSearchServiceModule = Eegeo_NEW(Search::EegeoPois::SdkModel::EegeoSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                               m_platformAbstractions.GetUrlEncoder(),
                                                                                                               m_networkCapabilities,
                                                                                                               searchTags,
                                                                                                               handledTags,
                                                                                                               m_applicationConfiguration.EegeoSearchServiceUrl(),
                                                                                                               m_applicationConfiguration.EegeoApiKey(),
                                                                                                               world.GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                                                               m_persistentSettings);

        const bool useYelpSearch = true;
        if (useYelpSearch)
        {
            const auto& searchTags = Search::SdkModel::CreateSearchTagsFromFile(m_platformAbstractions.GetFileIO(), "search_tags.json");
            m_searchServiceModules[ExampleApp::Search::YelpVendorName] = Eegeo_NEW(ExampleApp::Search::Yelp::YelpSearchServiceModule)(m_platformAbstractions.GetWebLoadRequestFactory(),
                                                                                                                                      m_networkCapabilities,
                                                                                                                                      m_platformAbstractions.GetUrlEncoder(),
                                                                                                                                      searchTags,
                                                                                                                                      m_applicationConfiguration.YelpConsumerKey(),
                                                                                                                                      m_applicationConfiguration.YelpConsumerSecret(),
                                                                                                                                      m_applicationConfiguration.YelpOAuthToken(),
                                                                                                                                      m_applicationConfiguration.YelpOAuthTokenSecret(),
                                                                                                                                      m_platformAbstractions.GetFileIO()
                                                                                                                                      );
        }
        
        m_pSearchServiceModule = Eegeo_NEW(Search::Combined::SdkModel::CombinedSearchServiceModule)(m_searchServiceModules, m_pWorld->GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel());
        
        m_pSearchModule = Eegeo_NEW(Search::SdkModel::SearchModule)(m_pSearchServiceModule->GetSearchService(),
                                                                    *m_pGlobeCameraController,
                                                                    *m_pCameraTransitionService,
                                                                    m_pWorld->GetMapModule().GetInteriorsPresentationModule().GetInteriorInteractionModel(),
                                                                    m_messageBus,
                                                                    m_sdkDomainEventBus);
        
        m_pSwallowSearchServiceModule = Eegeo_NEW(Search::Swallow::SdkModel::SwallowSearchServiceModule)(m_pTransitionPoiSearchServiceModule->GetSearchService(),
                                                                                                         *m_pCameraTransitionService,
                                                                                                         m_pAppCameraModule->GetController(),
                                                                                                         m_messageBus,
                                                                                                         m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                         m_networkCapabilities);
        m_pSwallowSearchServiceModule->Start();
        
        Eegeo::Modules::Map::CityThemesModule& cityThemesModule = world.GetCityThemesModule();
        
        m_pVisualMapModule = Eegeo_NEW(VisualMap::SdkModel::VisualMapModule)(cityThemesModule.GetCityThemesService(),
                                                                             cityThemesModule.GetCityThemesUpdater(),
                                                                             mapModule.GetEnvironmentFlatteningService());
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        m_pGpsMarkerModule = Eegeo_NEW(ExampleApp::GpsMarker::SdkModel::GpsMarkerModule)(m_pWorld->GetRenderingModule(),
                                                                                         m_pWorld->GetSceneModelsModule().GetLocalSceneModelFactory(),
                                                                                         m_platformAbstractions,
                                                                                         m_pWorld->GetLocationService(),
                                                                                         m_pWorld->GetTerrainModelModule(),
                                                                                         m_pWorld->GetMapModule(),
                                                                                         interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                         m_pVisualMapModule->GetVisualMapService(),
                                                                                         m_screenProperties,
                                                                                         m_messageBus);

        m_pSettingsMenuModule = Eegeo_NEW(ExampleApp::SettingsMenu::SdkModel::SettingsMenuModule)(m_identityProvider,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_pAboutPageModule->GetAboutPageViewModel(),
                                                                                                  m_pOptionsModule->GetOptionsViewModel());
        
        m_pPlaceJumpsModule = Eegeo_NEW(PlaceJumps::SdkModel::PlaceJumpsModule)(m_platformAbstractions.GetFileIO(),
                                                                                CameraTransitionController(),
                                                                                m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                                                m_messageBus,
                                                                                m_metricsService,
                                                                                m_menuReaction);
        
        m_pTagSearchModule = TagSearch::SdkModel::TagSearchModule::Create(m_pSwallowSearchServiceModule->GetTagSearchModels(),
                                                                          SearchModule().GetSearchQueryPerformer(),
                                                                          m_messageBus,
                                                                          m_metricsService);
        
        m_pMapModeModule = Eegeo_NEW(MapMode::SdkModel::MapModeModule)(m_pVisualMapModule->GetVisualMapService());
        
        m_pFlattenButtonModule = Eegeo_NEW(ExampleApp::FlattenButton::SdkModel::FlattenButtonModule)(m_pMapModeModule->GetMapModeModel(),
                                                                                                     m_identityProvider,
                                                                                                     m_messageBus);
        
        m_pRestrictedBuildingInfoService = Eegeo_NEW(ExampleApp::WifiInfo::RestrictedBuildingService)(m_applicationConfiguration.RestrictedBuildingsInfo(),m_platformAbstractions.GetConnectivityService(), m_pWorld->GetNativeUIFactories());
        
        m_pMyPinsModule = Eegeo_NEW(ExampleApp::MyPins::SdkModel::MyPinsModule)(m_pWorldPinsModule->GetWorldPinsService(),
                                                                                m_platformAbstractions,
                                                                                m_persistentSettings,
                                                                                m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                                                m_messageBus,
                                                                                m_sdkDomainEventBus,
                                                                                *m_pCameraTransitionService,
                                                                                m_pSearchModule->GetMyPinsSearchResultRefreshService(),
                                                                                m_metricsService,
                                                                                m_applicationConfiguration.MyPinsWebServiceUrl(),
																				m_applicationConfiguration.MyPinsWebServiceAuthToken(),
																				*m_pRestrictedBuildingInfoService,
                                                                                m_menuReaction,
                                                                                *m_pModalityIgnoredReactionModel);
        
        m_pSearchResultPoiModule =
        Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiModule)(m_identityProvider,
                                                                            m_pReactionControllerModule->GetReactionControllerModel(),
                                                                            m_pMyPinsModule->GetMyPinsService(),
                                                                            m_pSearchModule->GetSearchResultMyPinsService(),
                                                                            m_pTagSearchModule->GetSearchResultIconKeyMapper(),
                                                                            world.GetPlatformAbstractionModule().GetWebLoadRequestFactory(),
                                                                            m_messageBus);
        
        m_pSearchMenuModule = Eegeo_NEW(ExampleApp::SearchMenu::SdkModel::SearchMenuModule)(m_identityProvider,
                                                                                            m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                            m_pSearchModule->GetSearchQueryPerformer(),
                                                                                            m_messageBus,
                                                                                            m_metricsService);
        
        m_pSwallowSearchMenuModule = Eegeo_NEW(Search::Swallow::SdkModel::SwallowSearchMenuModule)(m_pSearchMenuModule->GetSearchMenuViewModel(),
                                                                                                   m_messageBus);

        Eegeo::Modules::Map::Layers::InteriorsModelModule& interiorsModelModule = mapModule.GetInteriorsModelModule();
        
        m_pSearchResultOnMapModule = Eegeo_NEW(SearchResultOnMap::SdkModel::SearchResultOnMapModule)(m_pSearchModule->GetSearchResultRepository(),
                                                                                                     m_pSearchServiceModule->GetSearchService(),
                                                                                                     m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                     m_pMyPinsModule->GetMyPinsService(),
                                                                                                     m_pTagSearchModule->GetSearchResultIconKeyMapper(),
                                                                                                     m_pSearchModule->GetSearchResultMyPinsService(),
                                                                                                     m_messageBus,
                                                                                                     m_metricsService,
                                                                                                     m_menuReaction);
        
        Eegeo::Camera::GlobeCamera::GpsGlobeCameraControllerFactory gpsCameraControllerFactory(m_pWorld->GetTerrainModelModule().GetTerrainHeightProvider(),
                                                                                               mapModule.GetEnvironmentFlatteningService(),
                                                                                               mapModule.GetResourceCeilingProvider(),
                                                                                               *m_pNavigationService);
        
        m_pSearchResultSectionModule = Eegeo_NEW(SearchResultSection::SdkModel::SearchResultSectionModule)(m_pSearchMenuModule->GetSearchMenuViewModel(),
                                                                                                           m_pSearchModule->GetSearchResultRepository(),
                                                                                                           m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                           *m_pCameraTransitionService,
                                                                                                           interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                           interiorsModelModule.GetInteriorMarkerModelRepository(),
                                                                                                           m_pAppCameraModule->GetController(),
                                                                                                           m_pSearchModule->GetSearchRefreshService(),
                                                                                                           m_messageBus,
                                                                                                           *m_pRestrictedBuildingInfoService);
        
        Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory cameraControllerFactory(m_pWorld->GetTerrainModelModule().GetTerrainHeightProvider(),
                                                                                         mapModule.GetEnvironmentFlatteningService(),
                                                                                         mapModule.GetResourceCeilingProvider());
        
        Eegeo::Resources::Interiors::InteriorsCameraConfiguration interiorsCameraConfig(Eegeo::Resources::Interiors::InteriorsCameraController::CreateDefaultConfig());
        interiorsCameraConfig.ExpandedLookAtDistanceScale = 1.5f;
        interiorsCameraConfig.ExpandedLookAtRightOffset = 0.02f;
        interiorsCameraConfig.ExpandedLookAtUpOffset = 0.09f;
        interiorsCameraConfig.BuildingHorizontalScreenSpacePercentInLandscape = 0.4f;

        const Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration& globeCameraConfig = Eegeo::Resources::Interiors::InteriorsCameraControllerFactory::DefaultGlobeCameraControllerConfiguration();
        const Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration& globeCameraTouchConfig = Eegeo::Resources::Interiors::InteriorsCameraControllerFactory::DefaultGlobeCameraTouchControllerConfiguration();
        Eegeo::Camera::GlobeCamera::GpsGlobeCameraComponentConfiguration gpsGlobeCameraComponentConfig = Eegeo::Resources::Interiors::InteriorsGpsCameraControllerFactory::DefaultGpsGlobeCameraComponentConfiguration();
        gpsGlobeCameraComponentConfig.defaultGpsDistanceToInterest = ExampleApp::InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance;
        gpsGlobeCameraComponentConfig.panToUnlockThreshold = PanToUnlockThreshold;

        if(m_applicationConfiguration.IsInKioskMode() && m_applicationConfiguration.IsFixedIndoorLocationEnabled())
        {
            Eegeo::Space::LatLong latlong(0.0, 0.0);
            Eegeo::Resources::Interiors::InteriorId interiorId;
            int floorIndex;
            double headingDegrees;
            m_applicationConfiguration.FixedIndoorLocation(latlong, interiorId, floorIndex, headingDegrees);
            gpsGlobeCameraComponentConfig.defaultGpsBearing = headingDegrees;
        }

        const Eegeo::Resources::Interiors::InteriorsCameraControllerFactory interiorsCameraControllerFactory(
                                                                                                             interiorsCameraConfig,
                                                                                                             globeCameraConfig,
                                                                                                             globeCameraTouchConfig,
                                                                                                             cameraControllerFactory,
                                                                                                             m_screenProperties,
                                                                                                             interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                             interiorsPresentationModule.GetInteriorViewModel(),
                                                                                                             mapModule.GetEnvironmentFlatteningService(),
                                                                                                             interiorsAffectedByFlattening );
        
        const Eegeo::Resources::Interiors::InteriorsGpsCameraControllerFactory interiorsGpsCameraControllerFactory(gpsGlobeCameraComponentConfig,
                                                                                                                   globeCameraConfig,
                                                                                                                   gpsCameraControllerFactory,
                                                                                                                   m_screenProperties,
                                                                                                                   interiorsPresentationModule.GetInteriorViewModel());
        
        Eegeo::Modules::Map::StreamingModule& streamingModule = world.GetStreamingModule();
        m_pWorldAreaLoaderModule = Eegeo_NEW(WorldAreaLoader::SdkModel::WorldAreaLoaderModule)(streamingModule.GetPrecachingService());

        m_initialExperienceModule.InitialiseWithApplicationModels(m_pWorldAreaLoaderModule->GetWorldAreaLoaderModel());

        const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
        
        if (m_interiorsEnabled)
        {
            m_pInteriorsEntitiesPinsModule = Eegeo_NEW(InteriorsEntitiesPins::SdkModel::InteriorsEntitiesPinsModule(m_pWorld->GetPlatformAbstractionModule(),
                                                                                                                    m_pWorld->GetRenderingModule(),
                                                                                                                    m_pWorld->GetMapModule(),
                                                                                                                    *m_pWorldPinsIconMapping,
                                                                                                                    m_screenProperties,
                                                                                                                    m_usingLegacyInteriorLabels));
        }
        
        m_pInteriorsExplorerModule = Eegeo_NEW(InteriorsExplorer::SdkModel::InteriorsExplorerModule)(interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                     interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                                                     interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                                     interiorsModelModule.GetInteriorMarkerModelRepository(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsService(),
                                                                                                     m_pWorldPinsModule->GetWorldPinsScaleController(),
                                                                                                     *m_pWorldPinsIconMapping,
                                                                                                     mapModule.GetEnvironmentFlatteningService(),
                                                                                                     m_pVisualMapModule->GetVisualMapService(),
                                                                                                     interiorsCameraControllerFactory,
                                                                                                     interiorsGpsCameraControllerFactory,
                                                                                                     m_screenProperties,
                                                                                                     m_identityProvider,
                                                                                                     m_messageBus,
                                                                                                     m_metricsService,
                                                                                                     initialExperienceModel,
                                                                                                     interiorsAffectedByFlattening,
                                                                                                     m_pInteriorsEntitiesPinsModule->GetInteriorsEntitiesPinsController(),
                                                                                                     m_persistentSettings,
                                                                                                     *m_pNavigationService,
                                                                                                     *m_pRestrictedBuildingInfoService,
                                                                                                     m_platformAbstractions.GetConnectivityService());
        
        m_pMyPinCreationModule = Eegeo_NEW(ExampleApp::MyPinCreation::SdkModel::MyPinCreationModule)(m_pMyPinsModule->GetMyPinsService(),
                                                                                                     m_identityProvider,
                                                                                                     m_pSettingsMenuModule->GetSettingsMenuViewModel(),
                                                                                                     m_pSearchModule->GetSearchQueryPerformer(),
                                                                                                     m_pSearchMenuModule->GetSearchMenuViewModel(),
                                                                                                     m_pSearchModule->GetSearchRefreshService(),
                                                                                                     m_pInteriorsExplorerModule->GetScreenControlViewModel(),
                                                                                                     m_messageBus,
                                                                                                     m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pPoiRingModule = Eegeo_NEW(ExampleApp::MyPinCreation::PoiRing::SdkModel::PoiRingModule)(m_pMyPinCreationModule->GetMyPinCreationModel(),
                                                                                                  m_platformAbstractions,
                                                                                                  m_pWorld->GetRenderingModule(),
                                                                                                  m_pWorld->GetAsyncLoadersModule(),
                                                                                                  m_pWorld->GetLightingModule(),
                                                                                                  m_pWorld->GetTerrainModelModule(),
                                                                                                  m_pWorld->GetMapModule(),
                                                                                                  *m_pAppModeModel,
                                                                                                  m_screenProperties,
                                                                                                  interiorsAffectedByFlattening,
                                                                                                  m_applicationConfiguration.IsInKioskMode());
        
        m_pMyPinCreationDetailsModule = Eegeo_NEW(ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsModule)(m_identityProvider,
                                                                                                                      m_pReactionControllerModule->GetReactionControllerModel());
        
        m_pMyPinDetailsModule = Eegeo_NEW(ExampleApp::MyPinDetails::SdkModel::MyPinDetailsModule)(m_identityProvider,
                                                                                                  m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                                  m_pMyPinsModule->GetMyPinsService(),
                                                                                                  m_pSearchResultPoiModule->GetSearchResultPoiViewModel(),
                                                                                                  m_messageBus,
                                                                                                  m_menuReaction);
        
        m_pCompassModule = Eegeo_NEW(ExampleApp::Compass::SdkModel::CompassModule)(*m_pNavigationService,
                                                                                   interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                   world.GetLocationService(),
                                                                                   m_pAppCameraModule->GetController(),
                                                                                   m_identityProvider,
                                                                                   m_messageBus,
                                                                                   m_metricsService,
                                                                                   m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                   *m_pAppModeModel,
                                                                                   m_pWorld->GetNativeUIFactories().AlertBoxFactory(),
                                                                                   m_applicationConfiguration.IsInKioskMode());
        
        m_pInteriorCameraWrapper = Eegeo_NEW(AppCamera::SdkModel::AppInteriorCameraWrapper)(m_pInteriorsExplorerModule->GetInteriorsGpsCameraController(),
                                                                                            m_pInteriorsExplorerModule->GetInteriorsCameraController());
        
        m_pWatermarkModule = Eegeo_NEW(ExampleApp::Watermark::SdkModel::WatermarkModule)(m_identityProvider,
                                                                                         m_applicationConfiguration.Name(),
                                                                                         m_applicationConfiguration.GoogleAnalyticsReferrerToken(),
                                                                                         world.GetMapModule().GetInteriorsPresentationModule().GetInteriorSelectionModel(),
                                                                                         world.GetMapModule().GetInteriorsModelModule().GetInteriorsModelRepository(),
                                                                                         m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                                         m_messageBus);
        
        m_pRenderingTransformMeshModule = Eegeo_NEW(RenderingTransformMesh::SdkModel::RenderingTransformMeshModule)(m_pWorld->GetRenderingModule(),
                                                                                                                    m_platformAbstractions.GetTextureFileLoader());

        m_pTwitterFeedModule = Eegeo_NEW(Social::TwitterFeed::TwitterFeedModule)(m_applicationConfiguration.TwitterAuthCode(),
                                                                                 World().GetPlatformAbstractionModule().GetWebLoadRequestFactory());
        
        std::vector<ScreenControl::View::IScreenControlViewModel*> reactors(GetReactorControls());
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables(GetOpenableControls());

        m_pModalityModule = Eegeo_NEW(Modality::View::ModalityModule)(m_messageBus, openables, *m_pModalityIgnoredReactionModel);
        
        m_pReactionModelModule = Eegeo_NEW(Reaction::View::ReactionModelModule)(m_pReactionControllerModule->GetReactionControllerModel(),
                                                                                openables,
                                                                                reactors,
                                                                                *m_pReactorIgnoredReactionModel);
        
        m_pSearchMenuModule->SetSearchSection("Search Results", m_pSearchResultSectionModule->GetSearchResultSectionModel());
        m_pSearchMenuModule->AddMenuSection("Meeting Rooms", m_pSwallowSearchMenuModule->GetMeetingRoomsMenuModel(), false);
        m_pSearchMenuModule->AddMenuSection("Facilities & Amenities",        m_pSwallowSearchMenuModule->GetFacilitiesMenuModel(), false);
        m_pSearchMenuModule->AddMenuSection("Buildings",          m_pSwallowSearchMenuModule->GetOfficesMenuModel(), false);

        if(!m_applicationConfiguration.IsInKioskMode())
        {
            m_pSearchMenuModule->AddMenuSection("My Location Reports", m_pMyPinsModule->GetMyPinsMenuModel(), true);
        }

        m_pSearchMenuModule->AddMenuSection("Discover", m_pTagSearchModule->GetTagSearchMenuModel(), true);
        
    }
    
    void MobileExampleApp::InitialiseAppState(Eegeo::UI::NativeUIFactories& nativeUIFactories)
    {
        Eegeo::Modules::Map::MapModule& mapModule = m_pWorld->GetMapModule();
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        AppModes::States::SdkModel::AppModeStatesFactory appModeStatesFactory(m_pAppCameraModule->GetController(),
                                                                      *m_pCameraSplinePlaybackController,
                                                                      *m_pGlobeCameraWrapper,
                                                                      *m_pInteriorCameraWrapper,
                                                                      *m_pStreamingVolume,
                                                                      m_pInteriorsExplorerModule->GetInteriorVisibilityUpdater(),
                                                                      m_pInteriorsExplorerModule->GetInteriorsExplorerModel(),
                                                                      m_pInteriorsExplorerModule->GetInteriorsExplorerUserInteractionModel(),
                                                                      *m_pAppModeModel,
                                                                      interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                      interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                      nativeUIFactories,
                                                                      m_pVisualMapModule->GetVisualMapService(),
                                                                      m_pWorld->GetLocationService(),
                                                                      m_userIdleService,
                                                                      m_applicationConfiguration.IsAttractModeEnabled(),
                                                                      m_applicationConfiguration.GetAttractModeTargetSplinePoints(),
                                                                      m_applicationConfiguration.GetAttractModePositionSplinePoints(),
                                                                      m_applicationConfiguration.GetAttractModePlaybackSpeed(),
                                                                      m_screenProperties,
                                                                      m_messageBus,
                                                                      *m_pNavigationService,
                                                                      m_pSearchModule->GetSearchQueryPerformer(),
                                                                      m_pFlattenButtonModule->GetFlattenButtonModel());

        m_pAppModeModel->InitialiseStateMachine(appModeStatesFactory.CreateStateMachineStates(*m_pGlobalAppModeTransitionRules), AppModes::SdkModel::WorldMode, m_pGlobalAppModeTransitionRules);
    }
    
    void MobileExampleApp::DestroyApplicationModelModules()
    {
        m_initialExperienceModule.TearDown();
        
        Eegeo_DELETE m_pModalityIgnoredReactionModel;
        
        Eegeo_DELETE m_pReactorIgnoredReactionModel;
        
        Eegeo_DELETE m_pTwitterFeedModule;
        
        Eegeo_DELETE m_pWorldAreaLoaderModule;
        
        Eegeo_DELETE m_pReactionModelModule;
        
        Eegeo_DELETE m_pModalityModule;
        
        Eegeo_DELETE m_pCompassModule;
        
        Eegeo_DELETE m_pMyPinDetailsModule;
        
        Eegeo_DELETE m_pMyPinCreationDetailsModule;
        
        Eegeo_DELETE m_pPoiRingModule;
        
        Eegeo_DELETE m_pMyPinCreationModule;
        
        Eegeo_DELETE m_pSearchMenuModule;
        
        Eegeo_DELETE m_pSearchResultSectionModule;
        
        Eegeo_DELETE m_pSearchResultOnMapModule;
        
        Eegeo_DELETE m_pSearchResultPoiModule;
        
        Eegeo_DELETE m_pPlaceJumpsModule;

        Eegeo_DELETE m_pFlattenButtonModule;
        
        Eegeo_DELETE m_pMapModeModule;
        
        Eegeo_DELETE m_pTagSearchModule;
        Eegeo_DELETE m_pSwallowSearchMenuModule;

        Eegeo_DELETE m_pSettingsMenuModule;
        
        Eegeo_DELETE m_pVisualMapModule;
        
        Eegeo_DELETE m_pGpsMarkerModule;
        
        Eegeo_DELETE m_pInteriorCameraWrapper;
        
        Eegeo_DELETE m_pWatermarkModule;
        
        Eegeo_DELETE m_pRestrictedBuildingInfoService;
        
        Eegeo_DELETE m_pInteriorsExplorerModule;
        
        Eegeo_DELETE m_pSearchModule;
        
        Eegeo_DELETE m_pSwallowSearchServiceModule;

        Eegeo_DELETE m_pTransitionPoiSearchServiceModule;
        
        for(std::map<std::string, ExampleApp::Search::SdkModel::ISearchServiceModule*>::iterator it = m_searchServiceModules.begin(); it != m_searchServiceModules.end(); ++it)
        {
            Eegeo_DELETE (*it).second;
        }
        m_searchServiceModules.clear();

        Eegeo_DELETE m_pReportPinsVisibilityMaskingModule;
        
        Eegeo_DELETE m_pMyPinsModule;
        
        Eegeo_DELETE m_pWorldPinsModule;
        
        Eegeo_DELETE m_pPinsModule;
        
        Eegeo_DELETE m_pWorldPinsIconMapping;
        
        Eegeo_DELETE m_pAppCameraModule;
        
        Eegeo_DELETE m_pOptionsModule;
        
        Eegeo_DELETE m_pAboutPageModule;
        
        
        Eegeo_DELETE m_pReactionControllerModule;
        
        Eegeo_DELETE m_pSwallowPoiDbModule;
    }
    
    std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> MobileExampleApp::GetOpenableControls() const
    {
        std::vector<ExampleApp::OpenableControl::View::IOpenableControlViewModel*> openables;
        openables.push_back(&SettingsMenuModule().GetSettingsMenuViewModel());
        openables.push_back(&SearchMenuModule().GetSearchMenuViewModel());
        openables.push_back(&SearchResultPoiModule().GetObservableOpenableControl());
        openables.push_back(&AboutPageModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinDetailsModule().GetObservableOpenableControl());
        openables.push_back(&MyPinCreationModule().GetObservableOpenableControl());
        openables.push_back(&OptionsModule().GetObservableOpenableControl());
        return openables;
    }
    
    std::vector<ExampleApp::ScreenControl::View::IScreenControlViewModel*> MobileExampleApp::GetReactorControls() const
    {
        std::vector<ExampleApp::ScreenControl::View::IScreenControlViewModel*> reactors;
        reactors.push_back(&SettingsMenuModule().GetSettingsMenuViewModel());
        reactors.push_back(&SearchMenuModule().GetSearchMenuViewModel());
        reactors.push_back(&FlattenButtonModule().GetScreenControlViewModel());
        reactors.push_back(&WorldPinsModule().GetScreenControlViewModel());
        reactors.push_back(&CompassModule().GetScreenControlViewModel());
        reactors.push_back(&MyPinCreationModule().GetInitiationScreenControlViewModel());
        reactors.push_back(&WatermarkModule().GetScreenControlViewModel());
        reactors.push_back(&InteriorsExplorerModule().GetScreenControlViewModel());
        return reactors;
    }
    
    Eegeo::Pins::PinsModule* MobileExampleApp::CreatePlatformPinsModuleInstance(Eegeo::EegeoWorld& world,
                                                                                const Eegeo::Helpers::GLHelpers::TextureInfo& pinTextureInfo,
                                                                                const Eegeo::Rendering::AtlasTexturePageLayout& atlasTexturePageLayout)
    {
        Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
        
        return Eegeo::Pins::PinsModule::CreateWithAtlas(renderingModule,
                                                        world.GetPlatformAbstractionModule(),
                                                        mapModule,
                                                        pinTextureInfo.textureId,
                                                        atlasTexturePageLayout,
                                                        Eegeo::Rendering::LayerIds::Pins,
                                                        m_screenProperties);
    }
    
    void MobileExampleApp::InitialisePinsModules(Eegeo::Modules::Map::MapModule& mapModule,
                                                 Eegeo::EegeoWorld& world,
                                                 const bool interiorsAffectedByFlattening,
                                                 const float screenOversampleScale)
    {
        
        ExampleApp::WorldPins::SdkModel::WorldPinIconMappingFactory worldPinIconMappingFactory(
                                                                                               m_platformAbstractions.GetFileIO(),
                                                                                               "SearchResultOnMap/pin_sheet.json",
                                                                                               m_platformAbstractions.GetTextureFileLoader(),
                                                                                               m_applicationConfiguration.IsInKioskMode());
        
        m_pWorldPinsIconMapping = worldPinIconMappingFactory.Create();
        
        m_pPinsModule = CreatePlatformPinsModuleInstance(world, m_pWorldPinsIconMapping->GetTextureInfo(), m_pWorldPinsIconMapping->GetTexturePageLayout());
        
        Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
        
        m_pWorldPinsModule = Eegeo_NEW(ExampleApp::WorldPins::SdkModel::WorldPinsModule)(
                                                                                         m_pPinsModule->GetRepository(),
                                                                                         m_pPinsModule->GetController(),
                                                                                         mapModule.GetEnvironmentFlatteningService(),
                                                                                         m_identityProvider,
                                                                                         m_messageBus,
                                                                                         interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                         interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                         m_sdkDomainEventBus,
                                                                                         interiorsAffectedByFlattening,
                                                                                         m_menuReaction,
                                                                                         screenOversampleScale,
                                                                                         *m_pWorldPinsIconMapping,
                                                                                         m_applicationConfiguration.IsInKioskMode());
    }
    
    void MobileExampleApp::OnPause()
    {
        Eegeo::EegeoWorld& eegeoWorld = World();
        eegeoWorld.OnPause();
    }
    
    void MobileExampleApp::OnResume()
    {
        Eegeo::EegeoWorld& eegeoWorld = World();
        eegeoWorld.OnResume();
    }
    
    void MobileExampleApp::Update(float dt)
    {
        Eegeo::EegeoWorld& eegeoWorld(World());
        
        m_pCurrentTouchController = &m_pAppCameraModule->GetController().GetTouchController();
        
        eegeoWorld.EarlyUpdate(dt);
        
        m_pNavigationService->Update(dt);
        
        m_pCameraTransitionService->Update(dt);
        m_pAppCameraModule->GetController().Update(dt);
        
        m_pAppModeModel->Update(dt);
        
        m_pInteriorsExplorerModule->Update(dt);
        
        Eegeo::Camera::RenderCamera renderCamera = m_pAppCameraModule->GetController().GetRenderCamera();
        Eegeo::Camera::CameraState cameraState = m_pAppCameraModule->GetController().GetCameraState();
        
        Eegeo::dv3 ecefInterestPoint(cameraState.InterestPointEcef());
        
        m_pPoiRingModule->GetPoiRingController().Update(dt, renderCamera, ecefInterestPoint);
        
        Eegeo::EegeoUpdateParameters updateParameters(dt,
                                                      cameraState.LocationEcef(),
                                                      cameraState.InterestPointEcef(),
                                                      cameraState.ViewMatrix(),
                                                      cameraState.ProjectionMatrix(),
                                                      GetUpdatedStreamingVolume(cameraState, renderCamera),
                                                      m_screenProperties);
        
        eegeoWorld.Update(updateParameters);
        
        m_pSwallowSearchServiceModule->Update();
        m_pSearchModule->GetSearchRefreshService().TryRefreshSearch(dt, ecefInterestPoint, cameraState.LocationEcef());
        
        m_pPinsModule->GetController().Update(dt, renderCamera);
        
        if(!eegeoWorld.Initialising() || (m_pLoadingScreen == NULL && eegeoWorld.Initialising()))
        {
            WorldPinsModule().GetWorldPinsService().Update(dt);
            WorldPinsModule().GetWorldPinsScaleController().Update(dt, renderCamera);
            WorldPinsModule().GetWorldPinsFloorHeightController().Update(dt);
            
            CompassModule().GetCompassUpdateController().Update(dt);
            m_pGpsMarkerModule->GetGpsMarkerController().Update(dt, renderCamera);
            
            if (m_interiorsEnabled)
            {
                Eegeo_ASSERT(m_pInteriorsEntitiesPinsModule != NULL);
                
                m_pInteriorsEntitiesPinsModule->GetPinsModule().Update(dt, renderCamera);
                m_pInteriorsEntitiesPinsModule->GetInteriorsEntitiesPinsController().Update(dt);
            }
            
            InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
            if(!initialExperienceModel.HasCompletedInitialExperience() && IsLoadingScreenComplete())
            {
                InitialExperience::SdkModel::IInitialExperienceController& initialExperienceController = m_initialExperienceModule.GetInitialExperienceController();
                initialExperienceController.Update(dt);
            }
            
            if (!m_setMetricsLocation)
            {
                Eegeo::dv3 gpsLocation;
                if(m_pNavigationService->TryGetGpsLocationOnTerrain(gpsLocation))
                {
                    Eegeo::Space::LatLong ll = Eegeo::Space::LatLong::FromECEF(gpsLocation);
                    m_metricsService.SetPosition(ll.GetLatitudeInDegrees(), ll.GetLongitudeInDegrees(), 0.f, 0.f);
                    m_setMetricsLocation = true;
                }
            }
        }
        
        UpdateLoadingScreen(dt);
    }
    
    void MobileExampleApp::Draw (float dt)
    {
        Eegeo::EegeoWorld& eegeoWorld = World();
        
        Eegeo::Camera::RenderCamera renderCamera = m_pAppCameraModule->GetController().GetRenderCamera();
        Eegeo::Camera::CameraState cameraState = m_pAppCameraModule->GetController().GetCameraState();
        
        Eegeo::dv3 ecefInterestPoint(cameraState.InterestPointEcef());
        
        if(!eegeoWorld.Initialising())
        {
            WorldPinsModule().GetWorldPinsInFocusController().Update(dt, ecefInterestPoint, renderCamera);
            
        }
        
        Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
                                                  cameraState.InterestPointEcef(),
                                                  cameraState.ViewMatrix(),
                                                  cameraState.ProjectionMatrix(),
                                                  m_screenProperties);
        
        eegeoWorld.Draw(drawParameters);
        
        if (m_pLoadingScreen != NULL)
        {
            m_pLoadingScreen->Draw();
        }
    }
    
    void MobileExampleApp::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_screenProperties = screenProperties;
        
        if (m_pLoadingScreen != NULL)
        {
            m_pLoadingScreen->NotifyScreenDimensionsChanged(screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
        }
        
        m_pPinsModule->UpdateScreenProperties(m_screenProperties);
        
        m_pGlobeCameraController->UpdateScreenProperties(m_screenProperties);

        m_pCameraSplinePlaybackController->UpdateScreenProperties(m_screenProperties);
        
        m_pInteriorsExplorerModule->GetInteriorsGpsCameraController().UpdateScreenProperties(m_screenProperties);
    }
    
    void MobileExampleApp::InitialiseApplicationViewState()
    {
        Eegeo_ASSERT(m_initialisedApplicationViewState == false, "Can only initialise application state once!\n");
        
        m_initialisedApplicationViewState = true;
        
        m_pSettingsMenuModule->GetSettingsMenuViewModel().AddToScreen();
        m_pSearchMenuModule->GetSearchMenuViewModel().AddToScreen();
        m_pFlattenButtonModule->GetScreenControlViewModel().AddToScreen();
        m_pCompassModule->GetScreenControlViewModel().AddToScreen();
        m_pMyPinCreationModule->GetInitiationScreenControlViewModel().AddToScreen();
        m_pWatermarkModule->GetWatermarkViewModel().AddToScreen();
    }
    
    void MobileExampleApp::UpdateLoadingScreen(float dt)
    {
        if (m_pLoadingScreen == NULL)
        {
            return;
        }
        
        Eegeo::EegeoWorld& eegeoWorld = World();
        
        if (!eegeoWorld.Initialising() && !m_pLoadingScreen->IsDismissed())
        {
            m_pLoadingScreen->Dismiss();
        }
        
        m_pLoadingScreen->SetProgress(eegeoWorld.GetInitialisationProgress());
        m_pLoadingScreen->Update(dt);
        
        if (!m_pLoadingScreen->IsVisible())
        {
            Eegeo_DELETE m_pLoadingScreen;
            m_pLoadingScreen = NULL;
            
            // Note: we're doing this here in a hacky way, as the views aren't constructed when the MEA ctor runs
            // ... doing it a little later ensures the view will get the notifications when items are added.
            MyPinsModule().GetMyPinsService().LoadAllPinsFromDisk();
            
            AddTagSearchModels(m_platformAbstractions.GetFileIO(), m_pTagSearchModule->GetTagSearchRepository());

            if (m_applicationConfiguration.IsAttractModeEnabled())
            {
                m_pAppModeModel->SetAppMode(AppModes::SdkModel::AttractMode);
            }
        }
    }
    
    bool MobileExampleApp::IsRunning() const
    {
        return !m_pWorld->Initialising();
    }
    
    Eegeo::Streaming::IStreamingVolume& MobileExampleApp::GetUpdatedStreamingVolume(const Eegeo::Camera::CameraState& cameraState,
                                                                                    const Eegeo::Camera::RenderCamera& renderCamera)
    {
        std::vector<Eegeo::Geometry::Plane> frustumPlanes(Eegeo::Geometry::Frustum::PLANES_COUNT);
        BuildFrustumPlanesFromViewProjection(frustumPlanes, renderCamera.GetViewProjectionMatrix());
        const double d = renderCamera.GetAltitude() * Eegeo::Streaming::StreamingVolumeController::CAMERA_ALTITUDE_TO_FAR_PLANE_DISTANCE_MULTIPLIER;
        const double cameraFarPlaneD = fmin(fmax(d, Eegeo::Streaming::StreamingVolumeController::MIN_STREAMING_FAR_PLANE_DISTANCE),
                                            frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d);
        frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d = static_cast<float>(cameraFarPlaneD);
        
        m_pStreamingVolume->updateStreamingVolume(renderCamera.GetEcefLocation(), frustumPlanes, renderCamera.GetFOV());
        m_pStreamingVolume->ResetVolume(cameraState.InterestPointEcef());
        return *m_pStreamingVolume;
    }
    
    void MobileExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchRotate(data);
        
    }
    
    void MobileExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCompassModule->GetTouchController().HandleRotateStart(data);
        m_pCurrentTouchController->Event_TouchRotate_Start(data);
    }
    
    void MobileExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }

        m_pCompassModule->GetTouchController().HandleRotateEnd(data);
        m_pCurrentTouchController->Event_TouchRotate_End(data);
    }
    
    void MobileExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPinch(data);
    }
    
    void MobileExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPinch_Start(data);
    }
    
    void MobileExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPinch_End(data);
    }
    
    void MobileExampleApp::Event_TouchPan(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan(data);
    }
    
    void MobileExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan_Start(data);
    }
    
    void MobileExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if(!CanAcceptTouch() || poiRingTouchController.IsDragging())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TouchPan_End(data);
    }
    
    void MobileExampleApp::Event_TouchTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        if(m_pWorldPinsModule->GetWorldPinsService().HandleTouchTap(data.point))
        {
            return;
        }

        
        m_pInteriorsEntitiesPinsModule->GetInteriorsEntitiesPinsController().Event_TouchTap(data);
        
        m_pCurrentTouchController->Event_TouchTap(data);
        
        const Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = m_pWorld->GetMapModule().GetInteriorsPresentationModule();
        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel = interiorsPresentationModule.GetInteriorInteractionModel();
        if (interiorInteractionModel.HasInteriorModel())
        {
            m_pInteriorsPickingController->CastRayFromScreenPosition(Eegeo::v2(data.point.GetX(), data.point.GetY()), m_pAppCameraModule->GetController().GetRenderCamera());
        }
    }
    
    void MobileExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        if (m_pWorldPinsModule->GetWorldPinsService().HandleTouchDoubleTap(data.point))
        {
            return;
        }
        if (m_pAppModeModel->GetAppMode() == AppModes::SdkModel::InteriorMode)
        {
            m_pDoubleTapIndoorInteractionController->OnDoubleTap(data);
        }
        m_pCurrentTouchController->Event_TouchDoubleTap(data);
    }
    
    void MobileExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchDown(data, m_pAppCameraModule->GetController().GetRenderCamera(), m_pAppCameraModule->GetController().GetNonFlattenedCameraPosition()))
        {
            m_pCurrentTouchController->Event_TouchDown(data);
        }
    }
    
    void MobileExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();

        if (!poiRingTouchController.HandleTouchMove(data, m_pAppCameraModule->GetController().GetRenderCamera(), m_pAppCameraModule->GetController().GetNonFlattenedCameraPosition()))
        {
            m_pCurrentTouchController->Event_TouchMove(data);
        }
    }
    
    void MobileExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        MyPinCreation::PoiRing::SdkModel::IPoiRingTouchController& poiRingTouchController = m_pPoiRingModule->GetPoiRingTouchController();
        if (!poiRingTouchController.HandleTouchUp(data))
        {
            m_pCurrentTouchController->Event_TouchUp(data);
        }
    }
    
    void MobileExampleApp::Event_Zoom(const AppInterface::ZoomData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_Zoom(data);
    }
    
    void MobileExampleApp::Event_Keyboard(const AppInterface::KeyboardData& data)
    {
        if (data.printable)
            Eegeo_TTY("Key Down: %c", data.keyCode);
        else
            Eegeo_TTY("Key Up: %c", data.keyCode);
    }
    
    void MobileExampleApp::Event_TiltStart(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TiltStart(data);
    }
    
    void MobileExampleApp::Event_TiltEnd(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_TiltEnd(data);
    }
    
    void MobileExampleApp::Event_Tilt(const AppInterface::TiltData& data)
    {
        if (!CanAcceptTouch())
        {
            return;
        }
        
        m_pCurrentTouchController->Event_Tilt(data);
    }
    
    bool MobileExampleApp::CanAcceptTouch() const
    {
        const bool worldIsInitialising = World().Initialising() && m_pLoadingScreen != NULL;
        const bool userInteractionEnabled = m_pUserInteractionModule->GetUserInteractionModel().IsEnabled();
        
        InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel = m_initialExperienceModule.GetInitialExperienceModel();
        const bool lockedCameraStepsCompleted = initialExperienceModel.LockedCameraStepsCompleted();
        
        return !worldIsInitialising && lockedCameraStepsCompleted && userInteractionEnabled;
    }
}
