
#ifndef LOGLINEFORMATTER_H
#define LOGLINEFORMATTER_H

namespace smf{
	//All logline formatter interfaces should derive from this
	class LogLineFormatter
	{
	protected:
		virtual ~LogLineFormatter() = 0;

	};
}

#endif