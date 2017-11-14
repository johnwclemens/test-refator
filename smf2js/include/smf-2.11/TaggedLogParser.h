
#ifndef TAGGEDLOGPARSER_H
#define TAGGEDLOGPARSER_H

#include "FileParser.h"



namespace smf{
	namespace Tagged{

		const char* LibName();
		FileParser* Open(const char* basefilename, const char* extension);
		void CloseParser(FileParser* p);
		FileParser::WhereFilter* CreateFilter(
			std::vector <FileParser::NameValuePair>& testitems, 
			bool And );
		void DestroyFilter(FileParser::WhereFilter* filter);
		const char* LogParserVersion();
	}
}


#endif