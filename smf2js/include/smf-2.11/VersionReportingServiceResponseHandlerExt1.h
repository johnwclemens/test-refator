#ifndef VERSIONREPORTINGSERVICERESPONSEHANDLEREXT1_H
#define VERSIONREPORTINGSERVICERESPONSEHANDLEREXT1_H

#include "SMFStandardInfo.h"
#include "VersionReportingRequestParamter.h"
#include "VersionReportingServiceResponseHandler.h"

//! Version Reporting Service - Response Handler
//! This is the interface Version Reporting client service uses to update/query version information
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Version Reporting client services when it calls OpenRequestChannel
//!
//! Please look at enum FailureReason in VersionReportingService.h to get the error codes from Version Reporting
namespace smf {
    class VersionReportingServiceResponseHandlerExt1 : public VersionReportingServiceResponseHandler
    {
    public :
        //! \brief Callback from smf::VersionReportingServiceRequestHandlerExt1::SetSMFStandardInfo(const SMFStandardInfo &ssinfo, unsigned int identifier)
        //! \param identifier	This is the identifier you supplied in SetSMFStandardInfo
        virtual void ReportSuccessfulSetSMFStandardInfo(unsigned int identifier) = 0;

        //! \brief Callback from smf::VersionReportingServiceRequestHandlerExt1::GetSMFStandardInfo(unsigned int identifier)
        //! \param parameter	The SMFStandardInfo object you have passed in the request
        //! \param identifier	This is the identifier you supplied in GetSMFStandardInfo
        virtual void ReportSuccessfulGetSMFStandardInfo(const SMFStandardInfo &ssinfo, unsigned int identifier) = 0;

        virtual ~VersionReportingServiceResponseHandlerExt1() {
        }

    } ;
}

#endif // VERSIONREPORTINGSERVICERESPONSEHANDLEREXT1_H
