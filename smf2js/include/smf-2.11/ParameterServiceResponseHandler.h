
#ifndef PSDSERVICERESPONSEHANDLER_H
#define PSDSERVICERESPONSEHANDLER_H

#include "ConstantVector.h"
#include "PsdFieldHandle.h"
#include "PsdFieldValue.h"
#include "PsdHandleValue.h"
#include "Types.h"
#include <vector>
#include <string>


//! Psd Service - Response Handler
//! This is the interface Psd client service uses to report Values etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the Psd client services when it  calls OpenRequestChannel
//!
//! Please look at enum FailureReason in PsdMessage.h to get the error codes from PSD
namespace smf{
	class ParameterServiceResponseHandler
	{
	public:
		typedef unsigned int Handle ;

		// A ConstantVector should provide the read functionality of the vector
		// It is unsafe to change a vector (or string etc...) created on one side 
		// of a DLL boundary, from the other side - i.e. if the vector is allocated 
		// inside the DLL it should not be changed outside the DLL.
		typedef smf::ConstantVector<smf::PsdFieldValue> FieldValues;
		typedef smf::ConstantVector<smf::PsdHandleValue> HandleValues;
		typedef smf::ConstantVector<smf::PsdFieldHandle> FieldHandles;
		typedef smf::ConstantVector<std::string> Schema;
		typedef smf::ConstantVector<char> Metadata;
		typedef smf::ConstantVector<std::string> Partitions;

		//! \brief Callback from smf::ParameterServiceRequestHandler::RequestValues(const Fields& fields, UnsignedInt identifier)
		//! \param fieldValues	This is a list of parameter names and their associated values. 
		//! \param identifier	This is the identifier you supplied in RequestValues.
		virtual void ReportValues(FieldValues& fieldValues, UnsignedInt identifier)=0;
		//! \brief Callback from smf::ParameterServiceRequestHandler::RequestValues(const Handles& handles, UnsignedInt identifier)
		//! \param handleValues	This is a list of handles and their associated values. 
		//! \param identifier	This is the identifier you supplied in RequestValues.
		virtual void ReportValues(HandleValues& handleValues, UnsignedInt identifier )=0;
		//! \brief  A handle directly maps through to a parameter at the server, 
		//! allowing the server to access the given parameter without having to search for it.
		//! Callback from smf::ParameterServiceRequestHandler::RequestHandles
		//! Note: all handles will become invalid and must be re-requested, in the event that the server
		//!is restarted
		//! \param fieldHandles		This is a list of parameter names and their corresponding handles.
		//!							Use fieldHandles[i].Handle() to get the associated handle.
		//!							Note: you should check fieldHandles[i].FailureReason() is equal to smf::PsdMessage::Success for each handle.
		//! \param identifier		This is the identifier you supplied in RequestHandles.
		virtual void ReportHandles(FieldHandles& fieldHandles, UnsignedInt identifier)=0;

		//! \brief The outcome of the update values operation 
		//! See the Parameter Service sample in the SMF-SDK samples directory for an example implementation
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulUpdate(UnsignedInt identifier)=0;
		//virtual void ReportSchema(const char* line)=0;
		virtual void ReportSchema(Schema&, UnsignedInt) = 0;

		//! \brief Callback from smf::ParameterServiceRequestHandler::RequestMetadata(const std::string &name, const std::string &type, Metadata& metadata, UnsignedInt identifier) when the metadata has been requested successfully.
		//! \param name		This is the name of metadata reported.  This should correspond to the requested name.
		//! \param type		This is the type of the metadata reported.
		//! \param metadata	This is the content of the requested metadata.
		//! \param identifier	This is the identifier you supplied in RequestMetadata.
		virtual void ReportMetadata(const std::string &name, const std::string &type, Metadata& metadata, UnsignedInt identifier) {};
		virtual void ReportMetadataError(const std::string &name, const std::string &type, unsigned short reason, const std::string &description, UnsignedInt) {};

		virtual void ReportPartitions(Partitions&, UnsignedInt)=0;

		//! \brief The outcome of the update values by name operation 
		//! \param fieldValues	This list contains one or more PsdFieldValue object. 
		//! Each PsdFieldValue should contain a failure reason if that specific parameter failed.
		//! Note: the list may be of a different length to the list you specified in the UpdateValues() function. 
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \note For a list of failure reasons see PsdMessage.h.
		virtual void ReportFailedUpdates(FieldValues& fieldValues, UnsignedInt identifier) = 0;

		//! \brief The outcome of the update values by handle operation 
		//! See the Parameter Service sample in the SMF-SDK samples directory for an example implementation
		//! \param handleValues		This list contains one or more PsdHandleValue object. 
		//! Each PsdHandleValue should contain a failure reason if that specific parameter failed.
		//! Note: the list may be of a different length to the list you specified in the UpdateValues() function. 
		//! \param identifier		This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \note For a list of failure reasons see PsdMessage.h.
		virtual void ReportFailedUpdates(HandleValues& handleValues, UnsignedInt identifier) = 0;
		virtual void ReportFailure(unsigned short reason) = 0;
		//virtual void ReportMissingMessages(unsigned int count) = 0;
		//virtual void ReportUnknownMessage() = 0;
		//virtual void ReportUnsupportedMessage() = 0;

		virtual ~ParameterServiceResponseHandler() {}
	};
}
#endif
