#ifndef SCtrlAppStatusRequestHandlerExt1_H
#define SCtrlAppStatusRequestHandlerExt1_H

#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "SCtrlSchedule.h"
#include "SCtrlTaskID.h"
#include "SCtrlAppStatusRequestHandler.h"

#include <string>

//! SCTRL Service - AppStatus Request Handler
//! This interface is for the remote client to make register the process and publish heartbeat
//! 

namespace smf{
	class SCtrlAppStatusRequestHandlerExt1
		: public SCtrlAppStatusRequestHandler
	{
	public:
		virtual ~SCtrlAppStatusRequestHandlerExt1() {}

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

		//! \brief Notify SMF that the shutdown of the application is a clean shutdown.
		//! \exception smf::Error See SCtrlAppStatusRequestHandlerExt1.h for more specific exceptions.
		//! \param appName	The name of the application
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void NotifyCleanShutdown(const std::string& appName) = 0;

		//! \brief Notify SMF to check and reset the clean shutdown flag.
		//! \exception smf::Error See SCtrlAppStatusRequestHandlerExt1.h for more specific exceptions.
		//! \param appName	The name of the application
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void CheckAndResetCleanShutdown(const std::string& appName) = 0;
	};
}
#endif