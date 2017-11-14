
#ifndef SMF_BinaryType_H
#define SMF_BinaryType_H

#include "Error.h"

namespace smf{

	class BinaryType{

	public:
		typedef unsigned int SizeType;

		//to create an empty buffer to read into
		BinaryType(void* buffer, SizeType limit);
		//to create a buffer with data
		BinaryType(void* buffer, SizeType dataSize, SizeType limit);


		SizeType Limit() const;
		SizeType DataSize() const;
		void DataSize(BinaryType::SizeType size) ;
		void* Data() const;

	private:

		void CheckLimit();

		SizeType limit;
		SizeType dataSize;
		void* buffer;

	};

}
#endif