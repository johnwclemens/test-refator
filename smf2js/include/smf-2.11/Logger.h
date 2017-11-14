
#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>

namespace smf{
	class Logger{

	public:
		enum Level
		{
			Default = 1,
			System = 0xff, //!< slightly misnamed - really means all
			LogServicesLog = 2,
		};

		virtual bool set(std::ostream& , Level ) = 0;
		virtual void write(const char*, Level ) = 0;

		virtual void startline(Level ) = 0;
		virtual void endline(Level ) = 0;

		virtual ~Logger(){}

	protected:
		Logger() {}
	private:
		Logger(const Logger &);
		Logger &operator=(Logger &);
	};
}
#endif