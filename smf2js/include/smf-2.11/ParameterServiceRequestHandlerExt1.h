
#ifndef PSDSERVICERREQUESTHANDLEREXT1_H
#define PSDSERVICERREQUESTHANDLEREXT1_H


#include "ParameterServiceRequestHandler.h"

//! Psd Service - Resizable Array Request Handler
//! This interface is for the remote client to make requests for Values, Handles or updates
//! 

namespace smf{
	class ParameterServiceRequestHandlerExt1 : public ParameterServiceRequestHandler
	{
	public:
				
		//! \brief Use this function to retrieve the array committed size of parameter by name.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the committed sizes.
		//! \remark Include: ParameterServiceResponseHandlerExt1.h, ParameterServiceRequestHandlerExt1.h, Error.h.
		//! \post The array sizes will be reported back through your implementation of the smf::ParameterServiceResponseHandlerExt1 in the ReportArraySize function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandlerExt1::RequestArraySize function is thread safe.
		virtual void RequestArraySize(const Fields& fields, UnsignedInt identifier)=0;
		
   
		//! \brief Use this function to retrieve the array capacity of parameter by name.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the capacities.
		//! \remark Include: ParameterServiceResponseHandlerExt1.h, ParameterServiceRequestHandlerExt1.h, Error.h.
		//! \post The capacities will be reported back through your implementation of the smf::ParameterServiceResponseHandlerExt1 in the ReportArraCapacity function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandlerExt1::RequestArrayCapacity function is thread safe.
		virtual void RequestArrayCapacity(const Fields& fields, UnsignedInt identifier)=0;
    

		virtual ~ParameterServiceRequestHandlerExt1() {}
		
	};
}

#endif