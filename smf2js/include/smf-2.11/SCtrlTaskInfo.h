#ifndef SCTRLTASKINFO_H
#define SCTRLTASKINFO_H

#include "SCtrlSchedule.h"
#include "SCtrlMessage.h"
#include "SCtrlTaskID.h"
#include <vector>


namespace smf{
	class SCtrlTaskInfo { 
	
	public:
		SCtrlTaskInfo();

		//for SMF or system task
		SCtrlTaskInfo(smf::SCtrlMessage::TaskFunction function,
			smf::SCtrlMessage::TaskType type,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID);

		//for Application task with startArgs
		SCtrlTaskInfo(const std::string& appName, 
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& startArgs,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		//for Application task without startArgs. It will use system default for that application if available.
		SCtrlTaskInfo(const std::string& appName, 
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		virtual ~SCtrlTaskInfo(){}

		const SCtrlTaskID& TaskID() const;
		const std::string& AppName() const;
		const unsigned int ID() const;
		const smf::SCtrlMessage::TaskFunction Function() const;
		const smf::SCtrlMessage::TaskType Type() const;
		const std::string& Cmd() const;
		const std::string& StartArgs() const;
		const std::string& StopEvent() const;
		unsigned int StopEventID() const;
		bool HasStartArgs() const;
		
		const SCtrlSchedule& Schedule() const;

		const std::string& ConnectionInfo() const;
	private:

		SCtrlTaskID taskID;
		std::string appName;
		unsigned int id;
		smf::SCtrlMessage::TaskFunction function;
		smf::SCtrlMessage::TaskType type;
		std::string cmd;
		std::string startArgs;
		std::string stopEvent;
		unsigned int stopEventID;
		bool hasStartArgs;

		SCtrlSchedule schedule;

		std::string connectionInfo;
		
	};
}

#endif