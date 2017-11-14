
#ifndef DATAPOSITIONFACTORY_H
#define DATAPOSITIONFACTORY_H

#include "CompiledAccessPartition.h"

namespace smf{
	class CompiledAccessPartition;
	class CompiledAccessPartition::DataPosition;


	class DataPositionFactory {
	public:
		//! \brief To create a DataPosition you must first create a DataPositionFactory.
		//! To access parameters in the partitions directly you need a DataPosition
		//! (see Creating a Data Position Factory)
		//! These functions can be used to create smf::CompiledAccessPartition::DataPositions
		//! \param name The name of the parameter. 
		//! \return A DataPosition pointer or null if the group could not be found.
		//! \exception CompiledAccessPartition::ParameterNotFound For more specific exceptions see CompiledAccessPartition.h
		//! \exception smf::Error
		//!	\post Cleanup: You must clear up the object by calling DestroyDataPosition (see Destroying a Data Position).
		//! \note This is not thread safe. 
		virtual smf::CompiledAccessPartition::DataPosition* CreateDataPosition(
													const std::string &name) = 0;
		virtual smf::CompiledAccessPartition::DataPosition* FindDataPosition(
													const std::string &name, const char* partitionName = 0) = 0;

		//! \brief Use this function to clear up a DataPosition created using the FindDataPosition() function (see Creating Data Positions)
		//! \param dataPosition A pointer to a DataPosition created by DataPositionFactory::FindDataPosition() function
		//! \note This is thread safe.	
		virtual void DestroyDataPosition(smf::CompiledAccessPartition::DataPosition* dataPosition) = 0;

		//! A flag to check the data position is vaild or not
		virtual bool IsValid() = 0; 
		
		virtual ~DataPositionFactory() {}
	};

}

#endif
