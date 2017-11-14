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
// File :        PSDRequestPtr.h
// Description : This file contains 
// Creator :     Nestal Wan
//
/////////////////////////////////////////////////////////////////////////

#ifndef PSDREQUESTPTR_H
#define PSDREQUESTPTR_H

namespace smf
{
    class Logger ;
    class ServiceChannel ;
    class ParameterServiceResponseHandler ;
    class ParameterServiceRequestHandler ;
}

class PSDRequestPtr
{
public:
    PSDRequestPtr( smf::ParameterServiceResponseHandler *rsp , smf::ServiceChannel *channel , smf::Logger *logger ) ;
    ~PSDRequestPtr( ) ;

    smf::ParameterServiceRequestHandler* Get( ) const ;

    smf::ParameterServiceRequestHandler& operator*() const ;
    smf::ParameterServiceRequestHandler* operator->() const ;

private :
    smf::ParameterServiceRequestHandler*    m_psd ;
    smf::ServiceChannel*                    m_channel ;
} ;

#endif
