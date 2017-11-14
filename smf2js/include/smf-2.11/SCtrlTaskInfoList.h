#ifndef SCTRLTASKINFOLIST_H
#define SCTRLTASKINFOLIST_H

#include "SCtrlTaskInfo.h"


namespace smf{
	class SCtrlTaskInfoList
	{
	public:
		SCtrlTaskInfoList(){}
		virtual ~SCtrlTaskInfoList(){}
		virtual const smf::SCtrlTaskInfo& at(size_t index) const = 0;

		virtual size_t size() const = 0;
	};
}

#endif