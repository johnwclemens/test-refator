#ifndef VS2003_MAPPING_H
#define VS2003_MAPPING_H

#include <stdlib.h>

typedef int errno_t;

#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif

#define _SH_DENYWR      0x20    /* deny write mode */

#ifndef _UINTPTR_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64    uintptr_t;
#else
typedef _W64 unsigned int   uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif

typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t); 

errno_t strncpy_s(
   char *strDest,
   size_t sizeInBytes,
   const char *strSource,
   size_t count
);

errno_t wcsncpy_s(
   wchar_t *strDest,
   size_t sizeInWords,
   const wchar_t *strSource,
   size_t count
);

_invalid_parameter_handler _set_invalid_parameter_handler(
      _invalid_parameter_handler pNew
);

errno_t wcstombs_s(
   size_t *pReturnValue,
   char *mbstr,
   size_t sizeInBytes,
   const wchar_t *wcstr,
   size_t count 
);

errno_t _itoa_s(
   int value,
   char *buffer,
   size_t sizeInCharacters,
   int radix 
);

errno_t memcpy_s(
   void *dest,
   size_t numberOfElements,
   const void *src,
   size_t count
   );

#endif
