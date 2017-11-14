#ifndef PACKAGEINFORMATION
#define PACKAGEINFORMATION

#include <string>

namespace smf{

    class PackageInformation
    {
    public:
        PackageInformation(const std::string &packageName = "", 
                            const std::string &rootAppName = "", 
                            const std::string &version = "");
        ~PackageInformation();
        const char* Name();
        const char* RootApplication();
        const char* Version();
    private:
        std::string m_packageName;
        std::string m_rootAppName;
        std::string m_version;
    };

}

#endif

