#ifndef SCTRLTASKID_H
#define SCTRLTASKID_H

#include "SCtrlMessage.h"
#include <string>

namespace smf{
	class SCtrlTaskID
	{
	public:			
		SCtrlTaskID(const std::string& strID);

		SCtrlTaskID();
		
		virtual ~SCtrlTaskID(){}

		const std::string& StrID() const;

		bool operator == (const smf::SCtrlTaskID& taskID) const;

		bool operator > (const smf::SCtrlTaskID& taskID) const;

		bool operator < (const smf::SCtrlTaskID& taskID) const;

	private:
		std::string strID;

	};
}

#endif
