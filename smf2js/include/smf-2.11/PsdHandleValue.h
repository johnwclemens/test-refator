#ifndef PSDHANDLEVALUE_H
#define PSDHANDLEVALUE_H

#pragma warning (disable : 4786)
#include <string>
#include <vector>
#include "PsdMessage.h"

// This line type is used when sending updates by handle to the server OR to receive
// responses by handle 

namespace smf{
	class PsdHandleValue
	{
	public:
		typedef unsigned int HandleType;
		
		PsdHandleValue(
			HandleType h, 
			unsigned int valueInt,
			const char *valueStr, 
			const std::vector<char>& valueBin,
			PsdMessage::ValueType type,
			PsdMessage::FailureReason reason);

		PsdHandleValue(
			HandleType h, 
			const char *value, 
			unsigned short len);

		PsdHandleValue(
			HandleType h, 
			const void *value, 
			unsigned int len);

		PsdHandleValue(HandleType h, const char *value) ;

		PsdHandleValue(HandleType h, int v) ;

		PsdHandleValue(HandleType h, const smf::VariableType& v);

		PsdHandleValue(HandleType h, PsdMessage::FailureReason reason);

		// non field specific failure
		PsdHandleValue(PsdMessage::FailureReason reason) ;

		PsdHandleValue();

		virtual ~PsdHandleValue();

		PsdMessage::ValueType Type(smf::PsdMessage::DataTypeVersion version = smf::PsdMessage::Version0) const;

		int ValueInt() const;

		const char *ValueStr() const;

		unsigned int StrLength() const;

		BinaryHolder ValueBin() const;
		unsigned int BinLength() const;

		Integer64Type ValueInt64() const;

		DoubleType ValueDouble() const;

		unsigned short FailureReason()const;

		HandleType Handle()const;

		HandleType Identifier()const;

		bool IsNull() const;
		bool IsInteger() const;
		bool IsString() const;
		bool IsBinary() const;
		bool IsInteger64() const;
		bool IsDouble() const;

	private:

		HandleType handle;
		smf::PsdMessage::FailureReason failureReason;
		smf::PsdMessage::ValueType type;
		unsigned int valueInt;
		std::string valueStr;
		std::vector<char> valueBinary;
	};
}
#endif
