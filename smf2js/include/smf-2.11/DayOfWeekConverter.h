#ifndef DAYOFWEEK
#define DAYOFWEEK

#include "Error.h"
#include <string>
#include <map>

namespace smf{
	class DayOfWeekConverter
	{
	public:
		class IncorrectSpecification:
			public smf::Error
		{
		public:
			IncorrectSpecification(const char* what);
		};
		DayOfWeekConverter();
		int ToLong(const char *);
		const char *ToString(int);
	private:
		typedef std::map<std::string, unsigned int> DayOfWeekToLong;
		DayOfWeekToLong dayOfWeekToLong;
		static const char *longToDayOfWeek[7];
	};
}

#endif
