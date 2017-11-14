#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;

namespace smf2js
{
	class JsonHandler
	{
	public:
		JsonHandler();
		~JsonHandler();

		void AddKeyValue(std::string key, std::string value);
		void AddKeyValue(std::string key, int value);
		void AddKeyValue(std::string key, unsigned int value);
		void AddKeyValue(std::string key, __int64 value);
		void AddKeyValue(std::string key, double value);
		void AddKeyValue(std::string key, char value);
		void RemoveKey(std::string key);
		std::string GetValue(std::string key);
		void GetArray(std::string key, std::vector<std::string>& vec);

		std::string Stringify();
		void Parse(std::string msg);
	private:
		//std::map<std::string, std::string> _document;
		Document _document;
	};
}

