////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 by
// Reuters Hong Kong Ltd. Technical Development, Hong Kong
// All rights reserved.
//
// No portion of this software in any form may be used or reproduced in
// any manner without written consent from Reuters Asia PTE Ltd.
//
// You must not remove this notice, or any other, from this software.
//

#include "ErrorReason.h"

const char* defaults[ ] =
{
    "Success" ,
    "Unclassified Failure" ,
    "Invalid Field Name" ,
    "Unknown Field Name or Invalid array index" ,
    "Field Not Modifiable" ,
    "Array Index Out Of Bounds" ,
    "Type Mismatch" ,
    "String Too Long" ,
    "Transaction In Progress" ,
    "Transaction Across Partitions" ,
    "Illegal Path Name" ,
    "Path Iterator Error" ,
    "Null Handle" ,
    "Invalid Handle" ,
    "Unknown Handle" ,
    "Handles Not Supported For This Partition" ,
    "Coding Error" ,
    "Field Value Too Big" ,
    "Invalid Update" ,
    "Missed Message" ,
    "Unknown Group" ,
    "Server Overloaded" ,
    NULL
};

smf2js::ErrorReason::ErrorReason( void )
{
    Set( defaults );
}

smf2js::ErrorReason::ErrorReason( const char * const* reasons )
{
    Set( reasons );
}

void smf2js::ErrorReason::Set( const char* const* reasons )
{
    for ( unsigned long i = 0 ; reasons[ i ] ; i++ )
    {
        Add( i , std::string( reasons[ i ] ) );
    }

}
std::string smf2js::ErrorReason::ReasonToString( unsigned long indx ) const
{
    Reasons::const_iterator itor = reasons.find( indx );

    if ( itor != reasons.end( ) )
    {
        return itor->second;
    }
    return std::string( "Unknown error message" );
}

void smf2js::ErrorReason::Add( unsigned long reason , std::string& detail )
{
    reasons[ reason ] = detail;
}
