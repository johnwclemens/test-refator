
#ifndef VERSIONREPORTINGSERVICEENTRYPOINTS_H
#define VERSIONREPORTINGSERVICEENTRYPOINTS_H

#include "VersionReportingRequestParamter.h"

namespace smf{

	class Logger;
	class ServiceChannel;
	class VersionReportingServiceRequestHandler;
	class VersionReportingServiceResponseHandler;
	class VersionReportingServiceRequestHandlerExt1;
	class VersionReportingServiceResponseHandlerExt1;
  
        

	namespace VersionReportingService{
		
        enum FailureReason
        {
            Success,
            UnclassifiedFailure,
            InvalidParameter,
            AlreadyExists,
            DuplicateExist,
            NoEmptySpace,
            NotFound,
            NotConnected,
            FailToRetrieveSMFBin,
            NoServiceProvidingApp,
            CodingError,
			GeneralFailure	//This identifier returned will be 0 in this case
        };

		const char* LibName();
		
		//! \brief This function will create a VersionReportingServiceRequestHandler which can be used to edit/query component version information in/from the SMF Server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::VersionReportingServiceResponseHandler interface.
		//!							See the samples/VersionReportingService directory in the SMF-SDK for an example implementation.
		//! \param serverName		The hostname of the server. If this is empty or 0, local server is assumed.
		//! \param port				the port of the server. This is useful only if the serverName is not empty.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::VersionReportingServiceRequestHandler object.
		//!	\remark					Include: VersionReportingService.h, VersionReportingServiceRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::VersionReportingService::CloseRequestChannel to cleanup (see Closing a VersionReporting Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in VersionReportingServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		VersionReportingServiceRequestHandler* OpenRequestChannel(
				VersionReportingServiceResponseHandler* responseHandler,
				Logger* logger , 
				const char* serverName = "",
				unsigned short port = 8603,
				unsigned int queueSize = 0, //the default queue size will be used
                const char* binConfigLocation = "", //the default location of the smf bin configuration placed, local application only				
                const char* binLocation = "" //the default location of the smf bin placed, local application only                
				);

		//! \brief You should call this function to close a smf::VersionReportingServiceRequestHandler once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this VersionReportingServiceRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::VersionReportingService::OpenRequestChannel function.
		//!	\remark						Include: VesionReportingService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				VersionReportingServiceRequestHandler* requestHandler
				);     

    
	    //! \brief This function will create a VersionReportingServiceRequestHandlerExt1 which can be used to edit/query component version information in/from the SMF Server
		//! \param responseHandlerExt1 You must provide an implementation of this.  Your implementation of the smf::VersionReportingServiceResponseHandlerExt1 interface.
		//!							   See the samples/VersionReportingService directory in the SMF-SDK for an example implementation.
		//! \param serverName		   The hostname of the server. If this is empty or 0, local server is assumed.
		//! \param port				   the port of the server. This is useful only if the serverName is not empty.
		//! \param logger			   Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							   (use smf::fileLogger function)
		//!							   A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							   Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		   The internal queue size for handling responses.
		//!							   If you pass zero here the default queue size will be used.
		//! \return					   A pointer to a Smf::VersionReportingServiceRequestHandlerExt1 object.
		//!	\remark					   Include: VersionReportingService.h, VersionReportingServiceRequestHandlerExt1.h, Logger.h.
		//!	\post					   Cleanup: You must call smf::VersionReportingService::CloseRequestChannel to cleanup (see Closing a VersionReporting Service Request Handler).
		//! \exception				   You should at least catch smf::Error. Specific exceptions that might be thrown are defined in VersionReportingServiceRequestHandler.h.
		//! \note					   This function is thread safe. 
		VersionReportingServiceRequestHandlerExt1* OpenRequestChannelExt1(
				VersionReportingServiceResponseHandlerExt1* responseHandlerExt1,
				Logger* logger , 
				const char* serverName = "",
				unsigned short port = 8603,
				unsigned int queueSize = 0, //the default queue size will be used
                const char* binConfigLocation = "", //the default location of the smf bin configuration placed, local application only				
                const char* binLocation = "" //the default location of the smf bin placed, local application only                
				);

		//! \brief You should call this function to close a smf::VersionReportingServiceRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this VersionReportingServiceRequestHandlerExt1. 
		//! \param requestHandlerExt1	The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::VersionReportingService::OpenRequestChannelExt1 function.
		//!	\remark						Include: VesionReportingService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				VersionReportingServiceRequestHandlerExt1* requestHandlerExt1
				);     

                unsigned int SetChannelLimit(unsigned int);
	}
}
#endif
