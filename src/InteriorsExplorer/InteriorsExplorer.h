// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorsExplorerModule;
            class InteriorsExplorerModel;
            class InteriorWorldPinController;
            class InteriorVisibilityUpdater;
            class InteriorExplorerUserInteractionModel;
            class InteriorsExplorerFloorDraggedObserver;
        }
        
        namespace View
        {
            class InteriorsExplorerViewModel;
            class IInteriorsExplorerView;
            class InteriorsExplorerController;
        }
        
        static const float DefaultInteriorTransitionInterestDistance = 250.f;
    }
}