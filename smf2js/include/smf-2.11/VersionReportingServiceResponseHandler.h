
#ifndef VERSIONREPORTINGSERVICERESPONSEHANDLER_H
#define VERSIONREPORTINGSERVICERESPONSEHANDLER_H

#include "PackageInformation.h"
#include "AppInformation.h"
#include "VersionReportingRequestParamter.h"

#include <vector>
#include <string>


//! Version Reporting Service - Response Handler
//! This is the interface Version Reporting client service uses to update/query version information
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Version Reporting client services when it calls OpenRequestChannel
//!
//! Please look at enum FailureReason in VersionReportingService.h to get the error codes from Version Reporting
namespace smf {

    class VersionReportingServiceResponseHandler {
    public:

        typedef std::vector<smf::PackageInformation> PackageInformationArray;
        typedef std::vector<smf::AppInformation> AppInformationArray;

        //! \brief Callback from smf::ParameterServiceRequestHandler::AddApplication(const VersionReportingRequestParamter &parameter, unsigned int identifier)
        //! \param parameter	The VersionReportingRequestParamter object you have passed in the request
        //! \param identifier	This is the identifier you supplied in AddApplication
        virtual void ReportSuccessfulApplicationUpdate(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Callback from smf::ParameterServiceRequestHandler::AddPackage(const VersionReportingRequestParamter &parameter, unsigned int identifier)		
        //! \param parameter	The VersionReportingRequestParamter object you have passed in the request
        //! \param identifier	This is the identifier you supplied in AddPackage
        virtual void ReportSuccessfulPackageUpdate(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Callback from smf::ParameterServiceRequestHandler::RemoveApplication(const VersionReportingRequestParamter &parameter, unsigned int identifier)		
        //! \param parameter	The VersionReportingRequestParamter object you have passed in the request
        //! \param identifier	This is the identifier you supplied in RemoveApplication
        virtual void ReportSuccessfulApplicationRemoval(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Callback from smf::ParameterServiceRequestHandler::RemovePackage(const VersionReportingRequestParamter &parameter, unsigned int identifier)		
        //! \param parameter	The VersionReportingRequestParamter object you have passed in the request
        //! \param identifier	This is the identifier you supplied in RemovePackage
        virtual void ReportSuccessfulPackageRemoval(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Callback from smf::ParameterServiceRequestHandler::RequestApplicationInformation(const VersionReportingRequestParamter &parameter, unsigned int identifier)		
        //! \param appInfos  	This is a list of application information you have requested
        //! \param identifier	This is the identifier you supplied in RequestApplicationInformation
        virtual void ReportApplicationInformation(const AppInformationArray &appInfos, unsigned int identifier) = 0;

        //! \brief Callback from smf::ParameterServiceRequestHandler::RequestPackageInformation(const VersionReportingRequestParamter &parameter, unsigned int identifier)		
        //! \param appInfos  	This is a list of package information you have requested
        //! \param identifier	This is the identifier you supplied in RequestApplicationInformation
        virtual void ReportPackageInformation(const PackageInformationArray &packageInfos, unsigned int identifier) = 0;

        //! \brief Callback if any of the request failed 		
        //! \param reason       The failure reason
        //! \param identifier	This is the identifier you supplied in the request function
        //! \note For a list of failure reasons see VersionReportingService.h.
        virtual void ReportFailure(unsigned short reason, unsigned int identifier) = 0;

        virtual ~VersionReportingServiceResponseHandler() {
        }
    };
}
#endif
