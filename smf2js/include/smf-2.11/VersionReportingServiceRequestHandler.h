
#ifndef VERSIONREPORTINGSERVICEREQUESTHANDLER_H
#define VERSIONREPORTINGSERVICEREQUESTHANDLER_H

#include "VersionReportingServiceResponseHandler.h"
#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "Types.h"

#include <vector>
#include "VersionReportingRequestParamter.h"

//! Version Reporting Service - Request Handler
//! This interface is for the local/remote client to update/display version information of the components
//! 

namespace smf {

    class VersionReportingServiceRequestHandler {
    public:

        //! \brief Use this function to add a new application entry into the SMF server.
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the abbreviation of the function/name of the application software installed on the server by VersionReportingRequestParamter::SetAppName(). E.g. ADS, SIR.
        //! Set the current version of the application software, which is passed in the VersionReportingRequestParamter::SetAppName(), by VersionReportingRequestParamter::SetAppVersion(). E.g. 1.0, 2.4.1.
        //! Pass true to VersionReportingRequestParamter::SetIsServiceApp() if the application software, which is passed in the VersionReportingRequestParamter::SetAppName(), is a major application providing service to customers.
        //! Pass VersionReportingRequestParamter::Overwrite to VersionReportingRequestParamter::SetActionsOnExist() for updating the application version If there is an existing entry with the same application name.
        //! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
        //! \remark Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h.
        //! \post The result will be reported back through your implementation of the smf::VersionReportingServiceResponseHandler in the ReportSuccessfulApplicationUpdate function
        //! \note	The VersionReportingServiceRequestHandler::AddApplication function is thread safe. 
        virtual void AddApplication(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Use this function to add a new package entry associate with its application into the SMF server
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the name of the associated "Root application" by VersionReportingRequestParamter::SetRootAppName(). If an empty string is passed into VersionReportingRequestParamter::SetRootAppName(), the package is added under all major application(s) providing service to customers.
        //! If a special key-word "no-association" is passed into VersionReportingRequestParamter::SetRootAppName(), the package is added with no "Root application".
        //! Set the software package name that is required to be installed for the application software by VersionReportingRequestParamter::SetPackageName(). E.g. RDMD.
        //! Set the version of the software package which is passed in the VersionReportingRequestParamter::SetPackageName() by VersionReportingRequestParamter::SetPackageVersion(). E.g. 4.20.20-1.
        //! Pass VersionReportingRequestParamter::Overwrite to VersionReportingRequestParamter::SetActionsOnExist() for updating the package version If there is an existing entry with the same package name.
        //! Pass VersionReportingRequestParamter::Duplicate to VersionReportingRequestParamter::SetActionsOnExist() for creating a new package entry if there is an existing entry with the same package name.
        //! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
        //! \remark Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h
        //! \post The values will be reported back through your implementation of the smf::VersionReportingServiceResponseHandler in theReportSuccessfulPackageUpdate function
        //! \note The VersionReportingServiceRequestHandler::AddPackage function is thread safe
        virtual void AddPackage(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Use this function to remove the application entry from the SMF server
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the abbreviation of the function/name of the application software installed on the server by VersionReportingRequestParamter::SetAppName(), E.g. ADS, SIR.
        //! For the specified application entry to be removed, all the associated package version entries are also removed.
        //! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the handles.
        //! \remark Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h
        //! \post The handles will be reported back through your implementation of the smf::VersionReportingServiceResponseHandler in the ReportSuccessfulApplicationRemoval function
        //! \note	The VersionReportingServiceRequestHandler::RequestHandles function is thread safe.
        virtual void RemoveApplication(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Use this function to remove the package entry associate with its application from the SMF server
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the name of the associated "Root application" by VersionReportingRequestParamter::SetRootAppName(). If an empty string is passed into VersionReportingRequestParamter::SetRootAppName(), the packages under all major application(s) providing service to customers are removed.
        //! If a special key-word "no-association" is passed into VersionReportingRequestParamter::SetRootAppName(), the package entry with no "Root application" is removed.
        //! Set the package name that is required to be removed for the application software by VersionReportingRequestParamter::SetPackageName(), E.g. RDMD.
        //! Set the version of the software package which is passed in the VersionReportingRequestParamter::SetPackageName() by VersionReportingRequestParamter::SetPackageVersion(), E.g. 4.20.20-1. 
        //! If an empty string is passed into VersionReportingRequestParamter::SetPackageVersion(), all the versions of the specified package entries are removed.        
        //! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \remark Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h
        //! \post The outcome of the update operation should be reported through your implementation of the smf::VersionReportingServiceResponseHandler in the ReportSuccessfulPackageRemoval function
        //! note The VersionReportingServiceRequestHandler::RemovePackage function is thread safe.
        virtual void RemovePackage(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Use this function to query the application version entry from the SMF server
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the abbreviation of the function/name of the application software installed on the server by VersionReportingRequestParamter::SetAppName(), E.g. ADS, SIR.
        //! If an empty string is passed into VersionReportingRequestParamter::SetAppName(), all the application version entries are reported.
        //! \param identifier		This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \remark	Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h
        //! \post The outcome of the update operation should be reported through your implementation of
        //! smf::VersionReportingServiceResponseHandler::ReportApplicationVersion or smf::VersionReportingServiceResponseHandler::ReportFailure
        //! (see the Parameter Service sample in the SMF-SDK samples directory for an example implementation).
        //! \note The VersionReportingServiceRequestHandler::RequestApplicationInformation function is thread safe.
        virtual void RequestApplicationInformation(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        //! \brief Use this function to query the package version entry associate with its application from the SMF server
        //! \param parameter	This is the VersionReportingRequestParamter object. The function will operate based on the values in the object.
        //! Set the name of the associated "Root application" by VersionReportingRequestParamter::SetRootAppName().
        //! If a special key-word "no-association" is passed into VersionReportingRequestParamter::SetRootAppName(), the specified package entry with no "Root application" is reported.
        //! If an empty string is passed into VersionReportingRequestParamter::SetRootAppName(), it reports (i) the specified package entries under all major application(s) providing service to customers; and (ii) the specified package entries with no "Root application".
        //! Set the package name that is required to be queried for the application software by VersionReportingRequestParamter::SetPackageName(), E.g. RDMD.
        //! If an empty string is passed into VersionReportingRequestParamter::SetPackageName(), all package entries under the specified application are reported.
        //! If an empty string is passed into both VersionReportingRequestParamter::SetRootAppName() and VersionReportingRequestParamter::SetPackageName(), all package version entries are reported.
        //! \param identifier		This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \remark	Include: VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h, Error.h
        //! \post The outcome of the update operation should be reported through your implementation of
        //! smf::VersionReportingServiceResponseHandler::ReportPackageInformation or smf::VersionReportingServiceResponseHandler::ReportFailure
        //! (see the Parameter Service sample in the SMF-SDK samples directory for an example implementation).
        //! \note The VersionReportingServiceRequestHandler::UpdateValues function is thread safe.
        virtual void RequestPackageInformation(const VersionReportingRequestParamter &parameter, unsigned int identifier) = 0;

        virtual bool IsConnected() = 0;

        virtual ~VersionReportingServiceRequestHandler() {
        }

    };
}

#endif
