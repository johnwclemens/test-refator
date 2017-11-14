#ifndef PSDVALUE_H
#define PSDVALUE_H

#pragma warning (disable : 4786)
#include "PsdMessage.h"
#include <string>
#include <vector>

namespace smf{
	class PsdValue
	{
	public:

		PsdValue();
        PsdValue(int value);
        PsdValue(const char* value);
		PsdValue(const std::vector<char>& value);
		PsdValue(const smf::VariableType& value);

        bool IsNull() const;
        bool IsInteger() const;
		bool IsString() const;
        bool IsBinary() const;
		bool IsInteger64() const;
		bool IsDouble() const;

        int IntegerValue() const;
		smf::BinaryHolder BinaryValue() const;
        const char* StringValue() const;
        size_t StringLength() const;
		Integer64Type Integer64Value() const;
		DoubleType DoubleValue() const;

	private:
        enum Type{
            Null,
            Integer,
            String,
			Binary,
			Integer64,
			Double
        };
        Type type;
        std::string strValue;
        int intValue;
		std::vector<char> binValue;
	};
}

#endif
