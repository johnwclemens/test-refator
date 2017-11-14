#ifndef FILETRANSFERSERVICERESOURCEPOOL_H_
#define FILETRANSFERSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class FileTransferServiceResourcePool
	{
	public:
		virtual ~FileTransferServiceResourcePool() {};

		class IncorrectTypeInDestoryFileTransferServiceResourcePool:
		public smf::Error
		{
		public:
			FileTransferServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryFileTransferServiceResourcePool(const char* expected, FileTransferServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
