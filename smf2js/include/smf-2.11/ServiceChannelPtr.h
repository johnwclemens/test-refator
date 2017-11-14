/////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2004 Reuters Limited
// This document contains information proprietary to Reuters Limited, and
// may not be reproduced, disclosed or used in whole or in part without
// the express written permission of Reuters Limited.
//
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//
// File :        ServiceChannelPtr.h
// Description : definition of the ServiceChannelPtr class
// Creator :     Nestal Wan
//
//////////////////////////////////////////////////////////////////////////

#ifndef SERVICECHANNELPTR_H
#define SERVICECHANNELPTR_H

namespace smf
{
    class Logger ;
    class ServiceChannel ;
}

// an auto_ptr like class to wrap up the ServiceChannel pointer
class ServiceChannelPtr
{
public :
    ServiceChannelPtr( const char *hostname , unsigned short port , smf::Logger *logger ) ;
    ServiceChannelPtr( const char *hostname , const char *service , smf::Logger *logger ) ;
    ~ServiceChannelPtr( ) ;

    smf::ServiceChannel* Get( ) const ;

    smf::ServiceChannel& operator*() const ;
    smf::ServiceChannel* operator->() const ;

private :
    smf::ServiceChannel *m_channel ;
} ;

/*
template <typename T, typename DetroyFunc=Btg::Destroy>
class AutoPtr
{
public :
    AutoPtr( T *t, DetroyFunc func = DetroyFunc( ) )
    : m_t( t ), m_func( func )
    {
    }
    
    ~AutoPtr( )
    {
        m_func( m_t ) ;
    }
} ;
*/
#endif
