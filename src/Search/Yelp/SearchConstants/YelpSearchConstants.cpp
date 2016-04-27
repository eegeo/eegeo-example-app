// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchConstants.h"

//
// Yelp categories from http://www.yelp.com/developers/documentation/v2/all_category_list
//

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                std::string GetDefaultCategory() { return "misc"; }
                
                std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap()
                {
                    std::map<std::string, std::string> yelpToApplicationCategoryMap;
                    
                    yelpToApplicationCategoryMap["food"] = "coffee";
                    yelpToApplicationCategoryMap["restaurants"] = "food";
                    yelpToApplicationCategoryMap["nightlife"] = "nightlife";
                    yelpToApplicationCategoryMap["arts"] = "arts";
                    yelpToApplicationCategoryMap["galleries"] = "arts";
                    yelpToApplicationCategoryMap["eventservices"] = "arts";
                    yelpToApplicationCategoryMap["venues"] = "arts";
                    yelpToApplicationCategoryMap["hotelstravel"] = "hotel";
                    yelpToApplicationCategoryMap["active"] = "park";
                    yelpToApplicationCategoryMap["financialservices"] = "bank";
                    
                    return yelpToApplicationCategoryMap;
                }
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    
//                  categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Meeting Rooms", MEETING_ROOM_CATEGORY_NAME, true, "meetingroom", showCategoriesInSearchMenu));

                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Around Me", "",false, "aroundme", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee",false, "coffee", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurants",false, "food", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "nightlife",false, "nightlife", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museums",false, "arts", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotels",false, "hotel", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "parks",false, "park", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "financialservices",false, "bank", true));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Sports", "active",false, "active", false));
                    return categories;
                }
                
                std::vector<std::string> GetCategories()
                {
                    std::vector<std::string> categories;
                    categories.push_back("");
                    categories.push_back("coffee");
                    categories.push_back("restaurants");
                    categories.push_back("nightlife");
                    categories.push_back("museums");
                    categories.push_back("hotels");
                    categories.push_back("parks");
                    categories.push_back("financialservices");
                    categories.push_back("active");
                    return categories;
                }
            }
        }
    }
}
