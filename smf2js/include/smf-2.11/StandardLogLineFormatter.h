
#ifndef STANDARDLOGLINEFORMATTER_H
#define STANDARDLOGLINEFORMATTER_H

#include "LogLineFormatter.h"



namespace smf{
	class StampedLogEntry;
	class UnstampedLogEntry;
	
	class StandardLogLineFormatter:
		public smf::LogLineFormatter
	{
	public:
		//use an smf wrapper for ostream to prevent problems with different
		//std lib versions


		virtual void BeginField(const StampedLogEntry&) = 0;
		virtual void EndField(const StampedLogEntry&) = 0;
		virtual void BeginLine(const StampedLogEntry&) = 0;
		virtual void EndLine(  const StampedLogEntry&) = 0;
		
		virtual void BeginFile() = 0;
		virtual void EndFile() = 0;
		
		virtual void BeginComment() = 0;
		virtual void Comment(const char*) = 0;
		virtual void EndComment() = 0;
		virtual void BeginHeader() = 0;
		virtual void Header(const char* name, const char* configname) = 0;
		virtual void EndHeader() = 0;

		virtual ~StandardLogLineFormatter() = 0;


	};
}

#endif