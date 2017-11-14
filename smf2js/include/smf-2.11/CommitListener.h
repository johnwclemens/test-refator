
#ifndef SMF_COMMITLISTENER_H
#define SMF_COMMITLISTENER_H

#include "Partition.h"

namespace smf{
	class CommitListener
	{
	public:
	    virtual void ValueCommitted(
            const Partition::DataPosition &, 
            const smf::PartitionTypes::CharType *olddata,
            const smf::PartitionTypes::CharType *newdata) = 0;
	    virtual void ValueCommitted(
            const Partition::DataPosition &, 
            smf::PartitionTypes::IntegerType olddata,
            smf::PartitionTypes::IntegerType newdata) = 0;

		
		virtual void ValueCommitted(
            const Partition::DataPosition &, 
            const Partition::BinaryType& olddata,
            const Partition::BinaryType& newdata) = 0;

		virtual void Completed() = 0;
		virtual void Started() = 0;

		virtual ~CommitListener() {}
	};

}

#endif