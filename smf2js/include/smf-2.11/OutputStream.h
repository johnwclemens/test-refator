#ifndef SMFOUTPUTSTREAM_H
#define SMFOUTPUTSTREAM_H

namespace smf
{

	class OutputStream
	{
	public:
		virtual ~OutputStream() {}

		virtual OutputStream& operator<< (bool) = 0;
		virtual OutputStream& operator<< (const std::string&) = 0;
		virtual OutputStream& operator<< (const char*) = 0;
		virtual OutputStream& operator<< (long) = 0;
		virtual OutputStream& endl() = 0;
		virtual void flush() = 0;
	};

}
#endif

