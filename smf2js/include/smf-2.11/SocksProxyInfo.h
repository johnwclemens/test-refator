
#ifndef SMF_SOCKSPROXYINFO_H
#define SMF_SOCKSPROXYINFO_H

#include <utility>
#include <string>

namespace smf{

	class SocksProxyInfo{

	public:
		SocksProxyInfo(){}
		virtual ~SocksProxyInfo(){}

		virtual std::string ProxyCommand(const char* remoteServer, unsigned short remotePort, unsigned short localProxyPort) const = 0;

		virtual std::pair<unsigned short, unsigned short> PortRange() const = 0;
		virtual const char* ProxyServerAddress() const = 0;
		virtual const char* UserId() const = 0;

	private:
		SocksProxyInfo(const SocksProxyInfo&);
		SocksProxyInfo& operator=(const SocksProxyInfo&);

	};

}

#endif