// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
//            class SearchQuery
//            {
//                std::string m_query;
//                bool m_isCategory;
//                Eegeo::Space::LatLongAltitude m_where;
//                float m_radius;
//
//            public:
//                SearchQuery(const std::string& query,
//                            bool isCategory,
//                            const Eegeo::Space::LatLongAltitude& where,
//                            float radius);
//
//                ~SearchQuery();
//
//                const std::string& Query() const;
//
//                bool IsCategory() const;
//
//                float Radius() const;
//
//                const Eegeo::Space::LatLongAltitude& Location() const;
//
//            };
            
            class SearchQuery
            {
                std::string m_query;
                bool m_isCategory;
                bool m_isInterior;
                Eegeo::Space::LatLongAltitude m_where;
                float m_radius;
                
            public:
                SearchQuery(const std::string& query,
                            bool isCategory,
                            bool isInterior,
                            const Eegeo::Space::LatLongAltitude& where,
                            float radius);
                
                ~SearchQuery();
                
                const std::string& Query() const;
                
                bool IsCategory() const;
                
                bool IsInterior() const;
                
                float Radius() const;
                
                const Eegeo::Space::LatLongAltitude& Location() const;
                
            };
        }
    }
}
