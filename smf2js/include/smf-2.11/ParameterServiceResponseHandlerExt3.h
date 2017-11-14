
#ifndef PSDSERVICERESPONSEHANDLEREXT3_H
#define PSDSERVICERESPONSEHANDLEREXT3_H

#include "ParameterServiceResponseHandlerExt2.h"


//! Psd Service - Support dynamic reload partition
//! This is the interface Psd client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Psd client services when it  calls OpenRequestChannel
//!
//! Please look at enum FailureReason in PsdMessage.h to get the error codes from PSD
namespace smf{
	class ParameterServiceResponseHandlerExt3 : public ParameterServiceResponseHandlerExt2
	{
	public:
		
		virtual void DynamicReloadPartitionSuccessful(UnsignedInt identifier) = 0;
		virtual void DynamicReloadPartitionFailed(UnsignedInt identifier, UnsignedInt reason) = 0;
		
		virtual ~ParameterServiceResponseHandlerExt3() {}
	};
}
#endif
