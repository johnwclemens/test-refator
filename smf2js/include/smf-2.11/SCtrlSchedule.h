#ifndef SCTRLSCHEDULE_H
#define SCTRLSCHEDULE_H

#include <vector>
#include <string>

namespace smf{
	class SCtrlSchedule
	{
	public:
		enum DaysOfWeek{
            Monday = 1,
            Tuesday = 2,
            Wednesday = 4,
			Thursday = 8,
			Friday = 16,
			Saturday = 32,
			Sunday = 64
        };

		enum TriggerType{
			TriggerDefault = 0,
			TriggerDisable,
			TriggerEnable,
		};

		typedef std::vector<smf::SCtrlSchedule::DaysOfWeek> DaysList;
		
		//! \brief Create the Periodic schedule
		//! \param days	The list stored the day of week when the schedule will run.
		//! \param minSinceMidNight	The time to run the schedule. It is the number of minutes since mid-night(00:00 am)
		//! \param trigger	The Schedule is enabled or not
		//! \param numWeeks	The interval of the number of week to repeated that schedule
		//! \exception smf::Error
		SCtrlSchedule(const DaysList& days, unsigned int minSinceMidNight, bool trigger, unsigned int numWeeks);
	
		//! \brief Create the Periodic schedule without the trigger status
		//! For new schedule task, the trigger will use system default.
		//! For existing schedule task, the trigger will no be changed
		//! \param days	The list stored the day of week when the schedule will run.
		//! \param minSinceMidNight	The time to run the schedule. It is the number of minutes since mid-night(00:00 am)
		//! \param numWeeks	The interval of the number of week to repeated that schedule
		//! \exception smf::Error
		SCtrlSchedule(const DaysList& days, unsigned int minSinceMidNight, unsigned int numWeeks);

		//! \brief Create the mon-Periodic schedule
		//! \param days	The list stored the day of week when the schedule will run.
		//! \param minSinceMidNight	The time to run the schedule. It is the number of minutes since mid-night(00:00 am)
		//! \param trigger	The Schedule is enabled or not
		//! \exception smf::Error
		SCtrlSchedule(const DaysList& days, unsigned int minSinceMidNight, bool trigger);
		
		//! \brief Create the mon-Periodic schedule without the trigger status
		//! For new schedule task, the trigger will use system default.
		//! For existing schedule task, the trigger will no be changed
		//! \param days	The list stored the day of week when the schedule will run.
		//! \param minSinceMidNight	The time to run the schedule. It is the number of minutes since mid-night(00:00 am)
		//! \exception smf::Error
		SCtrlSchedule(const DaysList& days, unsigned int minSinceMidNight);
		
		//! \brief Create the immediate triggered schedule
		//! \exception smf::Error
		SCtrlSchedule(); 

		//! \brief Get the list of the day of week in the schedule
		const DaysList& Days() const;

		//! \brief Get the trigger status in the schedule
		TriggerType Trigger() const;

		//! \brief Get the time to run the schedule.  It is the number of minutes since mid-night(00:00 am)
		unsigned int Time() const;

		//! \brief Get the interval of the number of week to repeated that schedule.
		unsigned int NumWeeks() const;
		
		//! \brief Whether it is immediate schedule
		bool Immediate() const;
		
		//! \brief Whether it is Periodic schedule
		bool IsPeriodic() const;

		//! \brief Convert the Time string to the number of minutes since mid-night(00:00 am)
		//! \param sTime The string contains the time information
		//! Format = HH:mm, eg: 01:30 and 18:05
		//! \exception smf::Error
		static unsigned int ConvertStrToTime(const std::string& sTime);
		
		//! \brief Convert the number of minutes since mid-night(00:00 am)
		//! \param HH The 24-hour value
		//! \param mm The minute value
		//! \exception smf::Error
		static unsigned int ConvertToTime(unsigned int HH, unsigned int mm);
		
		//! \brief Convert the number of minutes since mid-night(00:00 am) to string value
		//! The output format is HH:mm, eg: 01:30 and 18:05
		//! \param minSinceMidNight The number of minutes since mid-night(00:00 am)
		//! \exception smf::Error
		static std::string ConvertTimeToStr(unsigned int minSinceMidNight);

	private:
		DaysList days;
		unsigned int time;
		TriggerType trigger;
		unsigned int numWeeks;
		bool immediate;
	};
}

#endif