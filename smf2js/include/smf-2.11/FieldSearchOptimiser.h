//
//Behaviour: 
//	A search optimiser should be told where to start searching and how many guesses to make.
//	Everytime index() is called is 1 guess. If index() is called n times and n == max number of guesses
//	index must return false. Otherwise index() must return true and guess where the next field will 
//	be found.
//	NOTE: this is intended to *help* optimise a search - it is *not* an iterator



#ifndef FIELDSEARCHOPTIMISER_H
#define FIELDSEARCHOPTIMISER_H

#include "PartitionTypes.h"

namespace smf {

    class FieldSearchOptimiser{

    public:
	    FieldSearchOptimiser(){};

	    virtual bool index(PartitionTypes::LongIndexType&) = 0;
	    virtual void found() = 0;
	    virtual void found(PartitionTypes::LongIndexType index) = 0;
	    virtual void numAttempts(PartitionTypes::LongIndexType inStart, PartitionTypes::LengthType inSize) = 0;
	    virtual void set(FieldSearchOptimiser* ) = 0;

		virtual ~FieldSearchOptimiser() {}
    };
}

#endif