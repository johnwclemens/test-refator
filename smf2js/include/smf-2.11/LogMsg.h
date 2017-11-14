
#ifndef LOGMSG_H
#define LOGMSG_H

#include <string>
#pragma warning(default : 4265)

//use this to convert __LINE__ to a string
#ifndef LINEASSTR
	#define LINEASSTR2(x) #x
	#define LINEASSTR(x) LINEASSTR2(x)
#endif

// Want to get rid of this in the production version
//
// Replace the Error class with something that can report where it was thrown 
// from.
// Throw specific errors but derive them from a generic Error class - so if we 
// fail to handle a specific error we can catch the generic error and print out
// where it came from.
// Handle all specific errors in a specific fashion.

namespace smf{
	class LogMsg{

		enum size{
			MaxMsgSize = 2000
		};

		size_t indx;
		char message[MaxMsgSize + 4];
	public:
		virtual ~LogMsg();



		LogMsg(const char* basemsg);

		LogMsg& operator << (const char* msg);
		LogMsg& operator << (long value);
		LogMsg& operator << (unsigned long value);
		LogMsg& operator << (unsigned int value);
		LogMsg& operator << ( int value);
		LogMsg& operator << (unsigned short value);
		LogMsg& operator << (short value);
		LogMsg& operator << (const void* value);
		LogMsg& operator <<(__int64 value);
		LogMsg& operator <<(unsigned __int64 value);

		const char* Value();
		const char* RawValue();

		LogMsg(const LogMsg& that);
		LogMsg& operator =(const LogMsg& that);

	private:
		LogMsg();

		void StringCopy(char* to, const char* from, size_t sizeofToBuffer);
        void IntegerToString(__int64 value, char* buffer, size_t sizeofToBuffer, int radix);

	};
}

#endif