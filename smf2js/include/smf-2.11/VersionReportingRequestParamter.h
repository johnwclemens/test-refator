#ifndef VERSIONREPORTINGREQUESTPARAMETER
#define VERSIONREPORTINGREQUESTPARAMETER

#include <string>

namespace smf {

    class VersionReportingRequestParamter {
    public:

        enum ActionsOnExist {
            None,
            Overwrite,
            Duplicate,
        };

        VersionReportingRequestParamter();
        ~VersionReportingRequestParamter();

        void SetAppName(const std::string &appName);
        void SetAppVersion(const std::string &version);
        void SetIsServiceApp(bool isServiceApp);

        void SetRootAppName(const std::string &rootAppName);
        void SetPackageName(const std::string &packageName);
        void SetPackageVersion(const std::string &packageVersion);

        void SetActionsOnExist(ActionsOnExist actionOnExist);

        const std::string &GetAppName() const;
        const std::string &GetAppVersion() const;
        bool IsServiceApp() const;

        const std::string &GetRootAppName() const;
        const std::string &GetPackageName() const;
        const std::string &GetPackageVersion() const;

        ActionsOnExist GetActionsOnExist() const;

    private:
        std::string appNameStr;
        std::string pkgNameStr;
        std::string rootAppNameStr;
        std::string pkgVersionStr;
        std::string appVersionStr;
        bool isService;
        ActionsOnExist action;
    };

}

#endif