

#ifndef COMPILEDACCESSPARTITIONEXT1_H
#define COMPILEDACCESSPARTITIONEXT1_H

#include "PartitionTypes.h"
#include "Reference.h"
#include "Error.h"
#include "CompiledAccessPartition.h"

namespace smf {

		
	class CompiledAccessPartitionExt1 : public smf::CompiledAccessPartition 
	{
	public:

		virtual LongLengthType GetArraySize(const CompiledAccessPartition::DataPosition* pos) const = 0;
		virtual LongLengthType GetArrayCapacity(const CompiledAccessPartition::DataPosition* pos) const = 0;
		virtual bool SetArraySize(const std::string &name, unsigned int size) const = 0;

		virtual ~CompiledAccessPartitionExt1() {}
	};
}

#endif