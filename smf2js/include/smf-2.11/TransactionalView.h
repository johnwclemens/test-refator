
#ifndef TRANSACTIONALVIEW_H
#define TRANSACTIONALVIEW_H

#include "CompiledAccess.h"

namespace smf{
	//this class is designed to read a group of parameters such that they are
	//transactionally consistent - that is, from the first read to the last read
	//operation no transactions have been performed on the partitions containing
	//the parameters being read.
	//
	//When a transactional change is first detected on a partition, Read will return false
	//for parameters on that partition.
	//If a read attempt is made on a parameter from a different partition (provided 
	//it is still consistent) read will return true.
	//So, if parameters are being read from 2 partitions and one partition is in-consistent
	//part way through the read it is possible to continue reading and still get a consistent
	//view for parameters on the unchanged partition. Any parameters that have already been 
	//read must be checked (with Check (....)) to see if they are still valid.
	//
	//Before retrying to read from the inconsistent partition Clear should be called 
	//to reset everything.
	class TransactionalView
	{
	public:
		

		//Return true if the view is still consistent, false if any of the parameters
		//have changed - Note: this is based on whether a transaction has been performed
		//against a partition between two read operations on that partition (even if the 
		//transaction has not directly touched the parameters being read)
		virtual bool Read(const smf::StringElement& , smf::StringHolder&) = 0;
		virtual bool Read(const smf::IntegerElement& , int&) = 0;
        virtual bool Read(smf::CompiledAccessPartition::DataPosition*, smf::StringHolder&) = 0;
		virtual bool Read(smf::CompiledAccessPartition::DataPosition*, int&) = 0;

		//if one partition is changed part way through a read it is possible to
		//continue to read parameters on another partition. BUT any parameters 
		//that have already been read must be checked to ensure they are not on 
		//the changed partition
		virtual bool Check(const smf::StringElement& ) = 0;
		virtual bool Check(const smf::IntegerElement& ) = 0;
		virtual bool Check(smf::CompiledAccessPartition::DataPosition*) = 0;

		//Start again - the next read operation will be treated as the first read operation
		virtual void Clear() = 0;

		virtual ~TransactionalView(){}

	};
}
#endif