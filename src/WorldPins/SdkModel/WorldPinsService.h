// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "Pins.h"
#include "PinController.h"
#include "WorldPins.h"
#include "IWorldPinsService.h"
#include "VectorMath.h"
#include "EnvironmentFlatteningService.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsService : public IWorldPinsService, private Eegeo::NonCopyable
            {
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinSelectionHandler*> TPinToSelectionHandlerMap;
                typedef TPinToSelectionHandlerMap::iterator TPinToSelectionHandlerMapIt;
                
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinVisibilityStateChangedHandler*> TPinToVisiblityHandlerMap;
                typedef TPinToVisiblityHandlerMap::iterator TPinToVisiblityHandlerMapIt;

                TPinToSelectionHandlerMap m_pinsToSelectionHandlers;
                TPinToVisiblityHandlerMap m_pinsToVisbilityChangedHandlers;

                IWorldPinsRepository& m_worldPinsRepository;
                IWorldPinsFactory& m_worldPinsFactory;
                Eegeo::Pins::PinRepository& m_pinRepository;
                Eegeo::Pins::PinController& m_pinController;
                const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                const IWorldPinIconMapping& m_worldPinIconMapping;
                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& m_interiorMarkerPickingService;
                const bool m_useIndoorEntryMarkerLabels;
                bool m_pinAlreadySelected;

            public:
                WorldPinsService(IWorldPinsRepository& worldPinsRepository,
                                 IWorldPinsFactory& worldPinsFactory,
                                 Eegeo::Pins::PinRepository& pinRepository,
                                 Eegeo::Pins::PinController& pinController,
                                 const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                 const IWorldPinIconMapping& worldPinIconMapping,
                                 Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                 const bool useIndoorEntryMarkerLabels);

                ~WorldPinsService();

                WorldPinItemModel* AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                          IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                          const WorldPinFocusData& worldPinFocusData,
                                          bool interior,
                                          const WorldPinInteriorData& worldPinInteriorData,
                                          const Eegeo::Space::LatLong& location,
                                          const std::string& pinIconKey,
                                          float heightAboveTerrainMetres,
                                          int visibilityMask);

                void RemovePin(WorldPinItemModel* pinItemModel);

                void UpdatePinScale(const WorldPinItemModel& pinItemModel, float scale);

                bool HandleTouchTap(const Eegeo::v2& screenTapPoint);

				bool HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint);

                void GetPinEcefAndScreenLocations(const WorldPinItemModel& pinItemModel,
                                                  Eegeo::dv3& ecefLocation,
                                                  Eegeo::v2& screenLocation) const;

                void SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void Update(float dt);

            private:
                IWorldPinSelectionHandler* GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void ErasePin(const WorldPinItemModel::WorldPinItemModelId& id);

				bool TrySelectPinAtPoint(const Eegeo::v2& screenPoint);

            };
        }
    }
}
