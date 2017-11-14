#ifndef SCTRL_ENDPOINT_DETECTION_HEARTBEAT_H
#define SCTRL_ENDPOINT_DETECTION_HEARTBEAT_H

#include <string>
#include "Types.h"
#include "Error.h"

namespace smf 
{
    class TimeStamp;

    //! This SCtrlEndpointDetectionHeartbeat class represents the heartbeat 
    //! received, not thread safe. This class will parse the heartbeat 
    //! once when getting the values.
    class SCtrlEndpointDetectionHeartbeat
    {
    public:
        //! SMF Health Status Representation
        enum SMFHealthStatus
        {
            SMFHealthStatusHealthy = 0,      //!< SMF is healthy
            SMFHealthStatusUnhealthy = 1,    //!< SMF is not healthy
            SMFHealthStatusUnknown = 2       //!< SMF health status is unknown
        };

        //! Representation of the existence of GMI Event Agent (such 
        //! as TEC Adapter)
        enum GMIEventAgentExistence
        {
            EventAgentExists = 0,            //!< Exists
            EventAgentNotExists = 1,         //!< Not Exists
            EventAgentExistenceUnknown = 2   //!< Agent Existence unknown
        };

    public:
		SCtrlEndpointDetectionHeartbeat(SCtrlEndpointDetectionHeartbeat * pHeartbeat);
        virtual ~SCtrlEndpointDetectionHeartbeat(void);
		

    public:
        //! \return The version of the heartbeat.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual unsigned char           Version() const;

        //! \return The time of the heartbeat.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        //! \remark Include TimeStamp.h
        virtual TimeStamp               Time() const;

        //! \return The SMF health status of the heartbeat.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual enum SMFHealthStatus         SMFHealthStatus() const;        

        //! \return The GMI Event Agent existence (such as TEC Adapter)
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual enum GMIEventAgentExistence  GMIEventAgentExistence() const;
		
        //! \return The IP of the heartbeat sender.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual UnsignedInt             Ip() const;

        //! \return The size of the heartbeat buffer.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual UnsignedInt             BufferSize() const;

        //! \return The raw buffer.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual const char *            Buffer() const;

        //! \param  pos     The position.
        //! \return The value of the buffer at the specified position.
        //! \note   SCtrlEndpointDetectionHeartbeat is not thread safe.
        virtual const unsigned char &   operator[] (unsigned int pos) const;
		
	protected:
		SCtrlEndpointDetectionHeartbeat();

	private:
		SCtrlEndpointDetectionHeartbeat * m_pHeartbeat;		
		
		SCtrlEndpointDetectionHeartbeat(const SCtrlEndpointDetectionHeartbeat &);
		SCtrlEndpointDetectionHeartbeat & operator =(const SCtrlEndpointDetectionHeartbeat &);
    };

};
#endif //SCTRL_ENDPOINT_DETECTION_HEARTBEAT_H
