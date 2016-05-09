// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"
#include "SearchServiceBase.h"
#include "ICallback.h"
#include "CategorySearchModel.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                class CombinedSearchService
                : public Search::SdkModel::SearchServiceBase
                {
                public:
                    
                    CombinedSearchService(const std::map<std::string, Search::SdkModel::ISearchService*>& searchServices,
                                          AppModes::SdkModel::IAppModeModel& appModeModel);
                    
                    ~CombinedSearchService();
                    
                    bool CanHandleCategory(const std::string& category) const;
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    
                    void OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    
                    
                private:
                    
                    std::map<std::string,Search::SdkModel::ISearchService*> m_searchServices;
                    
                    Eegeo::Helpers::TCallback2<CombinedSearchService,
                                               const Search::SdkModel::SearchQuery&,
                                               const std::vector<Search::SdkModel::SearchResultModel>&> m_searchQueryResponseCallback;
                    
                    int m_pendingResultsLeft;
                    std::vector<Search::SdkModel::SearchResultModel> m_combinedResults;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    bool m_hasActiveQuery;
                    
                };
            }
        }
    }
}
