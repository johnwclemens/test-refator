
#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "DateTimeEntry.h"
#include "Error.h"
#include <string>
#include <vector>

class FileParser
{
public:
	class NoRecordSeperator:
		public smf::Error
	{
	public:
		NoRecordSeperator(std::string& line):
		  smf::Error("Missing a record seperator in the log line ")
		  {
			  (*this) << line.c_str();
		  }
	};
	class InvalidLine:
		public smf::Error
	{
	public:
		InvalidLine(const char* why):
		  smf::Error("Invalid log line: ")
		  {
			  (*this) << why;
		  }
	};

	class InvalidParser:
		public smf::Error
	{
	public:
		InvalidParser():
		  smf::Error("Invalid file parser")
		  {
			  
		  }
	};

	class NameValuePair{
	public:
		
		NameValuePair(const char* n, const char* v)
		{
			if(n)
				name = n;
			if(v)
				value = v;
		}


		NameValuePair()
		{
		}

		~NameValuePair(){
			
		}
		const char* Name()const{
			return name.c_str();
		}
		const char* Value()const{
			return value.c_str();
		}
	private:
		
		std::string name , value;
		
	};

	class WhereFilter 
	{
	public:
		//reset everything
		virtual  void start() = 0;
		//move to next item to be tested or return false if no more items
		virtual bool eachItem() = 0;
		//return the current items name
		virtual const char* item() = 0;
		//cuurently always return true
		//test this pair against the current item
		virtual bool test(FileParser::NameValuePair* ) = 0;
		//if *all* the filter conditions where met return true
		//i.e. if there are 2 items and the filter is an AND filter
		//both items must be matched to return true here
		virtual bool matched() = 0;

		virtual ~WhereFilter() {}
	};
	

	virtual FileParser::NameValuePair* at(const char* name) = 0;
	virtual FileParser::NameValuePair* at(unsigned int index) = 0;
	
	virtual void Deallocate(FileParser::NameValuePair* ) = 0;
	virtual bool MoveTo(const smf::DateTimeEntry& date, const char* datename = "date") = 0;
	virtual bool MoveToTime(unsigned int secondsSinceMidnight, const char* timename = "time") = 0;
	virtual bool EachLine()= 0;
	virtual bool EachLine(WhereFilter* filter) = 0;
	virtual const char* CurrentFile() = 0;
	virtual unsigned int CurrentLine() = 0;

	typedef std::vector <std::string > Sections;

	virtual Sections* LineInfo() = 0;

	virtual size_t size() = 0;

	virtual ~FileParser(){}
};

#endif