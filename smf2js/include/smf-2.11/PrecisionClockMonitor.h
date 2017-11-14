#ifndef PPRECISIONCLOCKMONITOR_H
#define PPRECISIONCLOCKMONITOR_H

#include "PrecisionTimeService.h"
#include <string>

namespace smf
{
    class PrecisionClockMonitor
    {
   	public: // construction
          
        PrecisionClockMonitor() {}
        virtual ~PrecisionClockMonitor() {}    

    public: // access methods

        //! \brief Use this function to check the current synchronization status of the system        
        //! \return					         If it returns true, the system is synchronized with the current time protocol
        //! \note This function is thread-safe. 
		virtual bool IsServerClockSync() = 0;

        //! \brief Use this function to retrieve the time protocol name currently used by the system
        //! \exception smf::Error You should at least catch smf::Error.  
		//! \remark    Include: PrecisionClockMonitor.h
		//! \note      The pointer returned is the internal storage of the protocol name. 
        //!            You have to convert the pointer into a sting object if the value will be carried around
		virtual const char* GetActiveProtocol() = 0;        
        
        //! \brief Use this function to retrieve a list of current master clock information
        //!        The statistic will be stored in the clockInfoArray object
        //! \param     clockInfoArray A list of MasterClockInfo for storing the statistic from each master clock
        //! \exception      smf::Error You should at least catch smf::Error.  
		//! \remark         Include: PrecisionClockMonitor.h, PrecisionTimeService.h, MasterClockInfo.h, Error.h
		//! \note      This function is thread safe.
        virtual void GetMasterClockInfo(PrecisionTimeService::MasterClockInfoArray& clockInfoArray) = 0; 
		
    };

}

#endif 