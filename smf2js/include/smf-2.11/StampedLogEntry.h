#ifndef STAMPEDLOGENTRY_H
#define STAMPEDLOGENTRY_H

#include <string>
#include <vector>
#include "UnstampedLogEntry.h"

namespace smf{
	class StampedLogEntry
	{
	public:
		StampedLogEntry();
		StampedLogEntry(
			unsigned short year, unsigned short month, unsigned short day,
			unsigned short hour, unsigned short minute, unsigned short second,
			unsigned int seqNo,
			const smf::UnstampedLogEntry &unstampedLogEntry
			);

		StampedLogEntry(
			smf::DateTimeEntry serverDateTime, 
			unsigned int seqNo,
			const smf::UnstampedLogEntry &unstampedLogEntry);

		unsigned int SeqNo() const;
		const smf::DateTimeEntry &DateTime() const;
		const smf::UnstampedLogEntry &LogEntry() const;

	private:
		smf::UnstampedLogEntry unstampedLogEntry;
		smf::DateTimeEntry serverDateTime;
		unsigned int seqNo;
	};
}

#endif
