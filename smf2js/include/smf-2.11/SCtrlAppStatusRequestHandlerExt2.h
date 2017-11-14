#ifndef SCtrlAppStatusRequestHandlerExt2_H
#define SCtrlAppStatusRequestHandlerExt2_H

#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "Types.h"
#include "SCtrlSchedule.h"
#include "SCtrlTaskID.h"
#include "SCtrlAppStatusRequestHandlerExt1.h"

#include <string>

//! SCTRL Service - AppStatus Request Handler
//! This interface is for the remote client to make register the process and publish heartbeat
//! 

namespace smf{
	class SCtrlAppStatusRequestHandlerExt2
		: public SCtrlAppStatusRequestHandlerExt1
	{
	public:
		virtual ~SCtrlAppStatusRequestHandlerExt2() {}

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
		//! \exception smf::Error See SCtrlAppStatusRequestHandler.h for more specific exceptions.
		//! \param appName	The name of the application
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void NotifyCleanShutdown(const std::string& appName) = 0;

		//! \brief Notify SMF to check and reset the clean shutdown flag.
		//! \exception smf::Error See SCtrlAppStatusRequestHandler.h for more specific exceptions.
		//! \param appName	The name of the application
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void CheckAndResetCleanShutdown(const std::string& appName) = 0;
		
		//! \brief Notify SMF that the application is invalid.
		//! \exception smf::Error See SCtrlAppStatusRequestHandler.h for more specific exceptions.
		//! \param appName	The name of the application for cross-checking with PID (set to empty to skip the checking)
		//! \param PID	The PID used to indentify the running process. The PID can be obtained by QueryProcessStatus function call.
		//! \param WaitTimeoutInSec	The time to wait for the invalid application process to stop (0=infinity)
		//! \note	The function is thread safe.
		virtual void SetAppAsInvalid(const std::string& appName, unsigned int PID, unsigned int WaitTimeoutInSec, UnsignedInt identifier) = 0;		
	};
}
#endif