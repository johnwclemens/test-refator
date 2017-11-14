#ifndef SCTRLSERVICERESPONSEHANDLER_H
#define SCTRLSERVICERESPONSEHANDLER_H

#include "SCtrlTaskInfo.h"
#include "SCtrlProcessStatusInfo.h"
#include "SCtrlTaskInfoList.h"
#include "SCtrlProcessStatusInfoList.h"
#include "SCtrlTaskID.h"
#include "SCtrlStatusInfo.h"
#include "ConstantVector.h"

#include <vector>
#include <string>


//! SCtrl Service - Response Handler
//! This is the interface SCtrl client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the SCtrl client services when it  calls OpenSCtrlRequestChannel
//!
//! Please look at enum FailureReason in SCtrlMessage.h to get the error codes from SCtrl
namespace smf{
	class SCtrlServiceResponseHandler
	{
	public:
		typedef smf::ConstantVector<SCtrlStatusInfo> StatusReasons;
		typedef unsigned int IdentifierType;
		typedef unsigned short ReasonType;

		virtual ~SCtrlServiceResponseHandler(){}

		//! \brief This is how you receive any positive responses to your request
		//! For sender: Callback functions from smf::SCtrlServiceRequestHandler:
		//! ScheduleApplicationStart
		//! ScheduleApplicationStartWithMonitoring
		//! ScheduleApplicationStop
		//! ScheduleApplicationRestart
		//! ScheduleSmfRestart
		//! ScheduleSystemStop
		//! ScheduleSystemRestart
		//! TriggerTask
		//! ClearTask
		//! RemoveTask
		//! \param taskID	The smf::SCtrlTaskID object stored the schedule task ID. 
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportRequestSuccess(const smf::SCtrlTaskID& taskID, IdentifierType identifier) = 0;
		
		//! \brief This is how you receive any negative responses to your request
		//! For sender: Callback functions from smf::SCtrlServiceRequestHandler:
		//! ScheduleApplicationStart
		//! ScheduleApplicationStartWithMonitoring
		//! ScheduleApplicationStop
		//! ScheduleApplicationRestart
		//! ScheduleSmfRestart
		//! ScheduleSystemStop
		//! ScheduleSystemRestart
		//! TriggerTask
		//! ClearTask
		//! RemoveTask
		//! \param reason	Reason of the failure. Refer to SCtrlMessage.h for possible failure reasons
		//! \param info	Extra failure information.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportRequestFailure(ReasonType reason, const std::string& info, IdentifierType identifier) = 0;
		
		//! \brief This is how you receive any responses to task query request
		//! For sender: Callback functions from smf::SCtrlServiceRequestHandler:
		//! QueryTaskByTaskID
		//! QueryTaskByTaskType
		//! \param taskInfoList The smf::SCtrlTaskInfoList object stored the task information
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportTaskInfo(const smf::SCtrlTaskInfoList& taskInfoList, IdentifierType identifier) = 0;
		
		//! \brief This is how you receive any responses to process status query request
		//! For sender: Callback functions from smf::SCtrlServiceRequestHandler:QueryProcessStatus
		//! \param processStatusList The smf::SCtrlProcessStatusInfoList object stored the process status information
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportProcessStatus(const smf::SCtrlProcessStatusInfoList& processStatusList, IdentifierType identifier) = 0;

		//! \brief This is how you receive any responses to an overall status query request (smf::SCtrlServiceRequestHandler::QueryStatus)
		//! \param isHealthy       The overall status of the server
		//! \param statusReasons   Individual status indicators
		//! \param identifier      Your identifier
		virtual void ReportStatus(bool isHealthy, const StatusReasons& statusReasons, IdentifierType identifier) {
		}
		
		//! \brief This is how you receive any failure responses to process status query request
		//! \param reason	Reason of the failure. Refer to SCtrlMessage.h for possible failure reasons
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportFailure(ReasonType reason, IdentifierType identifier) = 0;
		
	};
}
#endif