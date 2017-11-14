#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>
#include <vector>
#include "Error.h"

namespace smf{
	class LogEntry
	{
	public:	//! exception

		class ErrorTooManyMessages:
			public smf::Error
		{
		public:
			ErrorTooManyMessages(size_t number);
			  
		};

	public:	// type definitions and constants

		typedef std::vector<std::string> Messages;

		enum Severity
		{
			Harmless,
			Informational = Harmless,
			Warning,
			Critical,
			Clear,
			Unknown,			//!< this is an error
			UnSpecify = Unknown	//!< this is for an empty severity LogEntry, used for pre-defined log
		};

		enum
		{
			//!There are two types of messages:
			//!1) Free text messages
			//!2) Predefined messages
			//!Predefined messages are represented by a message ID and loaded from an XML file
			//!We use the message ID 0 to represent free text messages. Hence a message ID
			//!of 0 is not allowed.
			InvalidMessageId = 0
		};

	public:	// construction

		LogEntry();

		LogEntry(Severity severity, unsigned int messageId, 
			const Messages& parameters, bool notifyOtherLogSubscribers = true);

		LogEntry(Severity severity, const char *message, 
			const Messages& parameters, bool notifyOtherLogSubscribers = true);

		LogEntry(Severity severity, unsigned int messageId, const char *message, 
			const Messages& parameters, bool notifyOtherLogSubscribers = true);

		LogEntry(Severity severity, unsigned int messageId, const char *message, 
			const std::vector<const char*>& parameters, bool notifyOtherLogSubscribers = true);
	private:

		class SeverityToName{
		public:
			SeverityToName(Severity s, const char* name):
			severity(s), name(name)
			{
			}
			
			Severity severity;
			std::string name;
		};
		typedef std::vector<SeverityToName> SeveritiesToNames;
		static SeveritiesToNames SeverityNameMapping();


	public:	// access methods

		Severity SeverityAsCode() const;
		std::string SeverityAsText() const;
		static Severity TextToSeverity(const char* text);
		unsigned int MessageId() const;
		const Messages& Message() const;

		size_t MessageCount() const;
		//these methods provide some checking on the index
		size_t MessageSize(size_t index) const;
		const char* Message(size_t index)const;

        bool NotifyOtherLogSubscribers() const;
		
		bool operator==(const LogEntry &entry) const;
		bool operator!=(const LogEntry &entry) const;

	private:
		
		template <typename StringType>
			void Construct(const char* message, const std::vector<StringType>& parameters);
		void AddParameter(const std::string& str);
		void AddParameter(const char* str);
		
		Severity severity;
		unsigned int mid;
		Messages messages;
        bool notifyOtherLogSubscribers;
	};
}	
#endif
