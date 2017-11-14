#ifndef DATETIMEENTRY_H
#define DATETIMEENTRY_H

#include <string>
#include <sstream>

#include "Error.h"
#include "DurationEntry.h"

namespace smf{
	class DateTimeEntry
	{
	public:
		class DateTimeFormatError : public smf::Error
		{
		public:
			DateTimeFormatError(const char *whichField, unsigned short wrongValue);
		};

        class OutOfRangeException : public smf::Error
        {
        public:
            OutOfRangeException();
        };

		DateTimeEntry();

		DateTimeEntry(unsigned short year, unsigned short month, unsigned short day,
			unsigned short hour, unsigned short minute, unsigned short second);
		
		DateTimeEntry(unsigned int date, unsigned int time);

		unsigned int DateAsDecimal() const ;

		std::string DateAsText() const;

		unsigned short Year() const;

		unsigned short Month() const;

		unsigned short DayInMonth() const;

		unsigned int SecondsSinceMidnight() const;

		unsigned short HourOfDay() const;

		unsigned short MinuteOfHour() const;

		unsigned short SecondOfMinute() const;

		bool operator ==(const DateTimeEntry& rhs);

		bool operator !=(const DateTimeEntry& rhs);

        DateTimeEntry AddSeconds(int NumSeconds) const;
        DateTimeEntry AddMinutes(int NumMinutes) const;
        DateTimeEntry AddHours(int NumHours) const;
        DateTimeEntry AddDays(int NumDays) const;
        DateTimeEntry AddDuration(DurationEntry duration) const;
        DateTimeEntry SubtractDuration(DurationEntry duration) const;

	private:
		unsigned int date;	// yyyymmdd
		unsigned int time;	// seconds since mid-night
	};
}

#endif
