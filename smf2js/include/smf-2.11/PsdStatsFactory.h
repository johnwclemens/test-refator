
#ifndef SMF_PSDSTATSFACTORY_H
#define SMF_PSDSTATSFACTORY_H

#include "StatsFactory.h"

class PartitionModel;
namespace smf{

	class PsdStatsMemory:
		public StatsMemory
	{
	public:
		virtual void DestroyPartitionModel(PartitionModel*) = 0;
		virtual PartitionModel* PartitionSchema() = 0;
		virtual void WriteToStream(PartitionModel* model, std::ostream& out) = 0;

		virtual ~PsdStatsMemory(){}
	};
}
#endif