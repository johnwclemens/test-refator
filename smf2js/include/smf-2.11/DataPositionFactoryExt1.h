
#ifndef DATAPOSITIONFACTORYEXT1_H
#define DATAPOSITIONFACTORYEXT1_H


#include "DataPositionFactory.h"

namespace smf{

	class DataPositionFactoryExt1 : public DataPositionFactory
	{
	public:

		//! \brief Use this function to get the array committed size of a repeated parameter.
		//! \param dataPosition A pointer to a DataPosition created by DataPositionFactory::FindDataPosition() function
		//! \note This is thread safe.
		virtual smf::CompiledAccessPartition::LongLengthType GetArraySize(const CompiledAccessPartition::DataPosition* pos) = 0;

		//! \brief Use this function to get the array capacity of a repeated parameter.
		//! \param dataPosition A pointer to a DataPosition created by DataPositionFactory::FindDataPosition() function
		//! \note This is thread safe.
		virtual smf::CompiledAccessPartition::LongLengthType GetArrayCapacity(const CompiledAccessPartition::DataPosition* pos) = 0;

		//! \brief Use this function to set the array committed size of a repeated parameter.
		//! \param name The name of the parameter. 
		//! \note This is thread safe.
		virtual bool SetArraySize(const std::string &name, unsigned int size) = 0;

		virtual ~DataPositionFactoryExt1() {}

	};

}
#endif