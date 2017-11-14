#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include "Error.h"
#include "StatsValue.h"

#ifdef WIN32
#include "Windows.h"
#else 
#include "sys/time.h"
#endif

namespace smf
{
#ifdef WIN32
    typedef ::FILETIME WinFileTime;
    struct UnixTimeVal
    {
        long    tv_sec;         
        long    tv_usec;        
    };
    typedef unsigned __int64 NumMicroSecSinceMidnight;
#else
    struct WinFileTime
    {   
        unsigned int dwLowDateTime;
        unsigned int dwHighDateTime;
    };
    typedef  struct timeval UnixTimeVal;
     typedef unsigned long long NumMicroSecSinceMidnight;
#endif

    class TimeStamp{

	    public:	// type definitions 
                    
		    struct TimeValue{
                StatsValue::Integer64Type sec; // number of seconds since January 1, 1601 UTC
                int nanosec;                   // the remining nano-seconds
		    };           

        public: // construction

		    TimeStamp();
            TimeStamp(const WinFileTime& ft);
            TimeStamp(const UnixTimeVal& tv);
		    TimeStamp(const TimeValue& time); 
          
		    ~TimeStamp();

	    public: // access methods
                        
            void Set(const WinFileTime& ft);
            void Set(const UnixTimeVal& tv);
		    void Set(const TimeValue& time); 
                   
            //! \brief Use this function to get the time stamp in Window FILETIME format
            //! \return					The Window FILETIME structure            		    		    
		    //! \note					This function is thread safe.             
            WinFileTime AsWinFileTime() const; 

            //! \brief Use this function to get the time stamp in Solaris/Linux struct timeval format
            //! \return					The Solaris/Linux struct timeval structure           		    		    
		    //! \note					This function is thread safe.             
            UnixTimeVal AsUnixTimeVal() const; 

		    //! \brief Use this function to get the time stamp in TimeValue structure
            //! \return					The TimeValue structure           		    		    
		    //! \note					This function is thread safe.             
            TimeValue AsNanoSec() const; 
		
            //! \brief Use this function to get the time stamp in text formatted as [Jan,Feb,Mar...]/dd/yyyy HH:MM:SS.xxxxxxxxx GMT
            //! \param numDecimal       The number of decimal places in the string;
            //!                         If the value is 0, no decimal is shown;
            //!                         If the value is greater than 9, only 9 decimal places are dipalyed. 
		    //! \return					The formatted string.            		    		    
		    //! \note					This function is thread safe. 
            std::string AsText(unsigned int numDecimal = 9) const; 

            NumMicroSecSinceMidnight AsNumMicroSecFromMidnightGMT() const;

		    TimeStamp operator -(const TimeStamp&) const;
		    bool operator ==(const TimeStamp&) const;
		    bool operator !=(const TimeStamp&) const;

	    private:
		    TimeValue m_time;
	};

}

#endif
