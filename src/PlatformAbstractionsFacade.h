// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPlatformAbstractionModule.h"
#include "ExampleAppCustomWebLoadRequestFactory.h"
#include "NetIncludes.h"
#include "Tasks.h"

namespace ExampleApp
{
    class PlatformAbstractionsFacade: public Eegeo::Modules::IPlatformAbstractionModule, private Eegeo::NonCopyable
    {
    private:
        Eegeo::Modules::IPlatformAbstractionModule& m_wrappedPlatformAbstractions;
        Net::SdkModel::ExampleAppCustomWebLoadRequestFactory* m_pWebLoadRequestFactory;
        Net::SdkModel::ExampleAppCustomWebLoadRequestFactory* m_pPlatformWebLoadRequestFactory;
        
    public:
        PlatformAbstractionsFacade(Eegeo::Modules::IPlatformAbstractionModule& wrappedPlatformAbstractions,
                                   Net::SdkModel::INetworkCapabilities& networkCapabilities);
        
        ~PlatformAbstractionsFacade();
        
        Eegeo::Helpers::ITextureFileLoader& GetTextureFileLoader() const;
        Eegeo::Web::IWebLoadRequestFactory& GetWebLoadRequestFactory() const;
        Eegeo::Web::IWebLoadRequestFactory& GetPlatformWebLoadRequestFactory() const;
        Eegeo::Web::IWebProxySettings& GetProxySettings() const;
        Eegeo::Helpers::IHttpCache& GetHttpCache() const;
        Eegeo::Helpers::IFileIO& GetFileIO() const;
        Eegeo::Helpers::UrlHelpers::IUrlEncoder& GetUrlEncoder() const;
        Eegeo::Web::IConnectivityService& GetConnectivityService() const;
        Eegeo::Concurrency::Tasks::IWorkPool& GetWorkPool() const;
       
        void OnPause();
        void Update();
        void OnResume();
    };
}
