// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDirectionsMenuViewModule.h"

#include "BidirectionalBus.h"
#include "Menu.h"
#include "MenuController.h"
#include "Modality.h"
#include "Rendering.h"
#include "DirectionsMenuController.h"
#include "Types.h"
#include "ILocationService.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class DirectionsMenuViewModule: public IDirectionsMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                DirectionsMenuController* m_pController;
                DirectionsMenuView* m_pView;


            public:
                DirectionsMenuViewModule(Menu::View::IMenuModel& searchMenuModel,
                                         Menu::View::IMenuViewModel& searchMenuViewModel,
                                        Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                         const Eegeo::Rendering::ScreenProperties& screenProperties,
                                         Modality::View::IModalBackgroundView& modalBackgroundView,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         Eegeo::Location::ILocationService& locationService,
                                         ExampleApp::Menu::View::IMenuViewModel& settingsMenuViewModel);
                
                ~DirectionsMenuViewModule();
                
                Menu::View::MenuController& GetMenuController() const;
                
                DirectionsMenuView& GetDirectionsMenuView() const;
            };
        }
    }
}
