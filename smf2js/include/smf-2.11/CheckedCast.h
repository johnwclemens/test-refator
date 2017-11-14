
#ifndef CHECKEDCAST_H
#define CHECKEDCAST_H

#include "CriticalError.h"

template <typename ToType>
class CheckedCast{

public:

	
	
	template<typename FromType>
	static ToType Cast  (FromType from, const char* info = "<no info>")
	{
		ToType to = (ToType) from;
		FromType test = to;
		//
		if(test != from){
			smf::CriticalError e("Downcast caused variable wraparound casting from ");
			e	<< typeid(FromType).name() << " to " << typeid(ToType).name()
				<< " info: " << info;
			throw e;
		}
		return to;
	}
};
#endif