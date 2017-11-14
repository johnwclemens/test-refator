#ifndef SCTRLAPPSTATUSRESPONSEHANDLER_H
#define SCTRLAPPSTATUSRESPONSEHANDLER_H

#include "Types.h"

//! SCtrl Application Status - Response Handler
//! This is the interface SCtrl client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the SCtrl client services when it  calls OpenAppStatusRequestChannel
//!
//! Please look at enum FailureReason in SCtrlMessage.h to get the error codes from SCtrl
namespace smf{
	class SCtrlAppStatusResponseHandler
	{
	public:

		//! \brief The outcome of the update application health status operation 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulUpdate(UnsignedInt identifier)=0;
		virtual void ReportFailure(unsigned short reason, UnsignedInt identifier) = 0;
		
	};
}
#endif