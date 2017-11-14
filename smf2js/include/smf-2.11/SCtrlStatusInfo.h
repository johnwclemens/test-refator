
#ifndef SMF_SCTRLSTATUSINFO_H
#define SMF_SCTRLSTATUSINFO_H

#include <string>

namespace smf{

	class SCtrlStatusInfo{

	public:
		SCtrlStatusInfo();
		SCtrlStatusInfo(const std::string& statusIndicator, bool isHealthy, unsigned int value);

		const std::string& Indicator() const;
		bool IsHealthy() const;
		unsigned int Value()	const;

	private:

		std::string statusIndicator;
		bool isHealthy;
		unsigned int value;

	};

}
#endif