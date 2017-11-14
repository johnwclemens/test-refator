#ifndef SCTRLPROCESSSTATUSINFO_H
#define SCTRLPROCESSSTATUSINFO_H

#include <string>
#include <vector>

namespace smf{
	class SCtrlProcessStatusInfo{
	
	public:
		SCtrlProcessStatusInfo();

		SCtrlProcessStatusInfo(std::string& processName,
			std::string& applicationName,
			std::string& processDescription,
			unsigned int pid,
			bool statusHealth,
			bool smfMonitored,
			bool hbPublished,
			unsigned int hbDiffInSec);



		virtual ~SCtrlProcessStatusInfo(){};

		const std::string& ProcessName() const;
		const std::string& ApplicationName() const;
		const std::string& ProcessDescription() const;
		const unsigned int PID() const;
		const bool StatusHealth() const;
		const bool IsHeartBeatPublished() const;
		const bool SmfMonitored()	const;
		const unsigned int HeartBeatCountDiffInSec() const;

	private:
		std::string processName;
		std::string applicationName;
		std::string processDescription;
		unsigned int pid;
		bool smfMonitored;
		bool statusHealth;
		bool hbPublished;
		unsigned int hbDiffInSec;
	};
}

#endif