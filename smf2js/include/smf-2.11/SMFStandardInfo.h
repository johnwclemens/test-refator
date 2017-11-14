//
// Copyright (c) 1999 by Reuters
// All rights reserved.
//
// No portion of this software in any form my be used or 
// reproduced in any manner without written consent from
// Reuters
//
// Author:      Henry Fan
// Descirption: Header file of SMF Standardized information


#ifndef SMFSTANDARDINFO_H
#define SMFSTANDARDINFO_H

#include <string>

namespace smf{

    class SMFStandardInfo
    {
    public:
        SMFStandardInfo();
        virtual ~SMFStandardInfo();
        void SetLocation(const std::string &location);
        void SetSiteType(const std::string &siteType);
        void SetUsage(const std::string &usage);
        void SetServerType(const std::string &serverType);
        void SetServerGroup(const std::string &serverGroup);
        void SetSMFStartTime(const std::string &smfStartTime);
        void SetLastPublishedTime(const std::string &lastPublishedTime);
        void SetCurrentTimeZone(const std::string &currentTimeZone);
        void SetHealthStatus(const std::string &healthStatus);
        void SetLiveStandbyStatus(const std::string &liveStandbyStatus);

        const std::string &GetLocation() const;
        const std::string &GetSiteType() const;
        const std::string &GetUsage() const;
        const std::string &GetServerType() const;
        const std::string &GetServerGroup() const;
        const std::string &GetSMFStartTime() const;
        const std::string &GetLastPublishedTime() const;
        const std::string &GetCurrentTimeZone() const;
        const std::string &GetHealthStatus() const;
        const std::string &GetLiveStandbyStatus() const;
        static const char* KEEP_SSINFO_ENTRY ;
    
    private:
        std::string LocationStr;
        std::string SiteTypeStr;
        std::string UsageStr;
        std::string ServerTypeStr;
        std::string ServerGroupStr;
        std::string SMFStartTimeStr;
        std::string LastPublishedTimeStr;
        std::string CurrentTimeZoneStr;
        std::string HealthStatusStr;
        std::string LiveStandbyStatusStr;
    };

}

#endif // SMFSTANDARDINFO_H
