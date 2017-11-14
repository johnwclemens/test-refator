#ifndef PRECISIONTIMESERVICE_H
#define PRECISIONTIMESERVICE_H

#include <vector>
#include <map>

namespace smf
{

	class Logger;
	class PrecisionClock;
	class StatsValue;	   
    class MasterClockInfo;      
    class PrecisionClockMonitor;      

	namespace PrecisionTimeService
    {                
        typedef std::vector<MasterClockInfo> MasterClockInfoArray;        

        const char* LibName();
        
        //! \brief Before using Precision Clock service, you need to set up an internal logger. This function will also initialize the internal structure for the service
        //!        See Getting a Pointer to the Internal Logger for how to create an internal logger. 
        //! \param logger          A local logger created using smf::InternalLogger() function.  
        //! \param timeout         The global timeout value for getting clock statistic
        //!                        If you pass zero here the default timeout will be used.
        //! \remark                Include: Logger.h, Error.h
        //! \note                  This should *not* be called by multiple threads. 
        //!                        This function is thread safe, but you should only need to call them once during startup. 
        void SetInternalLogger(Logger* internalLogger, unsigned int timeout = 0);

		//! \brief Use this function to create a PrecisionClock. A PrecisionClock is a C++ object that representing the precision clock synchronized with current time protocol
		//! \param logger			A local logger created using smf::InternalLogger() function. See Opening a Logger. 						
		//! \return					A pointer to a PrecisionClock object.
		//!	\remark					Include: PrecisionClock.h, Logger.h, Error.h
		//! \post					Cleanup: You must call smf::DestroyPrecisionClock to cleanup (see Cleaning Up).
		//! \exception				You should at least catch smf::Error. 
		//! \note					This function is thread safe. 
		PrecisionClock* CreatePrecisionClock(
				Logger* logger						
				);

		void DestroyPrecisionClock(PrecisionClock* clock);
        
        //! \brief Use this function to create a PrecisionClockMonitor. A PrecisionClockMonitor is a C++ object able to return system statistic about the time protocol
		//! \param logger			A local logger created using smf::InternalLogger() function. See Opening a Logger. 						
		//! \return					A pointer to a PrecisionClockMonitor object.
		//!	\remark					Include: PrecisionClockMonitor.h, Logger.h, Error.h
		//! \post					Cleanup: You must call smf::DestroyClockMonitor to cleanup (see Cleaning Up).
		//! \exception				You should at least catch smf::Error. 
		//! \note					This function is thread safe. 
        PrecisionClockMonitor* CreateClockMonitor(Logger* logger);

        void DestroyClockMonitor(PrecisionClockMonitor* monitor);
		
	}
}

#endif