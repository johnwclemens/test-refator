#ifndef LOGSERVICEREQUESTHANDLER_H
#define LOGSERVICEREQUESTHANDLER_H

#include "LogEntry.h"
#include "Types.h"

namespace smf{
	class UnstampedLogEntry;

	class LogServiceRequestHandler
	{
	public:
		class PredefinedLogEntry
		{
		public:
			/** 
				A consturctor of Predefined Log Entry.
				The severity of this LogEntry will base on the pre-defined message XML file
			*/
			//! \brief To send a log message to the server you must first create a smf::LogServiceRequestHandler::PredefinedLogEntry.
			//! This object is passed into the smf::LogServiceRequestHandler::Record function (see Sending Log Messages) to send the message to the SMF server.
			//! \param msgId			The message ID as defined in the Predefined Log XML config file
			//!	\param parameters		A list of parameters. In the case of a predefined log entry, the message will be expanded to contain these parameters.
			//! \param notifiable		If this is false, the message will go to the server but the server will not sent it on to listening applications.
			//!							In most cases this should be set to true.
			//! \remark 				Include: LogServiceRequestHandler.h, Error.h
			//! \exception smf::Error	See LogServiceRequestHandler.h for a list of specific exceptions.
			//! \note					This class is not thread safe.
			PredefinedLogEntry(
				unsigned int msgId,
				const LogEntry::Messages& parameters,
                bool notifiable = true)
			: logEntry(LogEntry::UnSpecify, msgId, parameters, notifiable)
			{
			}

			/** 
				A consturctor of Predefined Log Entry.
				User can specify the severity. It will override the severity which the pre-defined message XML is defined
			*/
			//! \brief To send a log message to the server you must first create a smf::LogServiceRequestHandler::PredefinedLogEntry.
			//! This object is passed into the smf::LogServiceRequestHandler::Record function (see Sending Log Messages) to send the message to the SMF server.
			//! \param severity			The severity of the message. Must be one of:
			//!							smf::LogEntry::Informational, smf::LogEntry::Warning, smf::LogEntry::Critical, smf::LogEntry::Clear 
			//!							Note: if an application sends a Critical event, it should follow it up with a clear event if the problems is resolved.
			//! \param msgId			The message ID as defined in the Predefined Log XML config file
			//!	\param parameters		A list of parameters. In the case of a predefined log entry, the message will be expanded to contain these parameters.
			//! \param notifiable		If this is false, the message will go to the server but the server will not sent it on to listening applications.
			//!							In most cases this should be set to true.
			//! \remark 				Include: LogServiceRequestHandler.h, Error.h
			//! \exception smf::Error	See LogServiceRequestHandler.h for a list of specific exceptions.
			//! \note					This class is not thread safe.
			PredefinedLogEntry(
				LogEntry::Severity severity, 
				unsigned int msgId,
				const LogEntry::Messages& parameters,
                bool notifiable = true)
			: logEntry(severity, msgId, parameters, notifiable)
			{
			}

			const LogEntry &GetEntry() const {return logEntry;}
		private:
			const LogEntry logEntry;
		};

		class FreeFormatLogEntry
		{
		public:

			//! \brief To send a log message to the server you must first create a smf::LogServiceRequestHandler::FreeFormatLogEntry.
			//! This object is passed into the smf::LogServiceRequestHandler::Record function (see Sending Log Messages) to send the message to the SMF server.
			//! \param severity			The severity of the message. Must be one of:
			//!							smf::LogEntry::Informational, smf::LogEntry::Warning, smf::LogEntry::Critical, smf::LogEntry::Clear 
			//!							Note: if an application sends a Critical event, it should follow it up with a clear event if the problems is resolved.
			//! \param message			A string containing the free format log message.
			//!							Note: this string is passed as is onto the server. 
			//!	\param parameters		A list of parameters. In the case of a predefined log entry, the message will be expanded to contain these parameters.
			//! \param notifiable		If this is false, the message will go to the server but the server will not sent it on to listening applications.
			//!							In most cases this should be set to true.
			//! \remark 				Include: LogServiceRequestHandler.h, Error.h
			//! \exception smf::Error	See LogServiceRequestHandler.h for a list of specific exceptions.
			//! \note					This class is not thread safe.
			FreeFormatLogEntry(
				LogEntry::Severity severity, 
				const char *message,
				const LogEntry::Messages& parameters,
                bool notifiable = true)
			: logEntry(severity, message, parameters, notifiable)
			{
			}

			const LogEntry &GetEntry() const {return logEntry;}
		private:
			const LogEntry logEntry;
		};
		

		//! \brief To receive log messages you must first subscribe to the log service.
		//! (see Opening a Log Service Request Channel for how to get a LogServiceRequestHandler)
		//! \param id			This is an identifier defined by the application. 
		//!						SMF does not use it; 
		//!						SMF will pass this back to you when reporting whether the subscription was accepted or not through your LogServiceResponseHandler implementation.
		//! \remark 				Include: LogServiceRequestHandler.h, LogServiceResponseHandler, Error.h
		//! \exception smf::Error	See LogServiceRequestHandler.h for a list of specific exceptions.
		//! \note					The subscribe function is thread safe.
		//! \post					Once successfully subscribed you will be sent all log messages through your LogServiceResponseHandler implementation
		//!							through the smf::LogServiceResponseHandler::Report function
		virtual void Subscribe(UnsignedInt id) = 0;
		virtual void Unsubscribe(UnsignedInt id) = 0;

