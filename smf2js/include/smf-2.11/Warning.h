#ifndef WARNING_H
#define WARNING_H

#include "LogMsg.h"

namespace smf{
	class Warning: public LogMsg{

	public:
		virtual ~Warning();
		Warning(const char* warn);

	private:

		Warning();


	};
}


#endif