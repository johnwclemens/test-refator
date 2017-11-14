
#ifndef TRANSACTIONALUPDATE_H
#define TRANSACTIONALUPDATE_H

#include "CompiledAccess.h"
#include <string>
#include <vector>
#include <utility>

namespace smf
{

	class TransactionalUpdate
	{
	public:
		class Value{
		public:
			Value();
			explicit Value(const char*);
			explicit Value(long);

			const char* StringValue() const;
			long IntegerValue() const;

			bool IsInteger() const;
			bool IsNull() const;

		private:
			bool isInteger, isNull;
			std::string str;
			long integer;
		};

		typedef std::pair<smf::CompiledAccessPartition::DataPosition* , Value> PositionValue;
		typedef std::vector<PositionValue> PositionValues;
		
        virtual bool Write(const PositionValues&) = 0;
		
		virtual ~TransactionalUpdate(){}
	};

}

#endif
