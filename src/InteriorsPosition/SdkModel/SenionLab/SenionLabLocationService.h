// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "LatLongAltitude.h"
#include "InteriorsModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationService : public Eegeo::Location::ILocationService
                {
                public:
                    SenionLabLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                             const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             ExampleAppMessaging::TMessageBus& messageBus);
                    
                    const bool GetIsAuthorized() const;
                    
                    bool IsIndoors();
                    Eegeo::Resources::Interiors::InteriorId GetInteriorId();
                    bool GetLocation(Eegeo::Space::LatLong& latLong);
                    bool GetAltitude(double& altitude);
                    bool GetFloorIndex(int& floorIndex);
                    bool GetHorizontalAccuracy(double& accuracy);
                    bool GetHeadingDegrees(double& headingDegrees);
                    void StopListening();
                    
                    void SetIsAuthorized(bool isAuthorized);
                    void SetLocation(Eegeo::Space::LatLong& latLong);
                    void SetHeadingDegrees(double headingDegrees);
                    void SetFloorIndex(int floorIndex);
                    void SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                    void SetIsConnected(bool isConnected);
                    
                    void Update(float dt);
                    
                private:
                    bool ShouldUseSenionData() const;
                    
                    Eegeo::Location::ILocationService& m_defaultLocationService;
                    const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                    const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    
                    bool m_isAuthorized;
                    Eegeo::Space::LatLong m_latLong;
                    double m_headingDegrees;
                    int m_floorIndex;
                    Eegeo::Resources::Interiors::InteriorId m_interiorId;
                    bool m_isConnected;
                    
                    float m_disconnectTime;
                    
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                };
            }
        }
    }
}
