#ifndef SCtrlAppStatusResponseHandlerExt2_H
#define SCtrlAppStatusResponseHandlerExt2_H

#include "Types.h"
#include "SCtrlAppStatusResponseHandlerExt1.h"

//! SCtrl Application Status - Response Handler
//! This is the interface SCtrl client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the SCtrl client services when it  calls OpenAppStatusRequestChannelExt2
//!
//! Please look at enum FailureReason in SCtrlMessage.h to get the error codes from SCtrl
namespace smf{
	class SCtrlAppStatusResponseHandlerExt2
		: public SCtrlAppStatusResponseHandlerExt1
	{
	public:

		//! \brief The outcome of the update application health status operation 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulUpdate(UnsignedInt identifier)=0;
		
		virtual void ReportFailure(unsigned short reason, UnsignedInt identifier) = 0;

		//! \brief The outcome of the NotifyCleanShutdown 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulNotifyCleanShutdown(UnsignedInt identifier)=0;

		//! \brief The outcome of the CheckAndResetCleanShutdown 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulCheckAndResetCleanShutdown(UnsignedInt identifier)=0;
		
		//! \brief The outcome of the SetAppAsInvalid 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulSetAppAsInvalid(UnsignedInt identifier)=0;		
	};
}
#endif