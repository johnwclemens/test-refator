#include "JsonHandler.h"
#include <string>
#include <sstream>

smf2js::JsonHandler::JsonHandler() { _document.SetObject(); }


smf2js::JsonHandler::~JsonHandler() { }

void smf2js::JsonHandler::AddKeyValue(std::string key, std::string value)
{
	Value k = Value(key.c_str(), _document.GetAllocator());
	Value v = Value(value.c_str(), _document.GetAllocator());
	_document.AddMember(
		k,
		v,
		_document.GetAllocator());
}

void smf2js::JsonHandler::AddKeyValue(std::string key, int value) {	AddKeyValue(key, std::to_string(value)); }
void smf2js::JsonHandler::AddKeyValue(std::string key, unsigned int value) { AddKeyValue(key, std::to_string(value)); }
void smf2js::JsonHandler::AddKeyValue(std::string key, __int64 value) { AddKeyValue(key, std::to_string(value)); }
void smf2js::JsonHandler::AddKeyValue(std::string key, double value) { AddKeyValue(key, std::to_string(value)); }
void smf2js::JsonHandler::AddKeyValue(std::string key, char value) { AddKeyValue(key, std::to_string(value)); }

void smf2js::JsonHandler::RemoveKey(std::string key)
{
	_document.RemoveMember(key.c_str());
}

std::string smf2js::JsonHandler::GetValue(std::string key)
{
	std::string ret = _document[key.c_str()].GetString();
	return ret;
}

void smf2js::JsonHandler::GetArray(std::string key, std::vector<std::string>& vec)
{
	const Value& a = _document[key.c_str()];
	if (a.IsArray())
	{
		for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
			vec.push_back(a[i].GetString());
	}
}

std::string smf2js::JsonHandler::Stringify()
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	_document.Accept(writer);
	std::string tmp = buffer.GetString();
	return tmp;
}

void smf2js::JsonHandler::Parse(std::string msg)
{
	_document.Parse(msg.c_str());
}
