#ifndef SERVICEBUFFERPOOL_H_
#define SERVICEBUFFERPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;
class ClientResponseServiceBufferPool;

namespace smf {
	class ServiceBufferPool
	{
	public:
		
		virtual ~ServiceBufferPool() {}

		class IncorrectTypeInDestoryServiceBufferPool:
		public smf::Error
		{
		public:
			ServiceBufferPool  *received;
			const char* expected;
			IncorrectTypeInDestoryServiceBufferPool(const char* expected, ServiceBufferPool* received);

		};

		virtual ClientResponseServiceBufferPool* GetResponseServiceBufferPool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
