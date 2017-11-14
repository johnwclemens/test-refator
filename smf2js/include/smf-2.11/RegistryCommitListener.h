
#ifndef SMF_REGISTRYCOMMITLISTENER_H
#define SMF_REGISTRYCOMMITLISTENER_H

#include <string>
#include <vector>

#ifndef WIN32
typedef char BYTE;
#endif

namespace smf{
	class RegistryCommitListener
	{
	public:
	    virtual void ValueCommitted(
			const std::string &sRegistryPath, 
            const void* pBinData, 
			unsigned int iBinSize,
			const std::vector<BYTE>& oldBinData) = 0;

	    virtual void ValueCommitted(
            const std::string &sRegistryPath, 
            const char* pStringData,
            const std::vector<BYTE>& oldBinData) = 0;

		virtual void ValueCommitted(
            const std::string &sRegistryPath, 
            const char* pStringData,
			const std::string & oldStringData) = 0;

		virtual void ValueCommitted(
            const std::string &sRegistryPath, 
            int iIntegerData,
            const std::vector<BYTE>& oldBinData) = 0;

		virtual void ValueCommitted(
            const std::string &sRegistryPath, 
            int iIntegerData,
            int iOldIntegerData) = 0;

		virtual void Completed() = 0;
		virtual void Started() = 0;

		virtual ~RegistryCommitListener() {}
	};

}

#endif