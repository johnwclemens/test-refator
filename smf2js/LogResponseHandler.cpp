#include <sstream>
#include <iostream>
#include "LogResponseHandler.h"
#include "ErrorReason.h"


smf2js::LogResponseHandler::LogResponseHandler(smf::Logger* logger) :log(logger)
{ }


smf2js::LogResponseHandler::~LogResponseHandler()
{
}

void smf2js::LogResponseHandler::Report(ResponseLogEntry& entry)
{
	std::ostringstream msg;
	msg << "[" << entry.SeverityAsText() << "]" 
		<< "\n  " << "S[" << FormattedDate(entry.ServerDateTime()) << "T"
		<< FormattedTime(entry.ServerDateTime()) << "]::"
		<< "C[" << FormattedDate(entry.ClientDateTime()) << "T"
		<< FormattedTime(entry.ClientDateTime()) << "]::"
		<< "[" << entry.AppName() << "]::"
		<< "PID[" << entry.ProcessId() << "]::"
		<< "TID[" << entry.ThreadId() << "]"
		<< "\n  M[" << FormattedMessage(entry) << "]"
		<< "\n\n";

	log << msg.str().c_str();
}

void smf2js::LogResponseHandler::ReportFailure(UnsignedInt id, UnsignedInt reason, const char* info)
{
	ErrorReason errorReason;
	std::ostringstream msg;
	msg << "Log enrty failed for " << id << " because: "
		<< errorReason.ReasonToString(reason).c_str() << " Info:"
		<< info
		<< "\n\n";

	log << msg.str().c_str();
}

void smf2js::LogResponseHandler::SubscriptionSuccessful(UnsignedInt id)
{
	std::ostringstream msg;
	msg << "Subscribed: " << id << "\n\n";

	log << msg.str().c_str();
}

void smf2js::LogResponseHandler::SubscriptionFailed(UnsignedInt id, UnsignedInt reason)
{
	ErrorReason errorReason;
	std::ostringstream msg;
	msg << "Subscription failed: " << id << " because: "
		<< errorReason.ReasonToString(reason).c_str()
		<< "\n\n";

	log << msg.str().c_str();
}

void smf2js::LogResponseHandler::UnsubscribeSuccessful(UnsignedInt id)
{
	std::ostringstream msg;
	msg << "Unsubscribed: " << id << "\n\n";

	log << msg.str().c_str();
}

void smf2js::LogResponseHandler::UnsubscribeFailed(UnsignedInt id, UnsignedInt reason)
{
	ErrorReason errorReason;
	std::ostringstream msg;
	msg << "Unsubscribe failed: " << id << " because: "
		<< errorReason.ReasonToString(reason).c_str()
		<< "\n\n";

	log << msg.str().c_str();
}

std::string smf2js::LogResponseHandler::FormattedMessage(const ResponseLogEntry& entry)
{
	std::ostringstream out;

	try
	{
		smf::LogEntry::Messages messages = entry.Message();
		smf::LogEntry::Messages::iterator itor = messages.begin();

		out << *itor;
	}
	catch (...)
	{
		log << "Failed to FormattedMessage\n\n";
	}

	return out.str();
}

std::string smf2js::LogResponseHandler::FormattedDate(const smf::DateTimeEntry& date)
{
	std::ostringstream out;

	try
	{
		unsigned short month = date.Month();
		unsigned short day = date.DayInMonth();

		out << date.Year()
			<< "-"
			<< (month < 10 ? "0" : "")
			<< month
			<< "-"
			<< (day < 10 ? "0" : "")
			<< day;
	}
	catch (...) {
		log << "Failed in FormattedDate function\n";
	}

	return  out.str();
}

std::string smf2js::LogResponseHandler::FormattedTime(const smf::DateTimeEntry& date)
{
	std::ostringstream out;

	try
	{
		unsigned short hour = date.HourOfDay();
		unsigned short min = date.MinuteOfHour();
		unsigned short sec = date.SecondOfMinute();

		out << (hour < 10 ? "0" : "")
			<< hour
			<< ":"
			<< (min < 10 ? "0" : "")
			<< min
			<< ":"
			<< (sec < 10 ? "0" : "")
			<< sec;
	}
	catch (...) {
		log << "Failed in FormattedTime function\n";
	}

	return out.str();
}

