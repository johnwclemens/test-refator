#ifndef SMFDESTROYER_H
#define SMFDESTROYER_H

namespace smf {

    struct Destroyer
    {
        template <typename T>
        void operator( )( T *pt )
        {
            delete pt ;
        }
    } ;

}

#endif
