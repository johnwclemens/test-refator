
#ifndef STREAMLOGLINEFORMATTER_H
#define STREAMLOGLINEFORMATTER_H

#include "StandardLogLineFormatter.h"
#include "OutputStream.h"

namespace smf{
	class StreamLogLineFormatter:
		public StandardLogLineFormatter
	{
	public:

		
		virtual void SetStream(smf::OutputStream* out) = 0;
	
		virtual ~StreamLogLineFormatter() = 0;
	};
}

#endif