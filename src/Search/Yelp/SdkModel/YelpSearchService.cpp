// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include <sstream>
#include "YelpSearchService.h"
#include "ISearchResultParser.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "Logger.h"
#include "IYelpSearchQueryFactory.h"
#include "IYelpSearchQuery.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesParser.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpSearchService::YelpSearchService(IYelpSearchQueryFactory& searchQueryFactory,
                                                     Search::SdkModel::ISearchResultParser& searchResultParser,
                                                     Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                     const std::vector<std::string>& availableCategories)
                : Search::SdkModel::SearchServiceBase(availableCategories)
                , m_searchQueryFactory(searchQueryFactory)
                , m_searchResultParser(searchResultParser)
                , m_networkCapabilities(networkCapabilities)
                , m_currentQueryModel("", false,false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0.f)
                , m_poiSearchCallback(this, &YelpSearchService::HandleSearchResponse)
                , m_pCurrentRequest(NULL)
                , m_hasActiveQuery(false)
                {
                }
                
                YelpSearchService::~YelpSearchService()
                {
                    CancelInFlightQueries();
                }
                
                void YelpSearchService::CancelInFlightQueries()
                {
                    if(m_pCurrentRequest != NULL)
                    {
                        m_pCurrentRequest->Cancel();
                        m_pCurrentRequest = NULL;
                    }
                    
                    if(m_hasActiveQuery)
                    {
                        m_hasActiveQuery = false;
                        std::vector<Search::SdkModel::SearchResultModel> results;
                        ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, results);
                    }
                }
                
                void YelpSearchService::PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& searchQuery)
                {
                    CancelInFlightQueries();
                    
                    ExecuteQueryPerformedCallbacks(searchQuery);
                    if(m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi())
                    {
                        ExecutQueryResponseReceivedCallbacks(searchQuery, std::vector<Search::SdkModel::SearchResultModel>());
                        return;
                    }
                    
                    m_currentQueryModel = searchQuery;
                    m_hasActiveQuery = true;
                    
                    // We instantiate a request with the factory, but although we 'own' it, we do not delete it.
                    // The request is async and cleans itself up after it has posted a result back. This is due to
                    // the details of how cancellation works with the request lifecycle for our platform specific
                    // implementations. We keep a pointer to the current request so we can change the active request,
                    // have a NULL request, etc.
                    m_pCurrentRequest = m_searchQueryFactory.CreateYelpSearchForQuery(m_currentQueryModel, m_poiSearchCallback);
                    m_pCurrentRequest->Dispatch();
                }
                
                
                void YelpSearchService::HandleSearchResponse()
                {
                    Eegeo_ASSERT(m_pCurrentRequest != NULL, "Yelp search request must have been performed");
                    
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    
                    if(m_pCurrentRequest->IsSucceeded())
                    {
                        const std::string& response(m_pCurrentRequest->ResponseString());
                        m_searchResultParser.ParseSearchResults(response, results);
                    }
                    
                    m_pCurrentRequest = NULL;
                    m_hasActiveQuery = false;
                    ExecutQueryResponseReceivedCallbacks(m_currentQueryModel, results);
                }
                
                void YelpSearchService::PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                              Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
                {
                    m_searchQueryFactory.CreateYelpSearchForSpecificLocation(outdatedSearchResult, callback)->Dispatch();
                }
            }
        }
    }
}

