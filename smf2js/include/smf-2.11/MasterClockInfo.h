#ifndef MASTERCLOCKINFO_H
#define MASTERCLOCKINFO_H

#include "StatsValue.h"

#include <string>
#include <map>
#include <vector>

namespace smf{   

        class MasterClockInfo
        {
        public:	// type definitions     

            typedef std::map<std::string, StatsValue> StatsInfo;
            typedef StatsInfo::const_iterator iterator;

            class MemoryAllocator
            {
            public:
                virtual StatsInfo* Create() = 0;    
                virtual StatsInfo* Copy(StatsInfo*) = 0;          
                virtual bool Destroy(StatsInfo*) = 0;
            };

        public: // construction

            MasterClockInfo();        
            MasterClockInfo(StatsInfo* info, MemoryAllocator* allocator);        
            MasterClockInfo(const MasterClockInfo&);      
            ~MasterClockInfo();
            
        public: // access methods

            size_t size();
            StatsInfo::const_iterator begin();
            StatsInfo::const_iterator end();
            const StatsValue &operator[] (const std::string &);
            MasterClockInfo& operator=(const MasterClockInfo&);
			
        private:        
            StatsInfo *statsInfo;
            MemoryAllocator *allocator;
        };  

}

#endif
