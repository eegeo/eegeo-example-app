// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "CategorySearchModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SearchConstants
            {
                extern const std::string NAME_FIELD_NAME;
                extern const std::string JOB_TITLE_FIELD_NAME;
                extern const std::string IMAGE_FILENAME_FIELD_NAME;
                extern const std::string WORKING_GROUP_FIELD_NAME;
                extern const std::string OFFICE_LOCATION_FIELD_NAME;
                extern const std::string DESK_CODE_FIELD_NAME;
                extern const std::string DESKS_FIELD_NAME;
                extern const std::string AVAILABILITY_FIELD_NAME;
                extern const std::string DESCRIPTION_FIELD_NAME;
                extern const std::string CATEGORY_FIELD_NAME;
                extern const std::string SUBCATEGORY_FIELD_NAME;
                extern const std::string DISTANCE_FIELD_NAME;
                extern const std::string HEADING_DEGREES_FIELD_NAME;
                extern const std::string TARGET_INTERIOR_ID_FIELD_NAME;
                extern const std::string TARGET_INTERIOR_FLOOR_FIELD_NAME;
                extern const std::string TARGET_LATITUDE_DEGREES_FIELD_NAME;
                extern const std::string TARGET_LONGITUDE_DEGREES_FILED_NAME;
                
                extern const std::string PERSON_CATEGORY_NAME;
                extern const std::string MEETING_ROOM_CATEGORY_NAME;
                extern const std::string DEFIBRILLATOR_CATEGORY_NAME;
                
                extern const std::string WORKING_GROUP_CATEGORY_NAME;
                extern const std::string FACILITY_CATEGORY_NAME;
                extern const std::string OFFICE_CATEGORY_NAME;
                extern const std::string DEPARTMENT_CATEGORY_NAME;
                extern const std::string STATIONERY_CATEGORY_NAME;
                extern const std::string TRANSITION_CATEGORY_NAME;
                extern const std::string TOILETS_CATEGORY_NAME;
                extern const std::string PRINT_STATION_CATEGORY_NAME;
                extern const std::string EMERGENCY_EXIT_CATEGORY_NAME;
                
                extern const std::string MEETING_ROOM_AVAILABLE;
                extern const std::string MEETING_ROOM_AVAILABLE_SOON;
                extern const std::string MEETING_ROOM_OCCUPIED;
                
                extern const int MEETING_ROOM_AVAILABLE_PRIORITY;
                extern const int MEETING_ROOM_AVAILABLE_SOON_PRIORITY;
                extern const int MEETING_ROOM_OCCUPIED_PRIORITY;
                extern const int MEETING_ROOM_MAX_PRIORITY;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels();

                std::vector<std::string> GetAllCategories();
                
                std::vector<std::string> GetCategories();
                
                bool ShouldShowCategoryAsSearchResult(const std::string& category);
            }
        }
    }
}