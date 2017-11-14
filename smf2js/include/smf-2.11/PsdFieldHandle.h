#ifndef PSDFIELDHANDLE_H
#define PSDFIELDHANDLE_H

#pragma warning (disable : 4786)
#include <string>
#include "PsdMessage.h"

// This is used when reporting handles by name  - it contains the field name and 
// handle OR an error reason if the search for the field failed etc...
//
namespace smf{
	class PsdFieldHandle
	{
	public:
		
		typedef unsigned int HandleType;

		PsdFieldHandle();

		PsdFieldHandle(const char *f, int h, smf::PsdMessage::ValueType t);

		PsdFieldHandle(const char *f, smf::PsdMessage::FailureReason r) ;

		// non field specific failure
		explicit PsdFieldHandle(smf::PsdMessage::FailureReason r) ;

		PsdFieldHandle(const char *f, int h, smf::PsdMessage::ValueType t, smf::PsdMessage::FailureReason r);

		smf::PsdMessage::ValueType Type(smf::PsdMessage::DataTypeVersion version = smf::PsdMessage::Version0) const;
		HandleType Handle() const;

		const char *FieldName() const;

		const char* Identifier();

		smf::PsdMessage::FailureReason FailureReason()const;
		unsigned int FieldLength() const;

		bool IsNull() const;
		bool IsInteger() const;
		bool IsString() const;
		bool IsBinary() const;
		bool IsInteger64() const;
		bool IsDouble() const;

	private:
		

		std::string field;
		smf::PsdMessage::FailureReason reason;
		smf::PsdMessage::ValueType type;
		HandleType handle;
	};
}
#endif
