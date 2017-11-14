#ifndef PSDHANDLE_H
#define PSDHANDLE_H

#pragma warning (disable : 4786)
#include <string>

namespace smf{
	class PsdHandle
	{
	public:

		typedef unsigned int HandleType;

		PsdHandle() ;

		explicit PsdHandle(HandleType h) ;

		HandleType Handle() const;

		
	private:
		HandleType handle;
	};
}

#endif
