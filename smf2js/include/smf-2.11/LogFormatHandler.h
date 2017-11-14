
#ifndef LOGFORMATHANDLER_H
#define LOGFORMATHANDLER_H

#include "Recorder.h"

namespace smf{
	class LogFormatHandler
	{
	public:
		virtual bool RegisterRecorder(const char* configname, const Recorder& recorder) = 0;

		virtual ~LogFormatHandler() {}
	};
}
#endif