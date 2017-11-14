#ifndef STATSVALUE_H
#define STATSVALUE_H

#include <string>
#include "Error.h"

namespace smf{

	class StatsValue{
	 
	    public: // construction
          
            typedef std::string StringType;
#ifdef Win32
            typedef __int64 Integer64Type;
#else
            typedef long long Integer64Type;
#endif

            StatsValue();

            StatsValue(StringType &statsName, StringType &statsValue);

            StatsValue(StringType &statsName, Integer64Type statsValue);

		    ~StatsValue();

	    public: // access methods
            
		    StringType GetStatsName() const;
            
            //! \brief This function returns true if string type object is stored 
            //! \note This function is thread safe. 
            bool IsInteger64() const;
            
            //! \brief This function returns true if 64-bit type object is stored 
            //! \note This function is thread safe. 
            bool IsString() const;            

            //! \brief Use this function for returning the string value stored in the object
            //! \exception smf::Error
            //! \note This functions are thread safe. You have to use the corresponding function to access the value of the same type. 
            //!       For example, an smf::Error will be thrown if you try to query an integer for a string type statistic. 
            Integer64Type GetIntValue() const;
            
            //! \brief Use this function for returning the string value stored in the object
            //! \exception smf::Error
            //! \note This function are thread safe. You have to use the corresponding function to access the value of the same type. 
            //!       For example, an smf::Error will be thrown if you try to query a string for a integer type statistic. 
            StringType GetStringValue() const;         

	    private:

		    StringType m_statsName;
            StringType m_strValue;
            Integer64Type m_intValue;
            bool isInt64;
            bool isStr;
	};

}

#endif


