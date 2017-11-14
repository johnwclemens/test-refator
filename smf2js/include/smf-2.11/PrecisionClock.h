#ifndef PRECISIONCLOCK_H
#define PRECISIONCLOCK_H

#include "PrecisionTimeService.h"
#include "TimeStamp.h"

namespace smf{

	class PrecisionClock
	{	
	public:	// type definitions and constants

		enum Status{
			Success,
			Fail,
			SuccesWithLowPrecisionTime
		};

	public: // construction

        PrecisionClock() {}
        virtual ~PrecisionClock() {}

	public: // access methods
        
        //! \brief Use this function to retrieve the current statistic of the current precision clock. 
        //!        The statistic will be stored in the info object
        //! \param     info A MasterClockInfo for storing the statistic information
        //! \exception      smf::Error You should at least catch smf::Error.  
		//! \remark         Include: PrecisionClock.h, MasterClockInfo.h, Error.h
		//! \note      This function is thread safe.
        virtual void GetClockInfo(MasterClockInfo &info) = 0;
        
        //! \brief Use this function to retrieve the time protocol name of current precision clock.         
        //! \exception smf::Error You should at least catch smf::Error.  
		//! \remark    Include: PrecisionClock.h
		//! \note      The pointer returned is the internal storage of the protocol name. 
        //!            You have to convert the pointer into a sting object if the value will be carried around
        virtual const char* GetProtocol() const = 0;

        //! \brief Use this function to retrieve current time timestamp from the precision clock.         
        //! \param ts                        A Timestamp object for storing the current timestamp
        //! \param tryLowerPrecisionProtocol If it is set to true, the method returns the timestamp from the OS clock whenever getting timestamp from specific protocol fails.
        //! \return					         The return code represents the status
        //!                                  Success:                    The method can get the timestamp from the precision clock. 
        //!                                                              The value in ts is valid
        //!                                  Fail:                       The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is invalid
        //!                                  SuccesWithLowPrecisionTime: The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is the timestamp from the OS clock
        //! \note This function is thread-safe. The API speed varies from platforms and the time protocols
        virtual Status GetPrecisionTime(TimeStamp& ts, bool tryLowerPrecisionProtocol = false) const = 0;

        //! \brief Use this function to retrieve current time timestamp from the precision clock.         
        //! \param ts                        A WinFileTime object for storing the current timestamp, which has the same structure as FILETIME in Window
        //! \param tryLowerPrecisionProtocol If it is set to true, the method returns the timestamp from the OS clock whenever getting timestamp from specific protocol fails.
        //! \return					         The return code represents the status
        //!                                  Success:                    The method can get the timestamp from the precision clock. 
        //!                                                              The value in ts is valid
        //!                                  Fail:                       The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is invalid
        //!                                  SuccesWithLowPrecisionTime: The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is the timestamp from the OS clock
        //! \note This function is thread-safe. The API speed varies from platforms and the time protocols
        virtual Status GetPrecisionTime(WinFileTime& ts, bool tryLowerPrecisionProtocol = false) const = 0;

        //! \brief Use this function to retrieve current time timestamp from the precision clock.         
        //! \param ts                        A Timestamp object for storing the current timestamp, which has the same structure as struct timeval in Solaris
        //! \param tryLowerPrecisionProtocol If it is set to true, the method returns the timestamp from the OS clock whenever getting timestamp from specific protocol fails.
        //! \return					         The return code represents the status
        //!                                  Success:                    The method can get the timestamp from the precision clock. 
        //!                                                              The value in ts is valid
        //!                                  Fail:                       The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is invalid
        //!                                  SuccesWithLowPrecisionTime: The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is the timestamp from the OS clock
        //! \note This function is thread-safe. The API speed varies from platforms and the time protocols
        virtual Status GetPrecisionTime(UnixTimeVal& ts, bool tryLowerPrecisionProtocol = false) const = 0;
   
        //! \brief Use this function to retrieve current time timestamp from the precision clock.         
        //! \param ts                        A Timestamp object for storing the current timestamp as the number of micro seconds since midnight on the same day
        //! \param tryLowerPrecisionProtocol If it is set to true, the method returns the timestamp from the OS clock whenever getting timestamp from specific protocol fails.
        //! \return					         The return code represents the status
        //!                                  Success:                    The method can get the timestamp from the precision clock. 
        //!                                                              The value in ts is valid
        //!                                  Fail:                       The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is invalid
        //!                                  SuccesWithLowPrecisionTime: The method fails to get the timestamp from the precision clock. 
        //!                                                              The value in ts is the timestamp from the OS clock
        //! \note This function is thread-safe. The API speed varies from platforms and the time protocols
        virtual Status GetPrecisionTime(NumMicroSecSinceMidnight& tsFromMidnightInMicroSec, bool tryLowerPrecisionProtocol = false) const = 0;
       
	};
}

#endif