		//! \brief To send log messages use the LogServiceRequestHandler returned when you opened a connection to the log service. 
		//! (see Opening a Log Service Request Channel for how to get a LogServiceRequestHandler)
		//! \param id					This is an identifier defined by the application. 
		//!								SMF does not use it; SMF will pass this back to you if it needs to report a failure.
		//!								This identifier will not be passed on with the log message.
		//! \param predefinedLogEntry	This contains the log message ID as defined in the Predefined Log XML config file.
		//! \remark 					Include: LogServiceRequestHandler.h, Error.h
		//! \exception smf::Error		See LogServiceRequestHandler.h for a list of specific exceptions.
		//! \note						This function is thread safe.
		//!								This function will return immediately once the message has been queued internally. If the queue is full an exception (LogServiceRequestHandler::CouldNotHandleRequest) will be thrown.
		virtual void Record(UnsignedInt id, const PredefinedLogEntry &predefinedLogEntry) = 0;

		//! \brief To send log messages use the LogServiceRequestHandler returned when you opened a connection to the log service. 
		//! (see Opening a Log Service Request Channel for how to get a LogServiceRequestHandler)
		//! \param id					This is an identifier defined by the application. 
		//!								SMF does not use it; SMF will pass this back to you if it needs to report a failure.
		//!								This identifier will not be passed on with the log message.
		//! \param freeFormatLogEntry	This contains the log message.  See Free Format Log Entries.
		//! \remark 					Include: LogServiceRequestHandler.h, Error.h
		//! \exception smf::Error		See LogServiceRequestHandler.h for a list of specific exceptions.
		//! \note						This function is thread safe.
		//!								This function will return immediately once the message has been queued internally. If the queue is full an exception (LogServiceRequestHandler::CouldNotHandleRequest) will be thrown.
		//! \see 						Free Format Log Entries
		virtual void Record(UnsignedInt id, const FreeFormatLogEntry &freeFormatLogEntry) = 0;
		virtual ~LogServiceRequestHandler(){}

		// this one should not be used
		virtual void Record(UnsignedInt id, const LogEntry &) = 0;

		//! This can be used to send a non-predefined message with a message ID
		//! \brief To send log messages use the LogServiceRequestHandler returned when you opened a connection to the log service. 
		//! (see Opening a Log Service Request Channel for how to get a LogServiceRequestHandler)
		//! \param id					This is an identifier defined by the application. 
		//!								SMF does not use it; SMF will pass this back to you if it needs to report a failure.
		//!								This identifier will not be passed on with the log message.
		//! \param unstampedLogEntry	This contains the log message and message ID
		//! \remark 					Include: LogServiceRequestHandler.h, Error.h
		//! \exception smf::Error		See LogServiceRequestHandler.h for a list of specific exceptions.
		//! \note						This function is thread safe.
		//!								This function will return immediately once the message has been queued internally. If the queue is full an exception (LogServiceRequestHandler::CouldNotHandleRequest) will be thrown.
		virtual void Record(UnsignedInt id, const UnstampedLogEntry &unstampedLogEntry) = 0;

	public:	// exceptions

		class SizeLimitExceedsAllocationLimit : public Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details) : Error(details)
			{
			}
		};

		class CouldNotGetBuffer : public Error
		{
		public:
			CouldNotGetBuffer(unsigned int size)
				: Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}
		};

		class CouldNotHandleRequest : public Error
		{
		public:
			CouldNotHandleRequest()
				: Error("LogServiceRequestHandler could not handle request "
					"because the queue of the client service is full")
			{
				  
			}
		};

		class ConnectionDropped : public Error
		{
		public:
			ConnectionDropped() 
				: Error("The connection to the server has been closed or dropped")
			{
			}
		};

		class MessageFileLoadFailed : public Error
		{
		public:
			MessageFileLoadFailed(const char *filename, unsigned int errorCode)
				: Error("Failed to load the message file ")
			{
				*this << filename << ". ErrorCode: " << errorCode;
			}
		};

		class MessageFileNotDefined : public Error
		{
		public:
			explicit MessageFileNotDefined(unsigned int messageId)
				: Error("Logging by log message ID"
				" but the message file is not defined. Message id: ")
			{
				*this << messageId;
			}
		};


		class GetProcessInfoFailed : public Error
		{
		public:
			GetProcessInfoFailed() : Error("Failed to get the current process information")
			{
			}
		};

		class InvalidLogEntry : public Error
		{
		public:
			InvalidLogEntry()
				: Error("The log entry should contain either message ID"
					" or the message text, but not both")
			{
			}
		};
	};
}


#endif
