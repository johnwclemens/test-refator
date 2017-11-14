#ifndef SCTRLSERVICEREQUESTHANDLEREXT1_H
#define SCTRLSERVICEREQUESTHANDLEREXT1_H

#include "SCtrlServiceRequestHandler.h"

namespace smf{

	class SCtrlServiceRequestHandlerExt1
		: public SCtrlServiceRequestHandler
	{
	public:

		virtual ~SCtrlServiceRequestHandlerExt1() {};

		class ScheduleApplicationStartWithMonitoringNotSupported:
		public smf::Error
		{
		public:
			ScheduleApplicationStartWithMonitoringNotSupported()
				:smf::Error("The server does not support scheduling application start with monitoring"){
			}

		};

		//! \brief Use this function to add/modify the StartWithMonitoring schedule of application
		//!        The process started by this function will be monitored by SMF and stopped by SMF when SMF stops
		//! \param schedule				The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName				The name of the application. This is not necessary to match the executable name
		//! \param appPath				The full file path of application executable
		//! \param isCriticalProcess	If this is a critical process, a GMI alert will be sent if this process is dead.
		//!								The SMF health status will also report unhealthy if a critical process is not running.
		//! \param workingDirectory		The working directory to start the process
		//! \param processorAffinity	The logical processor indexes that will be used by the application process.
		//!								If this is empty, the process will use all the available processors.
		//! \param startArgs			The arguments used to start the application
		//! \param stopEvent			The event name to trigger the application to stop.
		//!								If this is empty, SMF will kill the process directly when it needs to terminate the process
		//! \param stopCmd				The command to trigger the application to stop. This can be empty. Either the stopEvent or stopCmd can be used.
		//!								If both are provided, only the stopEvent will be used.
		//! \param restartLimit			The maximum restart number for this application. It can be 0 (infinite).
		//! \param rebootIfRestartLimitReached Whether a system reboot will be triggered when restart limit is reached.
		//! \param restartCountTimeWindow  Only restarts happened within this time window will be counted.
		//! \param instanceID			The ID used to identify that application
		//! \param identifier			This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationStartWithMonitoring(const smf::SCtrlSchedule& schedule, const std::string& appName, const std::string& appPath,
												bool isCriticalProcess, const std::string& workingDirectory, const std::vector<unsigned short>& processorAffinity,
												const std::string& startArgs, const std::string& stopEvent, const std::string& stopCmd,
												unsigned int restartLimit, bool rebootIfRestartLimitReached, unsigned int restartCountTimeWindow,
												IdentifierType instanceID, IdentifierType identifier) =0;

	
	};
}

#endif
