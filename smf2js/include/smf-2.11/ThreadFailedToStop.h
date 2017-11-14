
#ifndef THREADFAILEDTOSTOP_H
#define THREADFAILEDTOSTOP_H

#include "CriticalError.h"

namespace smf{
	//this may be thrown to the client app, but they don't see the Thread interface
	//so we need to expose it to the client app specifically here
	class ThreadFailedToStop:
		public smf::CriticalError
	{
	public:
		ThreadFailedToStop(unsigned int stoptimeout, unsigned int threadid);
	};
}

#endif
