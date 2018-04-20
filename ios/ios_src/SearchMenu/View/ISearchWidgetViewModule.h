#pragma once

#include "SearchWidgetView.h"
#include "SearchWidgetController.h"
#include "SearchWidgetContainerView.h"
namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchWidgetViewModule
            {
            public:
                virtual ~ISearchWidgetViewModule() { }
                
                virtual SearchWidgetContainerView& GetSearchWidgetView() const = 0;
                
                virtual SearchWidgetController& GetSearchWidgetController() const = 0;
                virtual UIViewController& GetSearchWidgetUIViewController() const = 0;
            };
        }
    }
}

