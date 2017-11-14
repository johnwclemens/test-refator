#ifndef PSDRECORD_H
#define PSDRECORD_H

#pragma warning (disable : 4786)
#include <vector>
#include "PsdValue.h"

namespace smf{
	class PsdRecord
	{
	public:
        typedef unsigned int RowNumberType;
        typedef std::vector<PsdValue> Values;

		PsdRecord(RowNumberType index, const Values &values);
		explicit PsdRecord(RowNumberType index);
		PsdRecord();

        void AddValue(const PsdValue& value);

        RowNumberType RowNumber() const;

		//Try to reduce reallocations by allowing the user class to 
		// tell us how many entries there will be and then use that 
		// entry through [] operator
		void resize(size_t);
		size_t size() const;
		const PsdValue& operator[](size_t i) const;
		PsdValue& operator[](size_t i);

        bool operator<(const PsdRecord&)const;  // for sorting
	private:
        enum {
            NotInitialisedIndex = -1
        };

        RowNumberType index;
        Values values;
	};
}

#endif
