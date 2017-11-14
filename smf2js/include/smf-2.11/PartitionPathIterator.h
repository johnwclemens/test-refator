
#ifndef PARTITIONITERATOR_H
#define PARTITIONITERATOR_H

#include <string>

namespace smf {
	class PartitionPathIterator {
        public:
		   
		    virtual const char* FullPath( ) const = 0;

			virtual const char*     GroupName( )    const = 0;
			virtual const char*     FieldName( )    const = 0;
			virtual unsigned int   GroupIndex( )   const = 0;
			virtual unsigned int   FieldIndex( )   const = 0;

            virtual bool HasGroupIndex( ) const = 0;
            virtual bool HasFieldIndex( ) const = 0;

		    virtual bool Done( )     = 0;
		    
		    virtual bool operator==( const PartitionPathIterator& ) const = 0;
		    virtual bool operator!=( const PartitionPathIterator& ) const = 0;

		    virtual ~PartitionPathIterator( ) { }
	};
}

#endif
