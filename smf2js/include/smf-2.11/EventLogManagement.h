#ifndef EVENTLOGMANAGEMENT_H
#define EVENTLOGMANAGEMENT_H

#include "Warning.h"
#include "Error.h"
#include "Logger.h"

#include <string>

//! LOG Service - Event Log Management
//! This interface is for the client to mangement the event
//! Currently, the API can only be used locally
//! 

namespace smf{
	class EventLogManagement
	{
	public:
		class ConnectionFail:
		public smf::Error
		{
		public:
			ConnectionFail():smf::Error("The connection to the server cannot be established"){
			}

		};

		virtual ~EventLogManagement() {}

		//! \brief Set the hold on time of any critical event send to GMI.		
		//! \param timeInMs	The hold on time of any critical event in millisecond.
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual void SetGMIEventHoldTime(unsigned int timeInMs) =0;

		//! \brief Get the hold on time of any Critical event send to GMI.		
		//! \note	The function is thread safe.
		//!			This function will return immediately.
		virtual unsigned int GetGMIEventHoldTime() =0;
	};
}
#endif