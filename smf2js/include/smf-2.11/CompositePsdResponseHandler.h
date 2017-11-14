
#ifndef COMPOSITEPSDRESPONSEHANDLER_H
#define COMPOSITEPSDRESPONSEHANDLER_H

#define TRUETYPE

#include "Log.h"
#include "Logger.h"
#include "ParameterServiceResponseHandler.h"
#include "SectionLock.h"
#include <map>

class CompositePsdResponseHandler:
	public smf::ParameterServiceResponseHandler
{
public:
	CompositePsdResponseHandler(smf::Logger* logger)
		:log(logger), id(1), isStop(false)
	{
	}
	
	void ReportValues(FieldValues&, unsigned int identifier);
	void ReportValues(HandleValues&, unsigned int identifier );
	void ReportHandles(FieldHandles&, unsigned int identifier);
	void ReportSuccessfulUpdate(unsigned int identifier);
    void ReportMetadata(const std::string &name, const std::string &type, Metadata& metadata, unsigned int identifier);
    void ReportMetadataError(const std::string &name, const std::string &type, unsigned short reason, const std::string &description, unsigned int identifier);
	void ReportSchema(const char* line);
	void ReportSchema(Schema&, unsigned int);
	void ReportPartitions(Partitions&, unsigned int);
	void ReportFailedUpdates(FieldValues&, unsigned int identifier);
	void ReportFailedUpdates(HandleValues&, unsigned int identifier);
	void ReportFailure(unsigned short reason);

	unsigned int Add(smf::ParameterServiceResponseHandler*);
	void Remove(unsigned int id);
	smf::ParameterServiceResponseHandler* HandlerFromId(unsigned int id);
	
	void ExceptionHandler(const char* where);

	void SetStop();
	void ClearStop();

private:
	CompositePsdResponseHandler();
	CompositePsdResponseHandler(const CompositePsdResponseHandler&);
	CompositePsdResponseHandler& operator=(const CompositePsdResponseHandler&);
	
	std::map<unsigned int, smf::ParameterServiceResponseHandler*> knownHandlers;
	smf::Log log;
	smf::SectionLock lock;
	unsigned int id;
	bool isStop;
};
#endif