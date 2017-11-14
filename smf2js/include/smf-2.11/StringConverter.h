

#ifndef CPSMDAIG_STRINGCONVERTER_H
#define CPSMDAIG_STRINGCONVERTER_H

#include <string>
#include <vector>

namespace smf{

	//store everything as UTF-8
	// if we want the MB version then simply return the UTF 8 string
	// if we want the wstr version then convert to unicode
	class StringConverter{
	public:
		StringConverter(const std::wstring& wstr);
		StringConverter(const wchar_t* wstr);
		//this is expected to be a UTF-8 string - it will be copied direct to the buffer
		StringConverter(const char* utf8str);
		StringConverter(const std::string& utf8str);

		const std::wstring WideStr();
		const char* Str();

		//should go the other way too
		//const wchar_t* Convert(const char * );

	private:
		std::vector<char> buffer;

		void ConstructInternalRepresentation(const std::wstring&  wstr);

	};

}
#endif