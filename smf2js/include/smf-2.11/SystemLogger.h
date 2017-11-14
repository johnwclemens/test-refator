
#ifndef SYSTEMLOGGER_H
#define SYSTEMLOGGER_H


namespace smf{
	class SystemLogger
	{

	public:

		virtual void write(const char* msg , bool notifyClients) = 0;
		virtual ~SystemLogger() {}
	};
}
#endif