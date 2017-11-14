#ifndef SCTRLTASKINFOEXT1_H
#define SCTRLTASKINFOEXT1_H

#include "SCtrlTaskInfo.h"

namespace smf {
	class SCtrlTaskInfoExt1
		: public SCtrlTaskInfo
	{
	public:
		SCtrlTaskInfoExt1();

		//for SMF or system task
		SCtrlTaskInfoExt1(smf::SCtrlMessage::TaskFunction function,
			smf::SCtrlMessage::TaskType type,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID);

		//for Application task with startArgs
		SCtrlTaskInfoExt1(const std::string& appName, 
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
		SCtrlTaskInfoExt1(const std::string& appName, 
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		//for ApplicationStartWithMonitoring with startArgs
		SCtrlTaskInfoExt1(const std::string& appName, 
			const std::string& appPath,
			bool isCriticalProcess,
			const std::string& workingDirectory,
			unsigned int restartLimit,
			bool rebootIfRestartLimitReached,
			unsigned int restartCountTimeWindow,
			const std::vector<unsigned short> processorAffinity,
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& startArgs,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		//for ApplicationStartWithMonitoring without startArgs
		SCtrlTaskInfoExt1(const std::string& appName, 
			const std::string& appPath,
			bool isCriticalProcess,
			const std::string& workingDirectory,
			unsigned int restartLimit,
			bool rebootIfRestartLimitReached,
			unsigned int restartCountTimeWindow,
			const std::vector<unsigned short> processorAffinity,
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		//for ApplicationStartWithMonitoring with startArgs and processorAffinityMask
		SCtrlTaskInfoExt1(const std::string& appName, 
			const std::string& appPath,
			bool isCriticalProcess,
			const std::string& workingDirectory,
			unsigned int restartLimit,
			bool rebootIfRestartLimitReached,
			unsigned int restartCountTimeWindow,
			unsigned int processorAffinityMask,
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& startArgs,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		//for ApplicationStartWithMonitoring without startArgs and processorAffinityMask
		SCtrlTaskInfoExt1(const std::string& appName, 
			const std::string& appPath,
			bool isCriticalProcess,
			const std::string& workingDirectory,
			unsigned int restartLimit,
			bool rebootIfRestartLimitReached,
			unsigned int restartCountTimeWindow,
			unsigned int processorAffinityMask,
			unsigned int id, 
			smf::SCtrlMessage::TaskFunction function,
			const std::string& cmd,
			const std::string& stopEvent,
			unsigned int stopEventID,
			const SCtrlSchedule& schedule,
			const SCtrlTaskID& taskID,
			const std::string& connectionInfo = "");

		virtual ~SCtrlTaskInfoExt1() {}

		SCtrlTaskInfoExt1& operator=(const SCtrlTaskInfo& that);

		const std::string& AppPath() const;
		bool IsCriticalProcess() const;
		const std::string& WorkingDirectory() const;
		unsigned int RestartLimit() const;
		bool RebootIfRestartLimitReached() const;
		unsigned int RestartCountTimeWindow() const;
		const std::vector<unsigned short>& ProcessorAffinity() const;
		unsigned int ProcessorAffinityMask() const;




	private:
		std::string appPath;
		bool isCriticalProcess;
		std::vector<unsigned short> processorAffinity;
		unsigned int processorAffinityMask;
		std::string workingDirectory;
		unsigned int restartLimit;
		bool rebootIfRestartLimitReached;
		unsigned int restartCountTimeWindow;
	};
}

#endif