#ifndef SCTRLPROCESSSTATUSINFOLIST_H
#define SCTRLPROCESSSTATUSINFOLIST_H

#include "SCtrlProcessStatusInfo.h"

namespace smf{
	class SCtrlProcessStatusInfoList 
	{
	public:
		SCtrlProcessStatusInfoList(){}
		virtual ~SCtrlProcessStatusInfoList(){}
		
		virtual const smf::SCtrlProcessStatusInfo& at(size_t index) const = 0;

		virtual size_t size() const = 0;
	};
}
#endif