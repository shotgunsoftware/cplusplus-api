#ifndef __CONFIG_H__
#define __CONFIG_H__

//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)
#pragma warning (disable : 4251)
#pragma warning (disable : 4275)

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#ifdef SHOTGUN_DLL_BUILD
		#define SG_API __declspec(dllexport)
		#define SG_EXTERN
	#elif defined(SHOTGUN_DLL)
		#define SG_API __declspec(dllimport)
		#define SG_EXTERN extern
	#else
		#define SG_API
		#define SG_EXTERN
	#endif
#endif //_WIN32

#endif //__CONFIG_H__