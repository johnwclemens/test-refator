
#ifndef PSDSERVICERESPONSEHANDLEREXT1_H
#define PSDSERVICERESPONSEHANDLEREXT1_H

#include "ConstantVector.h"
#include "ParameterServiceResponseHandler.h"


//! Psd Service - Resizable Array Response Handler
//! This is the interface Psd client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Psd client services when it  calls OpenRequestChannel
//!
//! Please look at enum FailureReason in PsdMessage.h to get the error codes from PSD
namespace smf{
	class ParameterServiceResponseHandlerExt1 : public ParameterServiceResponseHandler
	{
	public:
		
		typedef smf::ConstantVector<smf::PsdFieldValue> FieldSize;		
		typedef smf::ConstantVector<smf::PsdFieldValue> FieldCapacity;		

		//! \brief Callback from smf::ParameterServiceRequestHandlerExt1::RequestArraySize(const Fields& fields, UnsignedInt identifier)		
		//! \param fieldSize	This is a list of parameter names and their associated array committed size. 
		//! \param identifier	This is the identifier you supplied in RequestCommittedSize. 
		virtual void ReportArraySize(FieldSize& fieldSize, UnsignedInt identifier)=0;		

		//! \brief Callback from smf::ParameterServiceRequestHandler::RequestArrayCapacity(const Fields& fields, UnsignedInt identifier)		
		//! \param fieldCapacity This is a list of parameter names and their associated array capacity. 
		//! \param identifier	 This is the identifier you supplied in RequestCapacity.
		virtual void ReportArrayCapacity(FieldCapacity& fieldCapacity, UnsignedInt identifier)=0;		
    

		virtual ~ParameterServiceResponseHandlerExt1() {}
	};
}
#endif
