#ifndef SCTRLSERVICEREQUESTHANDLER_H
#define SCTRLSERVICEREQUESTHANDLER_H


#include "SCtrlServiceResponseHandler.h"
#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "SCtrlSchedule.h"
#include "SCtrlTaskID.h"

#include <vector>
#include <string>

//! SCTRL Service - Request Handler
//! This interface is for the remote client to make requests for process control
//! 

namespace smf{
	class SCtrlServiceRequestHandler
	{
	public:
		typedef unsigned int IdentifierType;
		typedef std::vector<smf::SCtrlTaskID> SCtrlTaskIDList;
		typedef std::vector<std::string> ProcessesList;

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
	
		virtual ~SCtrlServiceRequestHandler() {}

		
		//! \brief Use this function to add/modify the Start schedule of application
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param startArgs	The arguments used to start the application
		//! \param instanceID	The ID used to indentify that application
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationStart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												const std::string& startArgs, IdentifierType instanceID, IdentifierType identifier) =0;

		
		//! \brief Use this function to add/modify the Start schedule of application
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param instanceID	The ID used to indentify that application
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationStart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												IdentifierType instanceID, IdentifierType identifier) =0;


		//! \brief Use this function to add/modify the stop schedule of application running in window environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The application name
		//! \param stopEvent	The Event name to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationStop(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												const std::string& stopEvent, IdentifierType PID, IdentifierType identifier) =0; 
		
		//! \brief Use this function to add/modify the stop schedule of application running in Solaris environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The application name
		//! \param stopEventID	The Event ID to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationStop(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												IdentifierType stopEventID, IdentifierType PID, IdentifierType identifier) =0; 

		
		//! \brief Use this function to add/modify the restart schedule of application running in window environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param startArgs	The arguments used to start the application
		//! \param stopEvent	The Event name to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationRestart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												const std::string& startArgs, const std::string& stopEvent, IdentifierType PID, IdentifierType identifier) =0;
		
		//! \brief Use this function to add/modify the restart schedule of application running in window environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param stopEvent	The Event name to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationRestart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												const std::string& stopEvent, IdentifierType PID, IdentifierType identifier) =0;

		
		//! \brief Use this function to add/modify the restart schedule of application running in Solaris environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param startArgs	The arguments used to start the application
		//! \param stopEvent	The Event name to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationRestart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												const std::string& startArgs, IdentifierType stopEvent, IdentifierType PID, IdentifierType identifier) =0;

		//! \brief Use this function to add/modify the restart schedule of application running in Solaris environment
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param appName	The full file path of application
		//! \param stopEvent	The Event name to trigger the process to exit
		//! \param PID	The PID used to indentify the runnign process. The PID can be obtained by QueryProcessStatus function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleApplicationRestart(const smf::SCtrlSchedule& schedule, const std::string& appName, 
												IdentifierType stopEvent, IdentifierType PID, IdentifierType identifier) =0;


		//! \brief Use this function to add/modify the restart schedule of smf
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleSmfRestart(const smf::SCtrlSchedule& schedule, IdentifierType identifier) =0;

		
		//! \brief Use this function to add/modify the system stop schedule
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleSystemStop(const smf::SCtrlSchedule& schedule, IdentifierType identifier) =0;


		//! \brief Use this function to add/modify the system restart schedule
		//! \param schedule	The smf::SCtrlSchedule object, which stores the schedule information.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ScheduleSystemRestart(const smf::SCtrlSchedule& schedule, IdentifierType identifier) =0;

		//! \brief Use this function to enable the trigger of schedule
		//! \param taskID	The smf::SCtrlTaskID object, which stores the ID of schedule task. The taskID can be obtained by QueryTaskByTaskType/QueryTaskByTaskID function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void TriggerTask(const smf::SCtrlTaskID& taskID, IdentifierType identifier) =0;
		
		//! \brief Use this function to disable the trigger of schedule
		//! \param taskID	The smf::SCtrlTaskID object, which stores the ID of schedule task. The taskID can be obtained by QueryTaskByTaskType/QueryTaskByTaskID function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void ClearTask(const smf::SCtrlTaskID& taskID, IdentifierType identifier) =0;
		
		//! \brief Use this function to remove the schedule
		//! \param taskID	The smf::SCtrlTaskID object, which stores the ID of schedule task. The taskID can be obtained by QueryTaskByTaskType/QueryTaskByTaskID function call.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportRequestSuccess/ReportRequestFailure function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void RemoveTask(const smf::SCtrlTaskID& taskID, IdentifierType identifier) =0;


		//! \brief Use this function to query the schedule task by smf::SCtrlTaskID object
		//! \param taskIDList	The list stored the smf::SCtrlTaskID objects for querying the schedule task information. Empty list means querying ALL schedule task infornation.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportTaskInfo function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void QueryTaskByTaskID(const smf::SCtrlServiceRequestHandler::SCtrlTaskIDList& taskIDList, IdentifierType identifier) =0;
		
		//! \brief Use this function to query the schedule task by taskType
		//! \param type	The task type defined in smf::SCtrlMessage::TaskType
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportTaskInfo function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void QueryTaskByTaskType(smf::SCtrlMessage::TaskType type, IdentifierType identifier) =0;
		
		//! \brief Use this function to query the process status
		//! \param processesList	The list stored the application name for querying the status. Empty list mean query ALL process status.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportProcessStatus function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void QueryProcessStatus(const smf::SCtrlServiceRequestHandler::ProcessesList& processesList, IdentifierType identifier) =0;
	
		//! \brief Use this function to query the system health status
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \post The values will be reported back through your implementation of the smf::SCtrlServiceResponseHandler in the ReportStatus function
		//! \exception smf::Error See SCtrlServiceRequestHandler.h for more specific exceptions.
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		virtual void QueryStatus(IdentifierType identifier) = 0;

	};
}

#endif