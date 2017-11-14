
#ifndef ERROR_H
#define ERROR_H

#include "LogMsg.h"

namespace smf{
	class Error: public smf::LogMsg{

	public:
		virtual ~Error();


		//for use by dummy error
		Error(const char* file, int line);
		Error(const char* error);
	private:

		Error();


	};
}


#ifdef _DEBUG
#define dummy_error smf::Error(__FILE__,  __LINE__);
#define DBG_THROW throw
#else
//dummy_error is not defined because in release build it should be replaced with proper error handling;
//

#define DBG_THROW
#endif

#endif