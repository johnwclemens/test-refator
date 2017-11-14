#pragma once
#include "SCtrlEndpointDetectionHeartbeat.h"
#include "ConstantVector.h"

namespace smf
{

    //! This SCtrlEndpointDetectionHeartbeatExt1 class represents the heartbeat
    //! (including version 1 and version 2) received, not thread safe. This class
    //! will parse the heartbeat once when getting the value.
    class SCtrlEndpointDetectionHeartbeatExt1 :
        public smf::SCtrlEndpointDetectionHeartbeat
    {
    public:
        //! Node Live/Standby status Representation.
        enum NodeStatus
        {
            NodeStatusUnknown = 0,					//!< Node status is unknown.
            LockedStandby,							//!< Node status is locked standby.
            LockedLive,								//!< Node status is locked live.
            Standby,								//!< Node status is standby.
            Live,									//!< Node status is live.
            NodeStatusUndetermined = 0xFFFFFFFFU    //!< Node status is undetermined, may be caused by network error
        };

        enum HealthStatusType
        {
            TypeUnknown = 0,
            TypeGenericHealthCheck,
            TypeSMFHealthStatus
        };

        SCtrlEndpointDetectionHeartbeatExt1(SCtrlEndpointDetectionHeartbeatExt1 * pHeartbeat);
        virtual ~SCtrlEndpointDetectionHeartbeatExt1(void);
        
        //! \return True if the Live Standby Entity List is requested, 
        //!         otherwise false.
        //! \note   SCtrlEndpointDetectionHeartbeatExit is not thread safe
        virtual bool IsLiveStandbyEntityListRequested() const;

        //! \return The list of live/standby status of the entities.
        //! \note   SCtrlEndpointDetectionHeartbeatExit is not thread safe
        //! \remark Include ConstantVector.h
        virtual const smf::ConstantVector<NodeStatus> & EntitiesLiveStandbyStatus() const;

        //! \return The type of the Health Status. 
        //! \note   SCtrlEndpointDetectionHeartbeatExit is not thread safe
        virtual enum HealthStatusType HealthStatusType() const;

    protected:
        SCtrlEndpointDetectionHeartbeatExt1();

    private:
        SCtrlEndpointDetectionHeartbeatExt1(const SCtrlEndpointDetectionHeartbeatExt1 &);
        SCtrlEndpointDetectionHeartbeatExt1 & operator =(const SCtrlEndpointDetectionHeartbeatExt1 &);

        SCtrlEndpointDetectionHeartbeatExt1 * m_pHeartbeatExt1;
    };
};