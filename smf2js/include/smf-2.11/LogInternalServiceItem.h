
#ifndef LOGINTERNALSERVICEITEM_H
#define LOGINTERNALSERVICEITEM_H

#include "InternalService.h"
#include "PoolState.h"

namespace smf{
	class LogInternalServiceItem:
		public smf::InternalService::InternalItem,
		public PoolState
	{
	public:
		virtual ~LogInternalServiceItem(){}

		virtual void Create(smf::DateTimeEntry,
							smf::LogEntry::Severity severity, 
							const char *message, 
							const smf::LogEntry::Messages& parameters,
							const char* processName,
							bool notifyClients
							) = 0;
	};
}
#endif