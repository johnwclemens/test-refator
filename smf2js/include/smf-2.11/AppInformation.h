#ifndef APPINFORMATION
#define APPINFORMATION

#include <string>

namespace smf{

    class AppInformation
    {
    public:
        AppInformation(const std::string &appName = "", 
                       const std::string &version = "",
                       bool isServiceApp = true);
        ~AppInformation(void);
         const char* Name();
        const char* Version();
        bool IsService();
    private:
        std::string m_appName;
        std::string m_version;
        bool m_isServiceApp;
    };

}

#endif
