
#ifndef DYNAMICLIBLOADER_H
#define DYNAMICLIBLOADER_H

#include <Windows.h>
#include "Error.h"

namespace smf{
	class DynamicLibLoader{

	public:
		class FailedToLoad:
			public smf::Error
		{
		public:
			FailedToLoad(const char* lib);
		};
		class FailedToFindFunction:
			public smf::Error
		{
		public:
			FailedToFindFunction(const char* lib);
		};

		DynamicLibLoader();

		DynamicLibLoader(const char* lib);
		explicit DynamicLibLoader(const wchar_t* lib);

		operator bool();

		void* load(const char* func);
		
		//HMODULE Library();

		void* load(const char* lib, const char* func);
	private:
		void* load(HMODULE library, const char* func);

		HMODULE lastlib;
	};
}
#endif