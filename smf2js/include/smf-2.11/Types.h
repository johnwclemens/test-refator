

#if defined TRUETYPE
	typedef unsigned int UnsignedInt;
	typedef int SignedInt;
#elif defined _WIN32
	typedef unsigned long UnsignedInt;
	typedef long SignedInt;
#else
	typedef unsigned int UnsignedInt;
	typedef int SignedInt;
#endif