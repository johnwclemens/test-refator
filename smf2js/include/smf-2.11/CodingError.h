
#ifndef CODINGERROR_H
#define CODINGERROR_H

#include "Error.h"

namespace smf{
	class CodingError: public smf::Error
	{

	public:
		CodingError(const char *where, const char *description);
	};
}

#endif