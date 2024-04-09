#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)  // exports anything with HAZELAPI using dllexport
	#else
		#define HAZEL_API __declspec(dllimport)  // imports anything with HAZELAPI using dllimport
	#endif
#else
	#error Hazel only supports Windows!
#endif

#define BIT(x) (1 << x)