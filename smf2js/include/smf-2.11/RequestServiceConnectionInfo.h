
#ifndef SMF_ARS_CONNECTIONINFO_H
#define SMF_ARS_CONNECTIONINFO_H

#include <string>
//PR: SMF_REQ00024 =>

namespace smf{
	
	class RequestServiceConnectionInfo{

	public:

		enum InfoTypes{
			ExternalIp,
			LocalIp,
			HostName,

			Unknown		//provide this because we expect to add other info

		};

		RequestServiceConnectionInfo();
		RequestServiceConnectionInfo(RequestServiceConnectionInfo::InfoTypes type, const char* value);

		unsigned short Type() const;
		const std::string& String() const;
	private:
		//use the compiler generated copy etc...

		std::string information;
		RequestServiceConnectionInfo::InfoTypes type;

	};


}
//PR: SMF_REQ00024 <=

#endif