#ifndef VERSIONREPORTINGSERVICEREQUESTHANDLEREXT1_H
#define VERSIONREPORTINGSERVICEREQUESTHANDLEREXT1_H

#include "VersionReportingServiceRequestHandler.h"
#include "SMFStandardInfo.h"
#include "Error.h"

namespace smf {
    class VersionReportingServiceRequestHandlerExt1 : public VersionReportingServiceRequestHandler {
    public:

        //! \brief Use this function to update standard information from the SMF server
        //! \param parameter	This is the SMFStandardInfo object. The function will operate based on the values in the object.
        //! If string "SMFStandardInfo_KEEP" is passed into a parameter, the operation will not be updated
        //! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \remark	Include: VersionReportingServiceResponseHandlerExt1.h, VersionReportingServiceRequestHandlerExt1.h, Error.h
        //!                  VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h
        //! \post The outcome of the update operation should be reported through your implementation of
        //! smf::VersionReportingServiceResponseHandlerExt1::ReportSucessfulSetSMFStandardInfo or smf::VersionReportingServiceResponseHandler::ReportFailure
        //! (see the Parameter Service sample in the SMF-SDK samples directory for an example implementation).
        //! \note The VersionReportingServiceRequestHandlerExt1::SetSMFStandardInfo function is thread safe.
        virtual void SetSMFStandardInfo(const SMFStandardInfo &ssinfo, unsigned int identifier) = 0;

        //! \brief Use this function to query standard information from the SMF server
        //! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \remark	Include: VersionReportingServiceResponseHandlerExt1.h, VersionReportingServiceRequestHandlerExt1.h, Error.h
        //!                      VersionReportingServiceResponseHandler.h, VersionReportingServiceRequestHandler.h
        //! \post The outcome of the get operation should be reported through your implementation of
        //! smf::VersionReportingServiceResponseHandlerExt1::ReportSucessfulGetSMFStandardInfo or smf::VersionReportingServiceResponseHandler::ReportFailure
        //! (see the Parameter Service sample in the SMF-SDK samples directory for an example implementation).
        //! \note The VersionReportingServiceRequestHandlerExt1::GetSMFStandardInfo function is thread safe.
        virtual void GetSMFStandardInfo(unsigned int identifier) = 0;

        virtual ~VersionReportingServiceRequestHandlerExt1() {
        }

    } ;
}

#endif // VERSIONREPORTINGSERVICEREQUESTHANDLEREXT1_H
