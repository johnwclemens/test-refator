#ifndef PSDFIELDVALUE_H
#define PSDFIELDVALUE_H

#pragma warning (disable : 4786)
#include <string>
#include <vector>
#include "PsdMessage.h"


// This is used when making an update using a name or reporting a value by name
//
// See also MessageParser

namespace smf{
	class PsdFieldValue
	{
	public:
		PsdFieldValue(
			const char *f, 
			const char *valueStr, 
			const std::vector<char>&, 
			unsigned int valueInt, 
			smf::PsdMessage::ValueType t,
			smf::PsdMessage::FailureReason r);

		PsdFieldValue(
			const char *f, 
			const char *value, 
			unsigned int len);
				
		PsdFieldValue(
			const char *f, 
			const void *value, 
			unsigned int len);

		PsdFieldValue(
			const char *f, 
			const char *value);

		PsdFieldValue(
			const char *f, 
			int v) ;

		PsdFieldValue(
			const char *f, 
			const VariableType& v) ;

		PsdFieldValue() ;

		explicit PsdFieldValue(const char *f) ;

		PsdFieldValue(
			const char *f, 
			smf::PsdMessage::FailureReason r) ;

		// non field specific failure
		explicit PsdFieldValue(
			smf::PsdMessage::FailureReason r) ;

		void Update(const char* value) ;

		void Update(int value) ;

		~PsdFieldValue();


		smf::PsdMessage::ValueType Type(smf::PsdMessage::DataTypeVersion version = smf::PsdMessage::Version0) const;

		int ValueInt() const;

		const char *ValueStr() const;

		unsigned int StrLength() const;

		BinaryHolder ValueBin() const;
		unsigned int BinLength() const;

		Integer64Type ValueInt64() const;

		DoubleType ValueDouble() const;

		const char *FieldName() const;

		const char* Identifier() const;

		unsigned int FieldLength() const;

		smf::PsdMessage::FailureReason FailureReason()const;

		bool IsNull() const;
		bool IsInteger() const;
		bool IsString() const;
		bool IsBinary() const;
		bool IsInteger64() const;
		bool IsDouble() const;
		
	private:
		std::string field;
		smf::PsdMessage::FailureReason failureReason;
		smf::PsdMessage::ValueType type;
		int valueInt;
		std::string valueStr;
		std::vector<char> valueBinary;
		
	};
}

#endif
