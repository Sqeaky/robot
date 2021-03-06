////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                       (C) 2010-2016 Robot Developers                       //
//                       See LICENSE for licensing info                       //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#pragma once



//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// Defines the current version of Robot as an integer and string value.

#define ROBOT_VERSION		0x020000
#define ROBOT_VERSION_STR	"2.0.0"



//----------------------------------------------------------------------------//
// Platforms                                                                  //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// Defines operating system and architecture identification macros. Operating
/// system macros are defined using the OS_* identifier while architectures are
/// defined using the ARCH_* identifier.

#if defined (__linux__)

	#define ROBOT_OS_LINUX
	#if defined (__x86_64__)
		#define ROBOT_ARCH_64
	#else
		#define ROBOT_ARCH_32
	#endif

#elif defined (__APPLE__) && defined (__MACH__)

	#define ROBOT_OS_MAC
	#if defined (__x86_64__)
		#define ROBOT_ARCH_64
	#else
		#define ROBOT_ARCH_32
	#endif

#elif defined (_WIN32)

	#define ROBOT_OS_WIN
	#if defined (_WIN64)
		#define ROBOT_ARCH_64
	#else
		#define ROBOT_ARCH_32
	#endif

#else

    #error Your operating system is not supported.

#endif


//----------------------------------------------------------------------------//
// Compilers                                                                  //
//----------------------------------------------------------------------------//

#if defined(_MSC_VER)

    #define ROBOT_VS_COMPILER_GROUP

    #if (_MSC_VER == 1900)
        #define ROBOT_VS_COMPILER_2015_14
    #elif (_MSC_VER == 1800)
        #define ROBOT_VS_COMPILER_2013_12
    #elif (_MSC_VER == 1700)
        #define ROBOT_VS_COMPILER_2011_11
    #elif (_MSC_VER == 1600)
        #define ROBOT_VS_COMPILER_2010_10
    #else
        #error Your version of microsoft visual C++ is not supported.
    #endif

#else

    #define ROBOT_NIX_COMPILER_GROUP

    #if defined(__clang__)
        #define ROBOT_CLANG_COMPILER
    #elif defined(__MINGW32__)
        #define ROBOT_MINGW_COMPILER
    #elif defined(__GNUC__) || defined(__GNUG__)
        // Must be last because Clange will report as an old Version of GCC and
        // who knows what MinGW will do that seems crazy but makes only on deep
        // inspection of GCC interactions with windows.
        #define ROBOT_GCC_COMPILER
    #endif

#endif

//----------------------------------------------------------------------------//
// Export                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// When building Robot as a DLL, BUILDING_ROBOT_SHARED needs to be defined.
/// When building a program which uses the Robot DLL, USING_ROBOT_SHARED needs
/// to be defined. When building Robot as either a static library or building a
/// program which uses Robot as a static library, neither BUILDING_ROBOT_SHARED
/// nor USING_ROBOT_SHARED need to be defined.

#if defined (BUILDING_ROBOT_SHARED) && defined (USING_ROBOT_SHARED)
#error Both BUILDING_ROBOT_SHARED and USING_ROBOT_SHARED are defined - please \
	   check your build configuration to ensure that only one of these is set
#endif

#ifdef ROBOT_OS_WIN

	#if defined (BUILDING_ROBOT_SHARED)
		#define ROBOT_EXPORT __declspec (dllexport)
	#elif defined (USING_ROBOT_SHARED)
		#define ROBOT_EXPORT __declspec (dllimport)
	#else
		#define ROBOT_EXPORT
	#endif

#elif (__GNUC__ >= 4)
	#define ROBOT_EXPORT __attribute__ ((visibility ("default")))
#else
	#define ROBOT_EXPORT
#endif



//----------------------------------------------------------------------------//
// Namespace                                                                  //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////
/// This library requires namespace encapsulation to prevent naming conflicts
/// with system libraries. To use a different name, modify the ROBOT_NS macro.
/// The ROBOT_NS_* family of macros can be used to define and use namespaces
/// without depending on explicit names.

#ifndef ROBOT_NS
#define ROBOT_NS Robot
#endif

#ifdef ROBOT_NS

	#define ROBOT_NS_BEGIN			namespace ROBOT_NS {
	#define ROBOT_NS_END			}

	#define ROBOT_NS_PRE( name )	ROBOT_NS::name
	#define ROBOT_NS_FWD( name )	\
			ROBOT_NS_BEGIN			\
				class name;			\
			ROBOT_NS_END

	#define ROBOT_NS_USE_ALL		using namespace ROBOT_NS;
	#define ROBOT_NS_USE( name )	using ROBOT_NS::name;

#else

	#error This library must be encapsulated in a namespace

#endif



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//


#include <cstdint>

ROBOT_NS_BEGIN

typedef std::int8_t   			int8;		// Signed  8-Bit integer
typedef std::int16_t     		int16;		// Signed 16-Bit integer
typedef	std::int32_t     		int32;		// Signed 32-Bit integer
typedef std::int64_t 	        int64;		// Signed 64-Bit integer

typedef std::uint8_t     		uint8;		// Unsigned  8-Bit integer
typedef std::uint16_t     		uint16;		// Unsigned 16-Bit integer
typedef std::uint32_t     		uint32;		// Unsigned 32-Bit integer
typedef std::uint64_t        	uint64;		// Unsigned 64-Bit integer

typedef float				real32;		// 32-Bit float value
typedef double				real64;		// 64-Bit float value

#ifdef ROBOT_ARCH_64

	typedef  int64			 intptr;	//   Signed pointer integer
	typedef uint64			uintptr;	// Unsigned pointer integer

#else

	typedef  int32			 intptr;	//   Signed pointer integer
	typedef uint32			uintptr;	// Unsigned pointer integer

#endif

ROBOT_NS_END
