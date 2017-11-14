#include "Log.h"
#include "Locker.h"

#include <iostream>


smf2js::Log::Log() : logger(NULL), level(smf::Logger::Default), defaultlevel(level)
{
}

smf2js::Log::Log(smf::Logger* l, smf::Logger::Level level) : logger(l), level(level)
{
	this->defaultlevel = this->level;
}

void smf2js::Log::set(smf::Logger* l, smf::Logger::Level lvl)
{
	this->logger = l;
	this->level = lvl;
	this->defaultlevel = this->level;
}

smf2js::Log& smf2js::Log::operator << (long value)
{
	char strvalue[200] = { 0 };

	try
	{
		::_snprintf_s(strvalue, sizeof(strvalue), _TRUNCATE, " %d ", value);
		(*this) << strvalue;
	}
	catch (...)
	{
		this->ExceptionHandler("smf2js::Log::op... << (long)");
	}
	return *this;
}

smf2js::Log& smf2js::Log::operator << (const char* msg)
{
	try
	{
		if (this->logger)
		{
			this->logger->write(msg, level);
		}
		else
		{
			Locker l(&lock);
			std::cout << msg;
		}
	}
	catch (...)
	{
		this->ExceptionHandler("smf2js::Log::op << ... (const char*)");
	}
	return *this;
}

smf2js::Log& smf2js::Log::operator << (smf::LogMsg& msg)
{
	try
	{
		if (this->logger)
		{
			this->logger->write(msg.Value(), level);
		}
		else
		{
			Locker l(&lock);
			std::cout << msg.Value();
		}
	}
	catch (...)
	{
		this->ExceptionHandler("smf2js::Log::op... <<(LogMsg)");
	}
	return *this;
}

smf2js::Log&  smf2js::Log::begin(smf::Logger::Level lvl)
{
	try
	{
		this->level = lvl;
		if (logger)
		{
			this->logger->startline(lvl);
		}
		else
		{
		}
	}
	catch (...)
	{
		this->ExceptionHandler("smf2js::Log::begin()");
	}
	return *this;
}

smf2js::Log&  smf2js::Log::begin()
{
	return begin(this->defaultlevel);
}

void smf2js::Log::end()
{
	try
	{
		if (this->logger)
		{
			this->logger->endline(level);
		}
		else
		{
		}
	}
	catch (...)
	{
		this->ExceptionHandler("smf2js::Log::end()");
	}
}

void smf2js::Log::ExceptionHandler(const char* where)
{
	try
	{
		std::cerr << "Exception in Log ... " << where;
	}
	catch (...)
	{
		//its all gone pear shaped ...
	}
}
