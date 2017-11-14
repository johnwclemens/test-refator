
#ifndef PSDPARTITIONBASEDSTATSFACTORYENTRYPOINTS_H
#define PSDPARTITIONBASEDSTATSFACTORYENTRYPOINTS_H



namespace smf{
	class Logger;
	class StatsFactory;

	namespace PartitionBasedStats{

		const char* LibName();

		smf::StatsFactory* CreateStatsFactory( Logger* logger );

		void DestroyStatsFactory( StatsFactory* factory );
	}
}

#endif