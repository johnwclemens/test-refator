
#ifndef SMF_VERSION_H
#define SMF_VERSION_H

#include <string>
#include "VersionInfo.h"

#define STRING2(x) #x
#define STRING(x) STRING2(x)

//this corresponds to package version 2.1.1
#define PACKAGEVERSION "2.11" 
#define PACKAGEVERSIONSERVICEINFO "smfversion"
#define PACKAGEVERSIONSERVICEID *((unsigned int*)"pkg\0")

#define SMFVERSIONSTRING ".smf190" 

#define MSCVERSIONSTRING ".msc" STRING(_MSC_VER)
#define CPPVERSIONSTRING ".c++libs" STRING(_CPPLIB_VER)

#ifdef _DEBUG
 #define DBGVERSIONSTRING ".dbg"
#else
 #define DBGVERSIONSTRING	
#endif

#ifdef _M_X64
 #define PLATFORMVERSIONSTRING	".64bit"
#else
 #define PLATFORMVERSIONSTRING	".32bit"
#endif

#define FULLVERSION MSCVERSIONSTRING  CPPVERSIONSTRING  SMFVERSIONSTRING PLATFORMVERSIONSTRING DBGVERSIONSTRING

#define VERSIONSEARCHSTRING "###lib-version-info###:"

#ifdef WIN32
 #define SMFCLIENTLIB "SmfClient" FULLVERSION ".dll"
#else
 #define SMFCLIENTLIB "SmfClient.so"
#endif


#ifdef WIN32
 #define RSSENDERLIB "RsSender" FULLVERSION ".dll"
#else
 #define RSSENDERLIB "RsSender.so"
#endif


#ifdef WIN32
 #define RSRECEIVERLIB "rsreceiver" FULLVERSION ".dll"
#else
 #define RSRECEIVERLIB "rsreceiver.so"
#endif

#ifdef WIN32
 #define LOGCLIENTSERVICELIB "LogClientService" FULLVERSION ".dll"
#else
 #define LOGCLIENTSERVICELIB "LogClientService.so"
#endif

#ifdef WIN32
 #define PSDBULKCLIENTSERVICELIB "PsdBulkClientService" FULLVERSION ".dll"
#else
 #define PSDBULKCLIENTSERVICELIB "PsdBulkClientService.so"
#endif

#ifdef WIN32
 #define PSDCLIENTSERVICELIB "PsdClientService" FULLVERSION ".dll"
#else
 #define PSDCLIENTSERVICELIB "PsdClientService.so"
#endif

#ifdef WIN32
 #define PSDSTATSLIB "psdstats" FULLVERSION ".dll";
#else
 #define PSDSTATSLIB "psdstats.so"
#endif


#ifdef WIN32
 #define PSDDIRECTLIB "PsdDirect" FULLVERSION ".dll"
#else
 #define PSDDIRECTLIB "PsdDirect.so"
#endif


#endif
