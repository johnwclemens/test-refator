
#ifndef CRITICALERROR_H
#define CRITICALERROR_H

#include "Error.h"

namespace smf{

	class CriticalError:
		public smf::Error
	{

	public:
		CriticalError(const char *description);
	};

}
#endif