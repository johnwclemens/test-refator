
#ifndef PSDSERVICERESPONSEHANDLEREXT2_H
#define PSDSERVICERESPONSEHANDLEREXT2_H

#include "ConstantVector.h"
#include "ParameterServiceResponseHandlerExt1.h"


//! Psd Service - Support parameter subscription
//! This is the interface Psd client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Psd client services when it  calls OpenRequestChannel
//!
//! Please look at enum FailureReason in PsdMessage.h to get the error codes from PSD
namespace smf{
	class ParameterServiceResponseHandlerExt2 : public ParameterServiceResponseHandlerExt1
	{
	public:
		

		virtual void SubscriptionSuccessful(UnsignedInt id) = 0;
		virtual void SubscriptionFailed(UnsignedInt id, UnsignedInt reason) = 0;
		virtual void UnsubscribeSuccessful(UnsignedInt id) = 0;
		virtual void UnsubscribeFailed(UnsignedInt id, UnsignedInt reason) = 0;    

		virtual ~ParameterServiceResponseHandlerExt2() {}
	};
}
#endif
