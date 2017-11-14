
#ifndef FILELOGGERENTRYPOINT_H
#define FILELOGGERENTRYPOINT_H

#include "Logger.h"


namespace smf{
	//! \brief This function gets a pointer to the internal logger (for writing direct to a local log file) and set’s the log file. 
	//! Note: this is not the log service; any log messages will not go through to the main server log. If you wish to use the log service see Using the Log Service.
	//! \param logfile		The name of the logfile. This can be a relative path or full path.
	//!						Note: if this is null, a pointer to the internal logger will be returned without changing the log file or the max size of the log file.
	//! \param maxsize		The maximum size of the log file in bytes. Smf will keep upto 10 files each of this size.
	//! \param logToStdOut	If this is false log messages will only be printed to the log file. Otherwise log messages will be printed to file and stdout.
	//! \return An smf::Logger pointer.
	//! \remark	Include: FileLoggerEntryPoint.h, Logger.h
	//! \post	Cleanup: This is an internal SMF object that is created by SMF when it starts and SMF is responsible for clearing it up. 
	//! \exception smf::Error
	//!	\note This function is thread safe, but it is recommended that you call it when you first start up and thereafter pass the smf::Logger pointer around, 
	//! or, thereafter call it with a null logfile pointer to simply retrieve the internal logger pointer.
	Logger* InternalLogger(const char* logfile, unsigned int maxsize, bool logToStdOut = true);
}

#endif
