////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 by
// Reuters Hong Kong Ltd. Technical Development, Hong Kong
// All rights reserved.
//
// No portion of this software in any form may be used or reproduced in
// any manner without written consent from Reuters Asia PTE Ltd.
//
// You must not remove this notice, or any other, from this software.
//


#ifndef ERRORREASON_H
#define ERRORREASON_H

#include <map>
#include <string>

namespace smf2js
{
	class ErrorReason
	{
	public:
		ErrorReason(void);
		ErrorReason(const char* const* reasons);

		void Set(const char* const* reasons);

		std::string ReasonToString(unsigned long indx) const;

		void Add(unsigned long reason, std::string& detail);

	private:
		typedef std::map< unsigned long, std::string > Reasons;
		Reasons reasons;

	};
}

#endif
