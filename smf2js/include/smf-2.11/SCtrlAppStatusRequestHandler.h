#ifndef SCTRLAPPSTATUSREQUESTHANDLER_H
#define SCTRLAPPSTATUSREQUESTHANDLER_H

#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "SCtrlSchedule.h"
#include "SCtrlTaskID.h"

#include <string>

//! SCTRL Service - AppStatus Request Handler
//! This interface is for the remote client to make register the process and publish heartbeat
//! 

namespace smf{
	class SCtrlAppStatusRequestHandler
	{
	public:
		class ConnectionDropped:
		public smf::Error
		{
		public:
			ConnectionDropped():smf::Error("The connection to the server has been closed or dropped"){
			}

		};

		class SizeLimitExceedsAllocationLimit:
		public smf::Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details):
			smf::Error(details)
			{
				
			}
		};

		class CouldNotGetBuffer:
		public smf::Error
		{
		public:
			CouldNotGetBuffer(unsigned int size):
			smf::Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}

		};


		virtual ~SCtrlAppStatusRequestHandler() {}

		//! \brief Register the application before publishing heartbeat
		//! After the application is registered. It will be monitered by SMF.
		//! The response will be reported back to you through this function.
		//! \param restartArgs		The arguments used to restart the application
		//! \param maxHeartBeatCountDiffInSec			The max. interval between 2 heartbeats. If the different is larger than that value, the status of procss is unhealth. Using 0 for system default
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void Register(const std::string& restartArgs, unsigned int maxHeartBeatCountDiffInSec=0) =0;

		//! \brief Publish the heartbeat to SMF.
		//! \exception smf::Error See SCtrlAppStatusRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void PublishHeartbeat() =0;

		//! \brief Update the health stats to SMF.
		//! \exception smf::Error See SCtrlAppStatusRequestHandler.h for more specific exceptions.
		//! \param status	The health status of the application
		//! \param details	The additional details of health status
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void UpdateHealthStatus(smf::SCtrlMessage::HealthStatus status, const std::string& details = "") =0;
	};
}
#endif