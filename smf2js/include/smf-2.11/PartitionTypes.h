
#ifndef PARTITIONTYPES_H
#define PARTITIONTYPES_H

#include "BinaryType.h"

namespace smf{

    namespace PartitionTypes{

	    // primitive types
	    typedef int IntegerType;
	    typedef char CharType;
		#ifdef _WIN32
			typedef __int64 Integer64Type;
		#else
			typedef long long Integer64Type;
		#endif 
		typedef double DoubleType;

	    // memory block related
	    typedef unsigned int SizeType;		// e.g. field size
	    typedef unsigned int OffsetType;	// e.g. offset of a field

	    // dimemsions
	    typedef unsigned short LengthType;	// e.g. string length
	    typedef unsigned short IndexType;	// for arrays
	    typedef unsigned int LongIndexType; //e.g. for group index (not group array index)
	    typedef unsigned int LongLengthType;

	    typedef unsigned char FlagType; // 
    }
}
#endif