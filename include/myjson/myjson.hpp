/**
 * @file myjson.hpp
 * @brief JSON For Modern C/C++.
 * @details All public API, types, macros, and configuration.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myjson
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Developed by Sackey Ezekiel Etrue and every direct or indirect contributors.
 * See LICENSE for copyright and licensing details (standard MIT License).
 *
 * MYJSON: What is `myjson` ?
 *
 *      myjson is a modern C/C++ library for JSON (JavaScript Object Notation).
 *
 *      MISSION:
 *
 *          To provide C++ developers with a human-centric configuration interface that prioritizes clarity
 *          and safety without compromising on technical rigor. Our mission is to transform TOML from a
 *          raw data format into a type-safe, intuitive C++ object model, enabling developers to build highly
 *          configurable applications where the distance between a user’s intent and the program’s state is zero
 *
 *          To provide a robust, industry-standard foundation for data exchange in modern C++ applications.
 *          Our mission is to eliminate the friction between complex C++ memory management and flexible JSON Structures,
 *          ensuring that developers can prioritize application logic over serialization boilerplate.
 *          We strive to deliver a library that is as invisible as it is indispensable,
 *          maintaining a perfect balance between human-centric API design and machine-level execution speed.
 *
 *          - Easy to hack and improve.
 *          - Minimize setup and maintenance.
 *          - Efficient runtime and memory consumption.
 *
 *
 *          Designed primarily for developers and not the typical end-user!
 *
 *      DESIGN: Design Goals
 *
 *          STANDARD COMPLIANCE :
 *              - JSON (https://www.json.org/json-en.html)
 *              - RFC 8259 (https://www.ietf.org/rfc/rfc8259.txt)
 *
 *          PERFORMANCE FOCUSED :
 *              - Minimize memory allocations and copies.
 *              - Optimize for speed and low latency.
 *
 *          WELL DOCUMENTED :
 *              - Comprehensive API documentation.
 *              - Code comments and examples.
 *
 *          HEAVILY TESTED :
 *              - Unit tests for all features.
 *              - Integration tests for all components.
 *              - Performance tests for critical paths.
 *
 *          FEATURE RICH :
 *              - Support for JSON Schema (https://json-schema.org/)
 *              - Support for JSON Pointer (https://tools.ietf.org/html/rfc6901)
 *              - Support for JSON Patch (https://tools.ietf.org/html/rfc6902)
 *
 *          PORTABLE :
 *              - Cross-platform compatibility.
 *              - Support for various compilers and platforms.
 *
 *      FEATURES:
 *          Brief overview of the features provided:
 *
 *          GENERAL :
 *
 *              * Line break formats
 *                  - Support the Mac style `\r`.
 *                  - Support the Unix style `\n`.
 *                  - Support the Windows style `\r\n`.
 *
 *          STANDARD : JSON LANGUAGE SPECIFICATION
 *                 (https://www.json.org/json-en.html)
 *              (https://www.ietf.org/rfc/rfc8259.txt)
 *
 * ENCODING:
 *
 *      * Support UTF-8, UTF-16 and UTF-32 encodings, including native, little and big endians.
 *      * Character types are :
 *
 *                       ****************************************
 *                       * Encodings *  Charater Type           *
 *                       ****************************************
 *                       * UTF-8     *  char8_t (since C++20)   *
 *                       * UTF-16    *  char16_t                *
 *                       * UTF-32    *  char32_t                *
 *                       ****************************************
 *
 *      * Support automatic detection of encodings.
 *      * Support encoding validation internally.
 *
 *
 * NOTES:
 *
 * USAGE:
 *
 * FAQS:
 *
 * HELP:
 *    - See links below.
 *    - Read top of myjson.cpp for more details and comments.
 *
 *  Has only had a few tests run, may have issues.
 *
 *  If having issues compiling/linking/running raise an issue (https://github.com/djoezeke/myjson/issues).
 *  Please post in https://github.com/djoezeke/myjson/discussions if you cannot find a solution.
 *
 * RESOURCES:
 * - Homepage ................... https://github.com/djoezeke/myjson
 * - Releases & changelog ....... https://github.com/djoezeke/myjson/releases
 * - Issues & support ........... https://github.com/djoezeke/myjson/issues
 *
 * LICENSE: MIT License
 *      See end of file for license information.
 *
 */

#ifndef DJOEZEKE_MYJSON_HPP

/**
 * SECTIONS: Index of this file
 *
 *  [SECTION] Include Mess
 *  [SECTION] Configurations
 *  [SECTION] Compiler & Platform
 *  [SECTION] API Imports/Exports
 *
 *  Forward: Forward Declarations
 *
 *      [SECTION] Details Forward
 *      [SECTION] Myjson Forward
 *      [SECTION] Literals Forward
 *
 *  Details: Details Namespace
 *
 *      [SECTION] Details : Enums
 *      [SECTION] Details : Structures
 *      [SECTION] Details : Functions
 *
 *  Myjson: Myjson Namespace
 *
 *      [SECTION] Myjson : Enums
 *      [SECTION] Myjson : Structures
 *      [SECTION] Myjson : Functions
 *
 *  Literals: Literals Namespace
 *
 *      [SECTION] Literals : Functions
 *
 */

#define DJOEZEKE_MYJSON_HPP

// clang-format off

#include <cstddef>
#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MYJSON_SKIP_VERSION_CHECK
    #if defined(MYJSON_VERSION_MAJOR) && defined(MYJSON_VERSION_MINOR) && defined(MYJSON_VERSION_PATCH)
        #if MYJSON_VERSION_MAJOR != 1 || MYJSON_VERSION_MINOR != 0 || MYJSON_VERSION_PATCH != 0
            #warning "Already included a different version of the library!"
        #endif
    #endif
#endif  // MYJSON_SKIP_VERSION_CHECK

/**
 * @defgroup version version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def MYJSON_VERSION_MAJOR
 * @brief Major version number of the library.
 * @note If this were version 1.2.3, this value would be 1.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYJSON_VERSION_MAJOR
    #define MYJSON_VERSION_MAJOR 0
#endif // MYJSON_VERSION_MAJOR

/**
 * @def MYJSON_VERSION_MINOR
 * @brief Minor version number of the library.
 * @note If this were version 1.2.3, this value would be 2.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYJSON_VERSION_MINOR
    #define MYJSON_VERSION_MINOR 1
#endif // MYJSON_VERSION_MINOR

/**
 * @def MYJSON_VERSION_PATCH
 * @brief Patch version number of the library.
 * @note If this were version 1.2.3, this value would be 3.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYJSON_VERSION_PATCH
    #define MYJSON_VERSION_PATCH 0
#endif // MYJSON_VERSION_PATCH

/**
 * @def MYJSON_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 * @sa MyGetVersion
 */
#ifndef MYJSON_VERSION
    #define MYJSON_VERSION "0.1.0"
#endif // MYJSON_VERSION

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Configurations
//-----------------------------------------------------------------------------

/**
 * @defgroup configuration Library Configurations.
 * @brief Preprocessor macros for configuring library functionality.
 * @{
 */

/**
 * @brief Configure file with user config.
 */
#ifdef MYJSON_CONFIG
    #include MYJSON_CONFIG
#endif // MYJSON_CONFIG

/**
 * @def MYJSON_IMPLEMENTATION
 * @brief Enable implementation of library.
 * @warning Comment to diable implementation.
 */
#define MYJSON_IMPLEMENTATION 1

/**
 * @def MYJSON_DISABLE_PARSER
 * @brief Exclude the Parser APIs.
 * @warning Uncomment to diable parsing.
 */
// #define MYJSON_DISABLE_PARSER 1

/**
 * @def MYJSON_DISABLE_EMITTER
 * @brief Exclude the Emitter APIs.
 * @warning Uncomment to diable emitting.
 */
// #define MYJSON_DISABLE_EMITTER 1

/**
 * @def MYJSON_NO_STL
 * @brief Diable use of STL Containers.
 * @warning Uncomment to diable STL.
 */
// #define MYJSON_NO_STL 1

/**
 * @def MYJSON_NO_EXCEPTIONS
 * @brief Stop the use of exceptions.
 * @warning Uncomment to diable exceptions.
 */
// #define MYJSON_NO_EXCEPTIONS 1

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Include Mess
//-----------------------------------------------------------------------------


#include <stdint.h>
#include <stdio.h>
#include <uchar.h> // char16_t, char32_t

#ifndef MYJSON_NO_STL
    #ifndef MYJSON_NO_IO
        #include <iosfwd>
        #include <istream>
        #include <ostream>
    #endif  // MYJSON_NO_IO
    #include <map>
    #include <optional>
    #include <string>
    #include <variant>
    #include <vector>
#endif // MYJSON_NO_STL

#ifndef MYJSON_NO_EXCEPTIONS
    #include <exception>
#endif

//-----------------------------------------------------------------------------
// [SECTION] Compiler & Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup platform Platform Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name Platform, like `APPLE`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define MYJSON_PLATFORM_IS(name) MYJSON_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#ifdef __APPLE__
  	/**
   	* @brief Defined if compiling for Apple.
   	*/
	#define MYJSON_PLATFORM_IS_APPLE 1
    #define MYJSON_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
  	/**
   	* @brief Defined if compiling for Linux.
   	*/
	#define MYJSON_PLATFORM_IS_LINUX 1
  	#define MYJSON_PLATFORM_NAME_IS "Linux"
#elif defined(__WIN32__) || defined(_WIN32) || defined(__MINGW32__)
  	/**
   	* @brief Defined if compiling for Windows.
   	*/
  	#define MYJSON_PLATFORM_IS_WINDOWS 1
  	#define MYJSON_PLATFORM_NAME_IS "Windows"
#else
  	/**
   	* @brief Defined if compiling for Others.
   	*/
  	#define MYJSON_PLATFORM_IS_OTHERS 1
  	#define MYJSON_PLATFORM_NAME_IS "Others"
#endif

/** @} */

/**
 * @defgroup language Standard Checks
 * @{
 */

// With the MSVC compilers, the value of __cplusplus is by default always "199611L"(C++98).
// To avoid that, the library instead references _MSVC_LANG which is always set a correct value.
// See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/ for more details.
#if defined(_MSVC_LANG) && !defined(__clang__)
    #define MYJSON_CPLUSPLUS _MSVC_LANG
#else
    #define MYJSON_CPLUSPLUS __cplusplus
#endif

// C++ language standard detection

#if !defined(MYJSON_HAS_CXX_26) && !defined(MYJSON_HAS_CXX_23) && !defined(MYJSON_HAS_CXX_20)\
    && !defined(MYJSON_HAS_CXX_17) && !defined(MYJSON_HAS_CXX_14) && !defined(MYJSON_HAS_CXX_11)
    #if (defined(MYJSON_CPLUSPLUS) && MYJSON_CPLUSPLUS > 202302L)
        #define MYJSON_HAS_CXX_26
        #define MYJSON_HAS_CXX_23
        #define MYJSON_HAS_CXX_20
        #define MYJSON_HAS_CXX_17
        #define MYJSON_HAS_CXX_14
    #elif (defined(MYJSON_CPLUSPLUS) && MYJSON_CPLUSPLUS > 202002L)
        #define MYJSON_HAS_CXX_23
        #define MYJSON_HAS_CXX_20
        #define MYJSON_HAS_CXX_17
        #define MYJSON_HAS_CXX_14
    #elif (defined(MYJSON_CPLUSPLUS) && MYJSON_CPLUSPLUS > 201703L)
        #define MYJSON_HAS_CXX_20
        #define MYJSON_HAS_CXX_17
        #define MYJSON_HAS_CXX_14
    #elif (defined(MYJSON_CPLUSPLUS) && MYJSON_CPLUSPLUS > 201402L)
        #define MYJSON_HAS_CXX_17
        #define MYJSON_HAS_CXX_14
    #elif (defined(MYJSON_CPLUSPLUS) && MYJSON_CPLUSPLUS > 201103L)
        #define MYJSON_HAS_CXX_14
    #endif
    // Always specified because it is the minimal required version
    #define MYJSON_HAS_CXX_11
#endif

/** @} */

/**
 * @defgroup compiler Compiler Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name  Compiler brand, like `MSVC`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define MYJSON_COMPILER_IS(name) MYJSON_COMPILER_IS_##name

/**
 * @brief   Checks if the compiler is of given brand and is newer than or equal
 *          to the passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name >= x.y.z.
 * @retval  false  otherwise.
 */
#define MYJSON_COMPILER_SINCE(name, x, y, z)                                 \
  (MYJSON_COMPILER_IS(name) && ((MYJSON_COMPILER_VERSION_MAJOR > (x)) ||     \
                                ((MYJSON_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((MYJSON_COMPILER_VERSION_MINOR > (y)) ||   \
                                  ((MYJSON_COMPILER_VERSION_MINOR == (y)) && \
                                   (MYJSON_COMPILER_VERSION_PATCH >= (z)))))))

/**
 * @brief   Checks if  the compiler  is of  given brand and  is older  than the
 *          passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name < x.y.z.
 * @retval  false  otherwise.
 */
#define MYJSON_COMPILER_BEFORE(name, x, y, z)                                \
  (MYJSON_COMPILER_IS(name) && ((MYJSON_COMPILER_VERSION_MAJOR < (x)) ||     \
                                ((MYJSON_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((MYJSON_COMPILER_VERSION_MINOR < (y)) ||   \
                                  ((MYJSON_COMPILER_VERSION_MINOR == (y)) && \
                                   (MYJSON_COMPILER_VERSION_PATCH < (z)))))))


/// Compiler is gcc
#if !defined(__GNUC__)
    #define MYJSON_COMPILER_IS_GCC 0
#else
    #define MYJSON_COMPILER_IS_GCC 1
    #define MYJSON_COMPILER_VERSION_MAJOR __GNUC__
    #define MYJSON_COMPILER_VERSION_MINOR __GNUC_MINOR__
    #define MYJSON_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/// Compiler is clang
#if !defined(__clang__)
    #define MYJSON_COMPILER_IS_CLANG 0
#elif MYJSON_COMPILER_IS(GCC)
    #define MYJSON_COMPILER_IS_CLANG 0
#else
    #define MYJSON_COMPILER_IS_CLANG 1
    #define MYJSON_COMPILER_VERSION_MAJOR __clang_major__
    #define MYJSON_COMPILER_VERSION_MINOR __clang_minor__
    #define MYJSON_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
    #define MYJSON_COMPILER_IS_MSVC 0
#elif MYJSON_COMPILER_IS(CLANG)
    #define MYJSON_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
    #define MYJSON_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZZ */
    #define MYJSON_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
    #define MYJSON_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
    #define MYJSON_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
    #define MYJSON_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZ */
    #define MYJSON_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
    #define MYJSON_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
    #define MYJSON_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
    #define MYJSON_COMPILER_IS_MSVC 1
    /* _MSC_VER = XXYY */
    #define MYJSON_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
    #define MYJSON_COMPILER_VERSION_MINOR (_MSC_VER % 100)
    #define MYJSON_COMPILER_VERSION_PATCH 0
#endif

/** @} */

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */
 
#if MYJSON_COMPILER_IS(GCC)
    #define MYJSON_PRAGMA_TO_STR(x) _Pragma(#x)
    #define MYJSON_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
    #define MYJSON_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
    #define MYJSON_GCC_SUPPRESS_WARNING(w) MYJSON_PRAGMA_TO_STR(GCC diagnostic ignored w)
    #define MYJSON_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
        MYJSON_GCC_SUPPRESS_WARNING_PUSH MYJSON_GCC_SUPPRESS_WARNING(w)
#else // MYJSON_GCC
    #define MYJSON_GCC_SUPPRESS_WARNING_PUSH
    #define MYJSON_GCC_SUPPRESS_WARNING(w)
    #define MYJSON_GCC_SUPPRESS_WARNING_POP
    #define MYJSON_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYJSON_GCC

#if MYJSON_COMPILER_IS(MSVC)
    #define MYJSON_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
    #define MYJSON_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
    #define MYJSON_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
    #define MYJSON_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
        MYJSON_MSVC_SUPPRESS_WARNING_PUSH MYJSON_MSVC_SUPPRESS_WARNING(w)
#else // MYJSON_MSVC
    #define MYJSON_MSVC_SUPPRESS_WARNING_PUSH
    #define MYJSON_MSVC_SUPPRESS_WARNING(w)
    #define MYJSON_MSVC_SUPPRESS_WARNING_POP
    #define MYJSON_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYJSON_MSVC

#if MYJSON_COMPILER_IS(CLANG)
    #define MYJSON_PRAGMA_TO_STR(x) _Pragma(#x)
    #define MYJSON_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
    #define MYJSON_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
    #define MYJSON_CLANG_SUPPRESS_WARNING(w) MYJSON_PRAGMA_TO_STR(clang diagnostic ignored w)
    #define MYJSON_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
        MYJSON_CLANG_SUPPRESS_WARNING_PUSH MYJSON_CLANG_SUPPRESS_WARNING(w)
#else // MYJSON_CLANG
    #define MYJSON_CLANG_SUPPRESS_WARNING_PUSH
    #define MYJSON_CLANG_SUPPRESS_WARNING(w)
    #define MYJSON_CLANG_SUPPRESS_WARNING_POP
    #define MYJSON_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYJSON_CLANG

#if MYJSON_COMPILER_IS(GCC)
    #define MYJSON_DIABLE_WARNINGS                  \
        MYJSON_GCC_SUPPRESS_WARNING_PUSH            \
        MYJSON_GCC_SUPPRESS_WARNING("-Weverything")
    
    #define MYJSON_ENABLE_WARNINGS                  \
        MYJSON_GCC_SUPPRESS_WARNING_POP
#endif // MYJSON_COMPILER_IS_GCC

#if MYJSON_COMPILER_IS(MSVC)
    #define MYJSON_DIABLE_WARNINGS                  \
        MYJSON_MSVC_SUPPRESS_WARNING_PUSH           \
        MYJSON_MSVC_SUPPRESS_WARNING()
    
    #define MYJSON_ENABLE_WARNINGS                  \
        MYJSON_MSVC_SUPPRESS_WARNING_POP
#endif // MYJSON_COMPILER_IS_MSVC

#if MYJSON_COMPILER_IS(CLANG)
    #define MYJSON_DIABLE_WARNINGS                  \
        MYJSON_CLANG_SUPPRESS_WARNING_PUSH          \
        MYJSON_CLANG_SUPPRESS_WARNING("-Weverything")
    
    #define MYJSON_ENABLE_WARNINGS                  \
        MYJSON_CLANG_SUPPRESS_WARNING_POP
#endif // MYJSON_COMPILER_IS_CLANG

/** @} */

/**
 * @defgroup compiler Compiler Attributes
 * @{
 */

 /** compiler builtin check */
#ifndef MYJSON_HAS_BUILTIN
	#ifdef __has_builtin
    	#define MYJSON_HAS_BUILTIN(x) __has_builtin(x)
  	#else
    	#define MYJSON_HAS_BUILTIN(x) 0
  	#endif
#endif

/** compiler attribute check */
#ifndef MYJSON_HAS_ATTRIBUTE
  	#ifdef __has_attribute
    	#define MYJSON_HAS_ATTRIBUTE(x) __has_attribute(x)
  	#else
    	#define MYJSON_HAS_ATTRIBUTE(x) 0
  	#endif
#endif

/** compiler feature check */
#ifndef MYJSON_HAS_FEATURE
  	#ifdef __has_feature
    	#define MYJSON_HAS_FEATURE(x) __has_feature(x)
  	#else
    	#define MYJSON_HAS_FEATURE(x) 0
  	#endif
#endif

/** compiler include check */
#ifndef MYJSON_HAS_INCLUDE
  	#ifdef __has_include
    	#define MYJSON_HAS_INCLUDE(x) __has_include(x)
  	#else
    	#define MYJSON_HAS_INCLUDE(x) 0
  	#endif
#endif

/** compiler cpp attribute check */
#ifndef MYJSON_HAS_CPP_ATTRIBUTE
  	#ifdef __has_cpp_attribute
        #define MYJSON_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
  	#else
    	#define MYJSON_HAS_CPP_ATTRIBUTE(x) 0
  	#endif
#endif

/** inline for compiler */
#ifndef MYJSON_INLINE
  	#if defined(__cplusplus) || MYJSON_STDC >= 199901L
    	#define MYJSON_INLINE inline
  	#elif MYJSON_HAS_ATTRIBUTE(always_inline) || MYJSON_COMPILER_SINCE(GCC, 4, 0, 0)
    	#define MYJSON_INLINE __inline__ __attribute__((always_inline))
  	#else
    	#define MYJSON_INLINE
  	#endif
#endif

/** noinline for compiler */
#ifndef MYJSON_NOINLINE
  	#if MYJSON_COMPILER_SINCE(MSVC, 14, 0, 0)
    	#define MYJSON_NOINLINE __declspec(noinline)
  	#elif MYJSON_HAS_ATTRIBUTE(noinline) || (MYJSON_COMPILER_SINCE(GCC, 4, 0, 0))
    	#define MYJSON_NOINLINE __attribute__((noinline))
  	#else
    	#define MYJSON_NOINLINE
  	#endif
#endif

/** align for compiler */
#ifndef MYJSON_ALIGN
  	#if MYJSON_COMPILER_SINCE(MSVC, 13, 0, 0)
    	#define MYJSON_ALIGN(x) __declspec(align(x))
  	#elif MYJSON_HAS_ATTRIBUTE(aligned) || defined(__GNUC__)
    	#define MYJSON_ALIGN(x) __attribute__((aligned(x)))
  	#elif MYJSON_CPP_VERSION >= 201103L
    	#define MYJSON_ALIGN(x) alignas(x)
  	#else
    	#define MYJSON_ALIGN(x)
  	#endif
#endif

/** deprecate warning */
#if defined(MYJSON_HAS_CXX_14)
    #define MYJSON_DEPRECATED(msg) [[deprecated(msg)]]
#else
    #define MYJSON_DEPRECATED(msg)
#endif

#ifndef MYJSON_NODISCARD
    #define MYJSON_NODISCARD [[nodiscard]]
#endif

// switch usage of constexpr keyword depending on active C++ standard.
#if defined(MYJSON_HAS_CXX_17)
    #define MYJSON_CONSTEXPR constexpr
#else
    #define MYJSON_CONSTEXPR
#endif

// switch usage of [[likely]] C++ attribute which has been available since C++20.
#if defined(MYJSON_HAS_CXX_20) && MYJSON_HAS_CPP_ATTRIBUTE(likely) >= 201803L
    #define MYJSON_LIKELY(expr) (!!(expr)) [[likely]]
#elif MYJSON_HAS_BUILTIN(__builtin_expect)
    #define MYJSON_LIKELY(expr) (__builtin_expect(!!(expr), 1))
#else
    #define MYJSON_LIKELY(expr) (!!(expr))
#endif

// switch usage of [[unlikely]] C++ attribute which has been available since C++20.
#if defined(MYJSON_HAS_CXX_20) && MYJSON_HAS_CPP_ATTRIBUTE(unlikely) >= 201803L
    #define MYJSON_UNLIKELY(expr) (!!(expr)) [[unlikely]]
#elif MYJSON_HAS_BUILTIN(__builtin_expect)
    #define MYJSON_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
#else
    #define MYJSON_UNLIKELY(expr) (!!(expr))
#endif

// switch usage of char8_t which has been available since C++20.
#if defined(MYJSON_HAS_CXX_20) && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
    #define MYJSON_HAS_CHAR8_T (1)
#else
    #define MYJSON_HAS_CHAR8_T (0)
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] API Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if MYJSON_PLATFORM_IS_WINDOWS
    #define MYJSON_API_EXPORT __declspec(dllexport)
    #define MYJSON_API_IMPORT __declspec(dllimport)
    #define MYJSON_NO_EXPORT
#else
    #define MYJSON_API_EXPORT __attribute__((visibility("default")))
    #define MYJSON_API_IMPORT __attribute__((visibility("default")))
    #define MYJSON_NO_EXPORT __attribute__((visibility("hidden")))
#endif  // MYJSON_PLATFORM_IS_WINDOWS

/**
 * @def MYJSON_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct
 * symbol visibility on all platforms.
 */

#if defined(MYJSON_BUILD_STATIC)
    #define MYJSON_API
#elif defined(MYJSON_BUILD_SHARED) || defined(MYJSON_EXPORTS)
    /* We are building this library */
    #define MYJSON_API MYJSON_API_EXPORT
#elif defined(MYJSON_LOAD_SHARED) || defined(MYJSON_IMPORTS)
    /* We are using this library */
    #define MYJSON_API MYJSON_API_IMPORT
#else  // MYJSON_BUILD_STATIC
    #define MYJSON_API
#endif  // MYJSON_BUILD_STATIC

/** @} */

#define MYJSON_VERSION_CONCAT_(major, minor, patch) v##major##_##minor##_##patch
#define MYJSON_VERSION_CONCAT(major, minor, patch) MYJSON_VERSION_CONCAT_(major, minor, patch)
#define MYJSON_VERSION_NAMESPACE_BEGIN  inline namespace \
    MYJSON_VERSION_CONCAT(MYJSON_VERSION_MAJOR, MYJSON_VERSION_MINOR, MYJSON_VERSION_PATCH) {
#define MYJSON_VERSION_NAMESPACE_END    } /* inline namespace MYJSON_VERSION */

#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS)) && !defined(MYJSON_NO_EXCEPTIONS)
    #define MYJSON_THROW(exception) throw exception
    #define MYJSON_TRY try
    #define MYJSON_CATCH(exception) catch(exception)
#else
  #define MYJSON_REQUIRE(expression, error)                                                        \
    do                                                                                             \
    {                                                                                              \
      if (MYJSON_UNLIKELY(!(expression)))                                                          \
      {                                                                                            \
        printf("Error: %s (%s:%d)\n", error, __FILE__, __LINE__);        \
        abort();                                                                                   \
      }                                                                                            \
    } while (0)
    
    #define MYJSON_THROWE(exception) MYJSON_REQUIRE(false, exception.what())
    #define MYJSON_THROW(exception) abort()
    #define MYJSON_TRY if(true)
    #define MYJSON_CATCH(exception) if(false)
#endif

#ifndef MYJSON_ASSERT
    #include <assert.h> // assert
    #define MYJSON_ASSERT(x) assert(x)
#else
    #define MYJSON_ASSERT(x)
#endif

#if MYJSON_COMPILER_SINCE(GCC, 6, 0, 0)
    #define MYJSON_QUOTE_OPERATOR operator""_json
    #define MYJSON_POINTER_QUOTE_OPERATOR operator""_json_pointer
#else
    #define MYJSON_QUOTE_OPERATOR operator"" _json
    #define MYJSON_POINTER_QUOTE_OPERATOR operator""_json_pointer
#endif

/** 
 * @brief One.
 *
 *  This is only semantic sugar for the number `1`.
 *  @note You can instead use `1` or `true` .
 *
 */
#define MYJSON_TRUE 1

/** 
 * @brief Zero.
 *
 *  This is only semantic sugar for the number `0`.
 *  @note You can instead use `0` or `false` .
 *
 */
#define MYJSON_FALSE 0

// clang-format on

#pragma region Forward

/**
 * @namespace myjson
 * @brief Primary library namespace for the myjson API.
 *
 * All public types, enums and functions are declared in this namespace.
 */
namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    /**
     * @namespace myjson::detail
     * @brief Internal implementation details.
     *
     * Types and helpers in this namespace are not part of the public API
     * and are subject to change without notice.
     */
    namespace detail
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Details Forward
        //-----------------------------------------------------------------------------

        /** Enumerations */

        enum class token_t : uint8_t;
        enum class error_t : uint8_t;
        enum class event_t : uint8_t;
        enum class value_t : uint8_t;
        enum class break_t : uint8_t;

        /** Structures */

        struct mark;
        struct event;
        struct token;

        // input
        class lexer;
        class parser;
        class iadapter;
        class deserializer;
        class file_iadapter;
        class memory_iadapter;

#ifndef MYJSON_NO_STL
        class stream_iadapter;
        class iterator_iadapter;
#endif // MYJSON_NO_STL

        // output
        class emitter;
        class oadapter;
        class serializer;
        class file_iadapter;
        class memory_oadapter;

#ifndef MYJSON_NO_STL
        class stream_oadapter;
        class iterator_oadapter;
#endif // MYJSON_NO_STL

        // encoding
        struct utf8;
        struct utf16;
        struct utf32;

    } // namespace detail

    MYJSON_VERSION_NAMESPACE_END

} // namespace myjson

/**
 * @namespace myjson
 * @brief The Api namespace myjson::
 */
namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson Forward
    //-----------------------------------------------------------------------------

    /** Enumerations */

    enum class encoding : uint8_t;
    enum class node_t : uint8_t;

    /** Structures */

    class json;
    class version;
    class formatter;

    class json;
    class json_patch;
    class json_pointer;
    class json_merge_patch;

#ifndef MYJSON_NO_EXCEPTIONS
    class exception;
    class io_error;
    class parse_error;
    class encoding_error;
#endif // MYJSON_NO_EXCEPTIONS

    MYJSON_VERSION_NAMESPACE_END

} // namespace myjson

namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    /**
     * @namespace literals
     * @brief The Literals namespace myjson::literals::
     */
    namespace literals
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Literals Forward
        //-----------------------------------------------------------------------------

    } // namespace literals

    MYJSON_VERSION_NAMESPACE_END

} // namespace myjson

#pragma endregion // Forward

#pragma region Detail

/**
 * @namespace myjson
 * @brief The API namespace myjson::
 */
namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    /**
     * @namespace detail
     * @brief The Details namespace myjson::detail::
     */
    namespace detail
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Details : Enums
        //-----------------------------------------------------------------------------

        /**
         * @defgroup enum Enums
         * @brief Detail enum types and flags.
         * @{
         */

        enum class token_t : uint8_t
        {
            unknown,
            array_end,
            stream_end,
            object_end,
            array_start,
            end_of_input,
            stream_start,
            object_start,
            null_literal,
            true_literal,
            string_value,
            number_value,
            false_literal,
            name_separator,
            value_separator,
        };

        enum class error_t : uint8_t
        {
            unknown,
            lexer,
            parser,
            reader,
            writer,
            emitter,
            encoding,
            decoding,
        };

        enum class event_t : uint8_t
        {
            unknown,
        };

        enum class value_t : uint8_t
        {
            unknown,
        };

        enum class break_t : uint8_t
        {
            any, /** Let the parser choose the break type. */
            cr,  /** Use CR for line breaks (Mac style). */
            ln,  /** Use LN for line breaks (Unix style). */
            crln /** Use CR LN for line breaks (DOS style). */

        };

        /** @} group enum */

        //-----------------------------------------------------------------------------
        // [SECTION] Details : Structures
        //-----------------------------------------------------------------------------

        /**
         * @defgroup structs Structures
         * @brief Detail types and Structures.
         * @{
         */

        struct mark
        {
            size_t column{0}; /** The position column. */
            size_t index{0};  /** The position index. */
            size_t line{0};   /** The position line. */
        };

        struct event
        {
            event_t type{event_t::unknown}; /** The event type. */
            mark start{};                   /** The beginning of the token. */
            mark end{};                     /** The end of the token. */
        };

        struct token
        {
            token_t type{token_t::unknown}; /** The token type. */
#ifndef MYJSON_NO_STL
            std::string text; /** Token text/value (for string/number). */
#else
            union
            {
                char *value;
            } value;
#endif
            mark start{}; /** The beginning of the token. */
            mark end{};   /** The end of the token. */
        };

        /** @} group structs */

        //-----------------------------------------------------------------------------
        // [SECTION] Details : Encoding
        //-----------------------------------------------------------------------------

        /**
         * @defgroup encoding
         * @brief Encoding helpers for UTF-8/16/32 and byte-order utilities.
         *
         * These helpers are used internally by the parser and emitter to
         * detect input encodings, decode individual code points and encode
         * code points back into the target encoding.
         */

        using encoding = myjson::encoding;

#ifdef endian
#undef endian
#endif

        /**
         * @brief Internal numeric endianness representation.
         */
        using myjson_endian_value_t = uint16_t;

        struct myjson_endian_t
        {
#if MYJSON_COMPILER_IS_GCC
            static constexpr myjson_endian_value_t little = __ORDER_LITTLE_ENDIAN__;
            static constexpr myjson_endian_value_t big = __ORDER_BIG_ENDIAN__;
            static constexpr myjson_endian_value_t native = __BYTE_ORDER__;
#else
            static constexpr myjson_endian_value_t little = 0;
            static constexpr myjson_endian_value_t big = 1;
            static constexpr myjson_endian_value_t native = little;
#endif // MYJSON_COMPILER_IS_GCC
        };

        /**
         * @brief Determine the text encoding of the supplied buffer.
         *
         * This function performs a best-effort inspection of the initial
         * bytes available at @p data (up to @p size) and returns a
         * corresponding myjson::encoding value describing the likely
         * encoding of the input text. Detection considers byte-order
         * marks (BOM), typical UTF-8/16/32 headers, and short sequences
         * that are unambiguous. The function never throws.
         *
         * Usage:
         * - Call with the pointer to the first byte of the input and the
         *   number of bytes available for inspection. Typical callers pass
         *   the whole buffer or the first 4 bytes. If @p size is 0 the
         *   function will return myjson::encoding::unspecified.
         *
         * @param data Pointer to the input bytes to examine. May be nullptr
         *             if @p size is zero.
         * @param size Number of bytes available at @p data.
         *
         * @returns A value from myjson::encoding describing the detected encoding
         *      and myjson::encoding::unspecified if detection failed or
         *      the input is insufficient to make a determination.
         */
        encoding determine_encoding(void *data, size_t size);

        /**
         * @brief UTF-8 encoding helpers.
         *
         * The helper exposes low-level operations used by the parser and
         * encoder to convert between encoded byte sequences and Unicode
         * code points. Functions return the number of bytes consumed or
         * produced on success, and -1 on error.
         *
         * Typical usage examples:
         * - decode(): pass a pointer to UTF-8 bytes and available size to
         *   obtain the decoded Unicode code point and number of bytes
         *   consumed.
         * - encode(): provide a Unicode code point and an output buffer
         *   to write the UTF-8 encoded bytes.
         */
        struct utf8
        {

#if MYJSON_HAS_CHAR8_T
            using char_t = char8_t;
#else
            using char_t = char;
#endif // MYJSON_HAS_CHAR8_T

            /**
             * @brief Decode a single UTF-8 code point from a byte buffer.
             *
             * Reads 1..4 bytes from @p data (not more than @p size) and
             * writes the resulting Unicode code point into @p value.
             *
             * @param data Pointer to UTF-8 bytes.
             * @param size Number of bytes available.
             * @param[out] value Decoded Unicode code point on success.
             * @return Number of bytes consumed (1..4) or -1 on error.
             */
            static int decode(const char *data, size_t size, unsigned int &value);

            /**
             * @brief Encode a Unicode code point as UTF-8.
             *
             * Writes the UTF-8 byte sequence for @p codepoint into
             * @p output if there is enough room (@p size bytes available).
             *
             * @param codepoint The Unicode code point to encode.
             * @param[out] output Destination buffer for encoded bytes.
             * @param size Size of the destination buffer in bytes.
             * @return Number of bytes written (1..4) or -1 on error.
             */
            static int encode(unsigned int codepoint, char_t *output, size_t size);

            /**
             * @brief Convert a UTF-8 std::string to a UTF-16 byte vector.
             *
             * This helper is convenience for producing a sequence of bytes
             * representing UTF-16 code units (endian-aware) from a UTF-8
             * C++ string.
             *
             * @param string Input UTF-8 encoded string.
             * @param order Desired byte order for output (default: native).
             * @return A vector of bytes containing the UTF-16 encoding.
             */
            static std::vector<unsigned char> to_utf16(const std::string &string, myjson_endian_value_t order);

            /**
             * @brief Convert a UTF-8 std::string to a UTF-32 byte vector.
             *
             * Similar to to_utf16() but produces UTF-32 (4 bytes per
             * code point), arranged according to @p order.
             *
             * @param string Input UTF-8 encoded string.
             * @param order Desired byte order for output (default: native).
             * @return A vector of bytes containing the UTF-32 encoding.
             */
            static std::vector<unsigned char> to_utf32(const std::string &string, myjson_endian_value_t order);
        };

        /**
         * @brief UTF-16 encoding helpers.
         *
         * Handles decoding of one or two UTF-16 code units (surrogate
         * pairs) into a single Unicode code point and encoding code
         * points into UTF-16 code units. All functions accept an
         * explicit @p order describing byte order for multi-byte units.
         */
        struct utf16
        {
            using char_t = char16_t;

            /**
             * @brief Decode a UTF-16 code unit sequence into a unicode code point.
             *
             * The function reads 2 or 4 bytes depending on whether a surrogate
             * pair is present. The @p data pointer is treated as a byte pointer
             * using the @p order endianness otherwise native endianness.
             *
             * @param data Pointer to UTF-16 data (bytes).
             * @param size Number of bytes available at @p data.
             * @param[out] value Decoded Unicode code point on success.
             * @param order Order to interprete incoming bytes.
             * @return Number of bytes consumed (2 or 4) or -1 on error.
             */
            static int decode(const char *data, size_t size, unsigned int &value, myjson_endian_value_t order);

            /**
             * @brief Encode a Unicode code point into UTF-16 code units.
             *
             * Writes one or two @p codepoint (2 or 4 bytes) to @p output
             * depending on whether the code point requires a surrogate pair
             * using the @p order endianness otherwise the native endianness.
             *
             * @param codepoint The Unicode code point to encode.
             * @param[out] output Destination buffer for UTF-16 code units.
             * @param size Size of the destination buffer in bytes.
             * @param order Order to represent/write the code units (codepoint) in.
             * @return Number of UTF-16 bytes written (2 or 4) or -1 on error.
             */
            static int encode(unsigned int codepoint, char_t *output, size_t size, myjson_endian_value_t order);

            /**
             * @brief Convert a UTF-16 byte vector into a UTF-8 std::string.
             *
             * Interprets @p bytes as UTF-16 code units in the given
             * @p order and returns the UTF-8 encoded form.
             *
             * @param bytes Byte vector containing UTF-16 code units.
             * @param order Byte order of the input data.
             * @return UTF-8 encoded std::string on success. If input is
             *         ill-formed the function will attempt best-effort
             *         conversion and may replace invalid sequences.
             */
            static std::string to_utf8(const std::vector<unsigned char> &bytes, myjson_endian_value_t order);
        };

        /**
         * @brief UTF-32 encoding helpers.
         *
         * UTF-32 uses a fixed 4-byte representation per Unicode code
         * point. These helpers decode and encode individual code points
         * and can convert between byte vectors and UTF-8 strings.
         */
        struct utf32
        {
            using char_t = char32_t;

            /**
             * @brief Decode a UTF-32 encoded value.
             *
             * Reads up to 4 bytes from @p data interpreting them according
             * to @p order and returns the decoded code point.
             *
             * @param data Pointer to input bytes containing a UTF-32 unit.
             * @param size Number of bytes available at @p data (should be >=4).
             * @param[out] value Decoded Unicode code point on success.
             * @param order Byte order of the input bytes.
             * @return Number of bytes consumed (4) on success, or -1 on error.
             */
            static int decode(const char *data, size_t size, unsigned int &value, myjson_endian_value_t order);

            /**
             * @brief Encode a Unicode code point as UTF-32.
             *
             * Writes 4 bytes for @p codepoint into @p output using the
             * specified @p order.
             *
             * @param codepoint Unicode code point to encode.
             * @param[out] output Buffer to receive char32_t values.
             * @param size Number of char32_t entries available in @p output.
             * @param order Byte order to use for the output.
             * @return Number of units written (1 == 4 bytes) or -1 on error.
             */
            static int encode(unsigned int codepoint, char_t *output, size_t size, myjson_endian_value_t order);

            /**
             * @brief Convert a UTF-32 byte vector into a UTF-8 std::string.
             *
             * @param bytes Byte vector containing UTF-32 code units.
             * @param order Byte order of the input data.
             * @return UTF-8 encoded std::string on success. Invalid input
             *         sequences are handled best-effort.
             */
            static std::string to_utf8(const std::vector<unsigned char> &bytes, myjson_endian_value_t order);
        };

        /** @} group encoding */

        /**
         * @defgroup input
         * @brief
         * @{
         */

        /**
         * @brief Abstract base for input adapters used by the parser.
         *
         * Implementers must advance the internal reading position by the number of
         * bytes actually copied into the caller buffer. All methods return
         * std::nullopt on error to allow callers to detect failures uniformly.
         */
        class iadapter
        {
        public:
            /**
             * @brief Default copy assignment operator
             */
            iadapter() = default;

            /**
             * @brief Default copy constructor
             */
            iadapter(const iadapter &) = default;

            /**
             * @brief Default move constructor
             */
            iadapter(iadapter &&) noexcept = default;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * Implementations must copy at most @p size bytes into the provided
             * buffer and advance the stream position accordingly.
             *
             * @param[out] data Buffer to receive the bytes. Must be at least @p size bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            virtual size_t read(void *data, size_t size) = 0;

            /**
             * @brief Default copy assignment operator
             */
            iadapter &operator=(const iadapter &) = default;

            /**
             * @brief Default move assignment operator
             */
            iadapter &operator=(iadapter &&) noexcept = default;

            /**
             * @brief Virtual destructor.
             */
            virtual ~iadapter() = default;
        };

        /**
         * @class file_iadapter
         * @brief Input adapter that reads from a C `FILE*`.
         */
        class file_iadapter : public iadapter
        {
        public:
            /**
             * @brief Construct the stream from a FILE pointer.
             * @param file File pointer to read from (must be valid for the lifetime).
             * @throws myjson::exception on error.
             */
            explicit file_iadapter(FILE *file);

            /**
             * @brief Deleted copy constructor
             */
            file_iadapter(const file_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            file_iadapter(file_iadapter &&) noexcept = default;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            size_t read(void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            file_iadapter &operator=(const file_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            file_iadapter &operator=(file_iadapter &&) = delete;

        private:
            /** Member data */
            FILE *m_file;
        };

#ifndef MYJSON_NO_STL
        /**
         * @class stream_iadapter
         * @brief Input adapter that reads from a C++ `std::istream`.
         */
        class stream_iadapter : public iadapter
        {
        public:
            /**
             * @brief Construct a stream-based input adapter from an std::istream.
             * @param stream Reference to an opened input stream supplying bytes.
             */
            explicit stream_iadapter(std::istream &stream);

            /**
             * @brief Deleted copy constructor
             */
            stream_iadapter(const stream_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            stream_iadapter(stream_iadapter &&) noexcept = default;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            size_t read(void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            stream_iadapter &operator=(const stream_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            stream_iadapter &operator=(stream_iadapter &&) = delete;

        private:
            /** Member data */
            std::istream *m_stream;
        };

#endif // MYJSON_NO_STL

        /**
         * @class memory_iadapter
         * @brief Input adapter that reads from a `char*`.
         */
        class memory_iadapter : public iadapter
        {
        public:
            /**
             * @brief Construct the stream from a C-String pointer.
             * @param data Pointer to the data to read from.
             * @param size Size of the data, in bytes
             * @throws myjson::exception on error.
             */
            memory_iadapter(void *data, size_t size);

            /**
             * @brief Deleted copy constructor
             */
            memory_iadapter(const memory_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            memory_iadapter(memory_iadapter &&) noexcept = default;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            size_t read(void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            memory_iadapter &operator=(const memory_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            memory_iadapter &operator=(memory_iadapter &&) = delete;

        private:
            /** Member data */
            size_t m_pos;
            size_t m_size;
            void *m_data;
        };

        /**
         * @class lexer
         * @brief Lexical analyzer for JSON input.
         *
         * The lexer reads bytes from an input adapter and produces tokens
         * consumed by the parser. It is a non-copyable, movable type.
         */
        class lexer
        {
        public:
            /**
             * @brief Construct a lexer from an input adapter.
             * @param adapter The input adapter providing raw bytes.
             */
            explicit lexer(iadapter *adapter);

            /**
             * @brief Deleted copy constructor
             */
            lexer(const lexer &) = delete;

            /**
             * @brief Deleted move constructor
             */
            lexer(lexer &&) noexcept = delete;

            /**
             * @brief Deleted copy assignment operator
             */
            lexer &operator=(const lexer &) = delete;

            /**
             * @brief Deleted move assignment operator
             */
            lexer &operator=(lexer &&) = delete;

            /**
             * @brief Advance the lexer and return the next token.
             *
             * This reads from the underlying input adapter as required and
             * updates the lexer's internal token state. The returned token
             * value represents the kind of token available.
             *
             * @return The next token produced by the lexer.
             */
            token next_token();

            /**
             * @brief Return the current token object.
             *
             * The returned token contains the token type and any value
             * information parsed by the lexer (for example string content).
             *
             * @return The current token.
             */
            MYJSON_NODISCARD token get_token();

            /**
             * @brief Return the type of the current token.
             * @return The current token type.
             */
            MYJSON_NODISCARD token_t get_type() const;

            MYJSON_NODISCARD token scan();

            MYJSON_NODISCARD mark position() const;

        private:
            /**
             * @defgroup position
             * @brief position methods.
             * @{
             */

            void advance(size_t amount = 1);

            void reverse(size_t amount = 1);

            /** @} group position */

            /**
             * @defgroup scanner
             * @brief scanner methods.
             * @{
             */

            bool scan_literal();

            bool scan_comment();

            bool scan_string();

            bool scan_number();

            /** @} group scanner */

            int skip_ws();

            /**
             * @brief Read a character (byte) from the input adapter.
             * @return The read character value or EOF-like sentinel.
             */
            MYJSON_NODISCARD int get_char();

            /**
             * @brief Push back the last-read character so it can be read again.
             */
            void unget_char();

            /**
             * @brief Append a character to the current token buffer.
             * @param character The character value to append.
             */
            void add_char(int charater);

        private:
            iadapter *m_adapter{nullptr};
            myjson::encoding m_encoding;
            std::string m_string; //!
            std::string m_input;
            size_t m_input_pos{0};
            int m_putback{-1};
            mark m_position;
            token m_token;
            int m_char;
        };

        /**
         * @class parser
         * @brief Recursive-descent JSON parser over a token stream.
         *
         * The parser consumes tokens from @ref lexer and materializes
         * a @ref myjson::json value.
         */
        class parser
        {
        public:
            /**
             * @brief Construct a parser from a lexer instance.
             * @param lexer Lexer producing JSON tokens.
             */
            explicit parser(class lexer *lexer);

            /**
             * @brief Deleted copy constructor.
             */
            parser(const parser &) = delete;

            /**
             * @brief Deleted move constructor.
             */
            parser(parser &&) = delete;

            /**
             * @brief Deleted copy assignment operator.
             */
            parser &operator=(const parser &) = delete;

            /**
             * @brief Deleted move assignment operator.
             */
            parser &operator=(parser &&) = delete;

            /**
             * @brief Parse one complete JSON value.
             * @return Parsed JSON value.
             */
            MYJSON_NODISCARD myjson::json parse();

        private:
            MYJSON_NODISCARD myjson::json parse_value();
            MYJSON_NODISCARD myjson::json parse_object();
            MYJSON_NODISCARD myjson::json parse_array();
            MYJSON_NODISCARD myjson::json parse_number(const std::string &text);
            MYJSON_NODISCARD std::string parse_string(const std::string &text);
            void advance();

        private:
            class lexer *m_lexer{nullptr};
            token m_current{};
        };

        class deserializer
        {
        public:
            /**
             * @brief Construct a deserializer view over an existing JSON value.
             * @param value JSON value to read from.
             */
            explicit deserializer(const json &value);

            /**
             * @brief Deleted copy constructor
             */
            deserializer(const deserializer &) = delete;

            /**
             * @brief Deleted move constructor
             */
            deserializer(deserializer &&) = delete;

            /**
             * @brief Deleted copy assignment operator
             */
            deserializer &operator=(const deserializer &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            deserializer &operator=(deserializer &&) = delete;

            /**
             * @brief Read a value of type @p T from the wrapped JSON value.
             * @param default_value Value returned if conversion is not possible.
             */
            template <typename T>
            T get(const T &default_value = T{}) const noexcept;

            /**
             * @brief Read a value of type @p T and throw on unsupported conversion.
             */
            template <typename T>
            T get_safe() const;

        private:
            const json &m_value;
        };

        /** @} group input */

        /**
         * @defgroup output
         * @brief
         * @{
         */

        /**
         * @class oadapter
         * @brief Abstract base for output adapters used by the emitter.
         *
         * Implementations provide a concrete destination for emitted bytes
         * (files, memory buffers, ostream, etc.).
         */
        class oadapter
        {
        public:
            /**
             * @brief Default copy assignment operator
             */
            oadapter() = default;

            /**
             * @brief Default copy constructor
             */
            oadapter(const oadapter &) = default;

            /**
             * @brief Default move constructor
             */
            oadapter(oadapter &&) noexcept = default;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * Implementations must copy at most @p size bytes from the provided
             * buffer and advance the stream position accordingly.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            virtual size_t write(const void *data, size_t size) = 0;

            /**
             * @brief Default copy assignment operator
             */
            oadapter &operator=(const oadapter &) = default;

            /**
             * @brief Default move assignment operator
             */
            oadapter &operator=(oadapter &&) noexcept = default;

            /**
             * @brief Virtual destructor.
             */
            virtual ~oadapter() = default;
        };

        /**
         * @class file_oadapter
         * @brief Output adapter that writes to a C `FILE*`.
         */
        class file_oadapter : public oadapter
        {
        public:
            /**
             * @brief Construct the stream from a FILE pointer.
             * @param file File pointer to write to (must be valid for the lifetime).
             * @throws myjson::exception on error.
             */
            explicit file_oadapter(FILE *file);

            /**
             * @brief Deleted copy constructor
             */
            file_oadapter(const file_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            file_oadapter(file_oadapter &&) noexcept = default;

            /**
             * @brief Write raw bytes to the underlying FILE*.
             * @param data Pointer to bytes to write.
             * @param size Number of bytes to write.
             * @return Number of bytes written or `0` on error.
             */
            size_t write(const void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            file_oadapter &operator=(const file_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            file_oadapter &operator=(file_oadapter &&) = delete;

        private:
            /** Member data */
            FILE *m_file;
        };

#ifndef MYJSON_NO_STL
        /**
         * @class stream_oadapter
         * @brief Output adapter that writes to a C++ `std::ostream`.
         */
        class stream_oadapter : public oadapter
        {
        public:
            /**
             * @brief Construct a stream-based output adapter from an std::ostream.
             * @param stream Reference to an opened output stream to write bytes to.
             */
            explicit stream_oadapter(std::ostream &stream);

            /**
             * @brief Deleted copy constructor
             */
            stream_oadapter(const stream_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            stream_oadapter(stream_oadapter &&) noexcept = default;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            size_t write(const void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            stream_oadapter &operator=(const stream_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            stream_oadapter &operator=(stream_oadapter &&) = delete;

        private:
            /** Member data */
            std::ostream *m_stream;
        };

#endif // MYJSON_NO_STL

        /**
         * @class memory_oadapter
         * @brief Output adapter that writes to a `char*`.
         */
        class memory_oadapter : public oadapter
        {
        public:
            /**
             * @brief Construct the stream from a C-String pointer.
             * @param data Pointer to the data to write to.
             * @param size Size of the data, in bytes
             * @throws myjson::exception on error.
             */
            memory_oadapter(void *data, size_t size);

            /**
             * @brief Deleted copy constructor
             */
            memory_oadapter(const memory_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            memory_oadapter(memory_oadapter &&) noexcept = default;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            size_t write(const void *data, size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            memory_oadapter &operator=(const memory_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            memory_oadapter &operator=(memory_oadapter &&) = delete;

        private:
            /** Member data */
            size_t m_pos;
            size_t m_size;
            void *m_data;
        };

        class serializer
        {
        public:
            /**
             * @brief Construct a serializer from an output adapter.
             * @param adapter Adapter receiving serialized bytes.
             */
            explicit serializer(oadapter *adapter);

            /**
             * @brief Deleted copy constructor
             */
            serializer(const serializer &) = delete;

            /**
             * @brief Deleted move constructor
             */
            serializer(serializer &&) = delete;

            /**
             * @brief Deleted copy assignment operator
             */
            serializer &operator=(const serializer &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            serializer &operator=(serializer &&) = delete;

            /**
             * @brief Serialize a JSON value into the bound output adapter.
             * @param value Value to serialize.
             * @param indent Pretty-print indentation. Use a negative value for compact output.
             */
            void serialize(const myjson::json &value, int indent);

        private:
            void write_raw(const char *text, size_t size);
            void write_raw(const std::string &text);
            void write_escaped(const std::string &text);
            void write_indent(int level, int indent);
            void write_value(const myjson::json &value, int indent, int level);

        private:
            oadapter *m_adapter{nullptr};
        };

        /** @} group output */

        //-----------------------------------------------------------------------------
        // [SECTION] Details : Functions
        //-----------------------------------------------------------------------------

        const char *string(mark type);
        const char *string(event type);
        const char *string(token type);

#ifndef MYJSON_NO_STL

        /**
         * @brief Write the token type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] type An token type.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const token_t &type);

        /**
         * @brief Write the error type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] type A error type.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const error_t &type);

        /**
         * @brief Write the event type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] type A event type.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const event_t &type);

        /**
         * @brief Write the value type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] type A value type.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const value_t &type);

        /**
         * @brief Write the break type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] type A break type.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const break_t &type);

        /**
         * @brief Write the token type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] mark A mark object.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const mark &type);

        /**
         * @brief Write the error type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] event An event object.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const event &type);

        /**
         * @brief Write the event type string into stream.
         * @param[in] ostream An output stream object.
         * @param[in] token A event object.
         * @return Reference to the output stream object `ostream`.
         */
        std::ostream &operator<<(std::ostream &ostream, const token &type);

#endif // MYJSON_NO_STL

    }; // namespace detail

    MYJSON_VERSION_NAMESPACE_END

} // namespace myjson

#pragma endregion // Detail

#pragma region Myjson

/**
 * @namespace myjson
 * @brief The API namespace myjson::
 */
namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Enums
    //-----------------------------------------------------------------------------

    /**
     * @defgroup enum Enums
     * @brief Core enum types and flags.
     * @{
     */

    enum class encoding : uint8_t
    {
        unspecified, /** Let the parser choose the encoding. */
        utf8,        /** The UTF-8 encoding. */
        utf16,       /** The UTF-16-LE encoding with native endianness. */
        utf16le,     /** The UTF-16-LE encoding with BOM. */
        utf16be,     /** The UTF-16-BE encoding with BOM. */
        utf32,       /** The UTF-32 encoding with native endianness. */
        utf32le,     /** The UTF-32-LE encoding with BOM. */
        utf32be,     /** The UTF-32-BE encoding with BOM. */
    };

    enum class node_t : uint8_t
    {
        unknown,
    };

    /** @} */

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Structures
    //-----------------------------------------------------------------------------

    /**
     * @defgroup struct Structures
     * @brief Core types and Structures.
     * @{
     */

    /**
     * @class myjson::version
     * @brief version numbering scheme @c https://semver.org/
     * @note Its members can be accessed directly (there are no accessors like
     * `SetMajor()`, `GetMajor()`). Usage example:
     */
    class version
    {
    public:
        /**
         * @brief Default constructor
         *
         * @note Creates a `version(0, 0, 0)`.
         */
        version() = default;

        /**
         * @brief Construct the version.
         *
         * @param major The major version number.
         * @param minor The minor version number.
         * @param patch The patch version number.
         *
         */
        version(int major, int minor, int patch);

    public:
        // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

        int major{}; /** The major version number. */
        int minor{}; /** The minor version number. */
        int patch{}; /** The patch version number. */

        // NOLINTEND(misc-non-private-member-variables-in-classes)
    };

    /**
     * @name Version comparison operators
     * @{
     */
    bool operator<(const version &lhs, const version &rhs) noexcept;
    bool operator>(const version &lhs, const version &rhs) noexcept;
    bool operator==(const version &lhs, const version &rhs) noexcept;
    bool operator!=(const version &lhs, const version &rhs) noexcept;
    bool operator<=(const version &lhs, const version &rhs) noexcept;
    bool operator>=(const version &lhs, const version &rhs) noexcept;
    /** @} */

#ifndef MYJSON_NO_STL

    /**
     * @brief Write the version object string into stream.
     *
     * @param[in] ostream An output stream object.
     * @param[in] version A version object.
     *
     * @return Reference to the output stream object `ostream`.
     */
    std::ostream &operator<<(std::ostream &ostream, const version &version);

#endif // MYJSON_NO_STL

#ifndef MYJSON_NO_EXCEPTIONS

    /**
     * @class myjson::exception
     * @brief A base exception class used in library.
     */
    class exception : public std::exception
    {
    public:
        /**
         * @brief Construct a new exception object without any error messages.
         */
        exception() = default;

        /**
         * @brief Construct a new exception object with an error messages.
         * @param[in] message An error message.
         */
        explicit exception(const char *message) noexcept;

        /**
         * @brief Returns an error message internally held. If nothing, a non-null,
         * empty string will be returned.
         * @return An error message internally held. The message might be empty.
         */
        MYJSON_NODISCARD const char *what() const noexcept override;

    private:
        std::string m_Message; /** An error message holder. */
    };

    class parse_error : public exception
    {
    public:
        /**
         * @brief Construct a new parse_error object.
         *
         * @param message An error message.
         */
        explicit parse_error(const char *message) noexcept;

        /**
         * @brief Construct a new encoding_error object.
         *
         * @param msg An error message.
         * @param mark The error position.
         */
        parse_error(const char *message, detail::mark mark) noexcept;

    private:
        /**
         * @brief Generate an error message from the given parameters.
         *
         * This helper constructs a human-readable error message that
         * includes the supplied @p message and positional information from
         * @p mark (line, column, index). The returned C-string pointer is a
         * pointer into an internal, thread-local buffer owned by the
         * implementation. The pointer is valid until the next call to this
         * function on the same thread. Callers (for example the
         * exception constructors) should immediately copy the returned
         * string if they need to retain it long-term.
         *
         * @param message An error message. May be nullptr.
         * @param mark The error position.
         *
         * @return Pointer to a null-terminated C-string describing the error.
         */
        static const char *generate(const char *message, detail::mark mark) noexcept;
    };

    class encoding_error : public exception
    {
    public:
        /**
         * @brief Construct a new encoding_error object.
         *
         * @param message An error message.
         */
        explicit encoding_error(const char *message) noexcept;

        /**
         * @brief Construct a new encoding_error object.
         *
         * @param encoding The encoding.
         * @param message An error message.
         * @param data The Encoded character.
         * @param size Number of bytes of data.
         */
        encoding_error(encoding encoding, const char *message, void *data, size_t size) noexcept;

    private:
        /**
         * @brief Generate an error message from encoding-related parameters.
         *
         * Builds a human-readable message including the @p message, the
         * detected @p encoding and a short hex representation of the
         * problematic @p data (up to a small limit). The returned pointer
         * points into an internal, thread-local buffer and is valid until
         * the next call to this function on the same thread. Callers must
         * copy the string if they need to keep it beyond the immediate use
         * (the exception constructors copy it into their member storage).
         *
         * @param encoding The detected encoding for the data.
         * @param message An error message. May be nullptr.
         * @param data Pointer to the raw encoded character bytes, or nullptr.
         * @param size Number of bytes available at @p data.
         *
         * @return Pointer to a null-terminated C-string describing the error.
         */
        static const char *generate(encoding encoding, const char *message, void *data, size_t size) noexcept;
    };

#endif // MYJSON_NO_EXCEPTIONS

    /**
     * @enum value_type
     * @brief Defines all possible JSON value types.
     */
    enum class value_type : uint8_t
    {
        null,    ///< null value
        object,  ///< object (map of string to json)
        array,   ///< array (vector of json values)
        string,  ///< string value
        number,  ///< numeric value (floating point)
        integer, ///< integer value
        boolean  ///< boolean value
    };

    /**
     * @class json
     * @brief A JSON value that can hold any JSON type.
     *
     * Supports:
     * - All standard JSON types (null, object, array, string, number, boolean)
     * - Type conversions via get<T>()
     * - Container-like access (operator[], at())
     * - Iteration over objects and arrays
     * - JSON Pointer (RFC 6901)
     * - JSON Patch (RFC 6902)
     * - Encoding conversions (UTF-8, UTF-16, UTF-32)
     */
    class json
    {
        friend class json_patch;
        friend class json_pointer;
        friend class json_merge_patch;

    public:
        // Type aliases for convenience
        using object_t = std::map<std::string, json>;
        using array_t = std::vector<json>;
        using string_t = std::string;
        using number_t = double;
        using integer_t = int64_t;
        using boolean_t = bool;
        using null_t = std::nullptr_t;

        // Json/Object Iterator types
        using iterator = object_t::iterator;
        using const_iterator = object_t::const_iterator;
        using reverse_iterator = object_t::reverse_iterator;
        using const_reverse_iterator = object_t::const_reverse_iterator;

        // Array iterator support
        using array_iterator = array_t::iterator;
        using array_const_iterator = array_t::const_iterator;

    public:
        //========== Constructors ==========
        json() noexcept;
        explicit json(std::nullptr_t) noexcept;
        explicit json(bool value) noexcept;
        explicit json(int value) noexcept;
        explicit json(integer_t value) noexcept;
        explicit json(number_t value) noexcept;
        explicit json(const string_t &value);
        explicit json(const char *value);
        explicit json(const array_t &value);
        explicit json(const object_t &value);

        static json object();
        static json array();

        //========== Destructor and Assignment ==========
        ~json() noexcept;
        json(const json &other);
        json(json &&other) noexcept;
        json &operator=(const json &other);
        json &operator=(json &&other) noexcept;

        /**
         * @brief Assign JSON null.
         */
        json &operator=(std::nullptr_t) noexcept;

        /**
         * @brief Assign a boolean value.
         */
        json &operator=(bool value) noexcept;

        /**
         * @brief Assign a signed integer value.
         */
        json &operator=(int value) noexcept;

        /**
         * @brief Assign a 64-bit integer value.
         */
        json &operator=(integer_t value) noexcept;

        /**
         * @brief Assign a floating-point numeric value.
         */
        json &operator=(number_t value) noexcept;

        /**
         * @brief Assign a UTF-8 string value.
         */
        json &operator=(const string_t &value);

        /**
         * @brief Assign a C-string value (nullptr becomes empty string).
         */
        json &operator=(const char *value);

        /**
         * @brief Assign an array value.
         */
        json &operator=(const array_t &value);

        /**
         * @brief Assign an object value.
         */
        json &operator=(const object_t &value);

        //========== Type Information ==========
        MYJSON_NODISCARD value_type type() const noexcept;
        MYJSON_NODISCARD bool is_null() const noexcept;
        MYJSON_NODISCARD bool is_object() const noexcept;
        MYJSON_NODISCARD bool is_array() const noexcept;
        MYJSON_NODISCARD bool is_string() const noexcept;
        MYJSON_NODISCARD bool is_number() const noexcept;
        MYJSON_NODISCARD bool is_integer() const noexcept;
        MYJSON_NODISCARD bool is_boolean() const noexcept;
        MYJSON_NODISCARD bool is_primitive() const noexcept;
        MYJSON_NODISCARD bool is_structured() const noexcept;

        //========== Type Conversions ==========
        template <typename T>
        T get(const T &default_value) const noexcept;
        template <typename T>
        T get_safe() const;

        MYJSON_NODISCARD bool as_bool() const noexcept;
        MYJSON_NODISCARD integer_t as_integer() const noexcept;
        MYJSON_NODISCARD number_t as_number() const noexcept;
        MYJSON_NODISCARD string_t as_string() const noexcept;

        //========== Container Access (Objects) ==========
        json &at(const std::string &key);
        MYJSON_NODISCARD const json &at(const std::string &key) const;
        json &operator[](const std::string &key);
        json operator[](const std::string &key) const;
        json &operator[](const char *key);
        json operator[](const char *key) const;
        MYJSON_NODISCARD bool contains(const std::string &key) const noexcept;
        MYJSON_NODISCARD size_t count(const std::string &key) const noexcept;
        size_t erase(const std::string &key) noexcept;

        //========== Container Access (Arrays) ==========
        json &at(size_t index);
        MYJSON_NODISCARD const json &at(size_t index) const;
        json &operator[](size_t index);
        const json &operator[](size_t index) const;
        json &front();
        MYJSON_NODISCARD const json &front() const;
        json &back();
        MYJSON_NODISCARD const json &back() const;
        void push_back(const json &value);
        void push_back(json &&value);

        /**
         * @brief Append a boolean element to the array.
         */
        void push_back(bool value);

        void push_front(const json &value);
        array_iterator insert(const array_const_iterator &pos, const json &value);
        array_iterator insert(const array_const_iterator &pos, json &&value);
        array_iterator erase(array_const_iterator pos);
        array_iterator erase(array_const_iterator first, array_const_iterator last);

        //========== Size and Capacity ==========
        MYJSON_NODISCARD size_t size() const noexcept;
        MYJSON_NODISCARD bool empty() const noexcept;
        void clear() noexcept;

        //========== Iteration ==========
        iterator begin();
        MYJSON_NODISCARD const_iterator begin() const;
        MYJSON_NODISCARD const_iterator cbegin() const;
        iterator end();
        MYJSON_NODISCARD const_iterator end() const;
        MYJSON_NODISCARD const_iterator cend() const;
        reverse_iterator rbegin();
        MYJSON_NODISCARD const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        MYJSON_NODISCARD const_reverse_iterator rend() const;
        array_iterator array_begin();
        MYJSON_NODISCARD array_const_iterator array_begin() const;
        array_iterator array_end();
        MYJSON_NODISCARD array_const_iterator array_end() const;

        //========== Comparison ==========
        bool operator==(const json &other) const noexcept;
        bool operator!=(const json &other) const noexcept;
        bool operator<(const json &other) const noexcept;
        bool operator<=(const json &other) const noexcept;
        bool operator>(const json &other) const noexcept;
        bool operator>=(const json &other) const noexcept;

        //========== Serialization ==========
        MYJSON_NODISCARD string_t dump(int indent = -1) const;
        MYJSON_NODISCARD string_t dump_pretty() const;
        MYJSON_NODISCARD string_t dump_compact() const;

        //========== Parsing ==========
        static json parse(const string_t &str);
        static json parse(const char *str);
        static json parse(FILE *file);
#ifndef MYJSON_NO_STL
        static json parse(std::istream &stream);
#endif // MYJSON_NO_STL
        static json parse(detail::iadapter &adapter);
        static std::optional<json> try_parse(const string_t &str) noexcept;

        //========== JSON Pointer (RFC 6901) ==========
        json &at_pointer(const std::string &pointer);
        MYJSON_NODISCARD const json &at_pointer(const std::string &pointer) const;
        std::optional<json *> find_pointer(const std::string &pointer) noexcept;
        MYJSON_NODISCARD std::optional<const json *> find_pointer(const std::string &pointer) const noexcept;
        MYJSON_NODISCARD std::string pointer_to(const json &value) const;

        //========== JSON Patch (RFC 6902) ==========
        MYJSON_NODISCARD json apply_patch(const json &patch) const;
        static json generate_patch(const json &source, const json &target);

        //========== JSON Merge Patch (RFC 7386) ==========
        MYJSON_NODISCARD json apply_merge_patch(const json &patch) const;

        //========== Utility ==========
        MYJSON_NODISCARD json clone() const;
        void merge(const json &other);
        MYJSON_NODISCARD std::vector<std::string> keys() const;
        MYJSON_NODISCARD std::vector<json> values() const;

        template <typename Visitor>
        auto apply_visitor(Visitor &&vis);

    private:
        void ensure_object();
        void ensure_array();
        MYJSON_NODISCARD const object_t &get_object() const;
        MYJSON_NODISCARD const array_t &get_array() const;
        object_t &get_object();
        array_t &get_array();

    private:
        std::variant<
            null_t,
            boolean_t,
            integer_t,
            number_t,
            string_t,
            array_t,
            object_t>
            m_value;
    };

    /**
     * @class json_pointer
     * @brief Utility class for working with JSON Pointers (RFC 6901).
     *
     * Example: "/users/0/email" points to the email field of the first user.
     */
    class json_pointer
    {
        friend class json;

    public:
        explicit json_pointer(const std::string &pointer_str);

        MYJSON_NODISCARD std::string to_string() const;
        MYJSON_NODISCARD const std::vector<std::string> &tokens() const;
        MYJSON_NODISCARD size_t depth() const;
        MYJSON_NODISCARD bool is_root() const;
        MYJSON_NODISCARD json_pointer parent() const;
        MYJSON_NODISCARD std::string back() const;
        MYJSON_NODISCARD json_pointer push(const std::string &token) const;
        json &ref(json &document);
        MYJSON_NODISCARD const json &ref(const json &document) const;
        std::optional<json *> try_ref(json &document) noexcept;
        MYJSON_NODISCARD std::optional<const json *> try_ref(const json &document) const noexcept;

        json_pointer &operator/=(const json_pointer &ptr);
        json_pointer &operator/=(std::string token);
        json_pointer &operator/=(std::size_t index);

    private:
        static std::string unescape(const std::string &token);
        static std::string escape(const std::string &token);
        void parse(const std::string &pointer_str);

    private:
        std::vector<std::string> m_tokens;
        std::string m_original;
    };

    /**
     * @class json_patch
     * @brief Utility class for applying JSON Patch operations (RFC 6902).
     */
    class json_patch
    {
        /**
         * @enum operation_t
         * @brief Types of JSON Patch operations (RFC 6902).
         */
        enum class operation_t : uint8_t
        {
            add,     ///< Add a value at path
            remove,  ///< Remove the value at path
            replace, ///< Replace the value at path
            move,    ///< Move value from one path to another
            copy,    ///< Copy value from one path to another
            test,    ///< Test that a value at path equals specified value
        };

    public:
        explicit json_patch(const json &patch_json);

        MYJSON_NODISCARD json apply(const json &document) const;
        void apply_inplace(json &document) const;

        MYJSON_NODISCARD const json &operations() const;
        MYJSON_NODISCARD size_t size() const;
        MYJSON_NODISCARD bool empty() const;

        static json add_operation(const std::string &path, const json &value);
        static json remove_operation(const std::string &path);
        static json replace_operation(const std::string &path, const json &value);
        static json move_operation(const std::string &from_path, const std::string &to_path);
        static json copy_operation(const std::string &from_path, const std::string &to_path);
        static json test_operation(const std::string &path, const json &value);

    private:
        void apply_operation(const json &operation, json &document) const;
        static operation_t get_operation_type(const json &operation);

    private:
        json m_operations;
    };

    /**
     * @class json_merge_patch
     * @brief Utility class for JSON Merge Patch (RFC 7386).
     */
    class json_merge_patch
    {
    public:
        explicit json_merge_patch(const json &patch_json);

        MYJSON_NODISCARD json apply(const json &document) const;
        void apply_inplace(json &document) const;

        static json generate(const json &source, const json &target);

    private:
        static json apply_recursive(const json &target, const json &patch);

    private:
        json m_patch;
    };

    namespace detail
    {
        template <typename T>
        T deserializer::get(const T &default_value) const noexcept
        {
            return m_value.template get<T>(default_value);
        }

        template <typename T>
        T deserializer::get_safe() const
        {
            return m_value.template get_safe<T>();
        }
    } // namespace detail

    /** @} */

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Functions
    //-----------------------------------------------------------------------------

    /**
     * @brief Generate minimal JSON Patch between two documents.
     */
    json diff(const json &source, const json &target);

    /**
     * @brief Convenience function to create object JSON.
     */
#ifndef __INTELLISENSE__
    inline json object() { return json::object(); }

    /**
     * @brief Convenience function to create array JSON.
     */
    inline json array() { return json::array(); }
#endif // __INTELLISENSE__

    const char *string(encoding type);

    const char *string(node_t type);

#ifndef MYJSON_NO_STL

    /**
     * @brief Write the encoding type string into stream.
     * @param[in] ostream An output stream object.
     * @param[in] type An encoding type.
     * @return Reference to the output stream object `ostream`.
     */
    std::ostream &operator<<(std::ostream &ostream, const encoding &type);

    /**
     * @brief Write the node type string into stream.
     * @param[in] ostream An output stream object.
     * @param[in] type A node type.
     * @return Reference to the output stream object `ostream`.
     */
    std::ostream &operator<<(std::ostream &ostream, const node_t &type);

    /**
     * @brief A wrapper for the serialization feature.
     * @param[in] stream An output stream object.
     * @param[in] node A json object.
     * @return Reference to the output stream object `stream`.
     */
    std::ostream &operator<<(std::ostream &stream, const json &node);

    /**
     * @brief A wrapper for the deserialization feature.
     * @param[in] stream An input stream object.
     * @param[in] node A json object.
     * @return Reference to the input stream object `stream`.
     */
    std::istream &operator>>(std::istream &stream, json &node);

#endif // MYJSON_NO_STL

    MYJSON_VERSION_NAMESPACE_END

} // namespace myjson

#pragma endregion // Myjson

#pragma region Literal

/**
 * @namespace myjson
 * @brief The API namespace myjson::
 */
namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    /**
     * @namespace literals
     * @brief The literals namespace myjson::literals::
     */
    namespace literals
    {

        inline namespace json_literals
        {
            //-----------------------------------------------------------------------------
            // [SECTION] Literals : Functions
            //-----------------------------------------------------------------------------

            // Whitespace before the literal operator is deprecated in C++23 or later but required in C++11.
            MYJSON_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wdeprecated")

#ifndef __INTELLISENSE__

            /**
             * @brief Deserializes a `char` array into a `json` object.
             *
             * @param string An input `char` array.
             * @param size The size of `string`.
             *
             * @return The resulting `json` object deserialized from `string`.
             */
            MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char *string, size_t size);

#if MYJSON_HAS_CHAR8_T

            /**
             * @brief Deserializes a `char8_t` array into a `json` object.
             *
             * @param string An input `char8_t` array.
             * @param size The size of `string`.
             *
             * @return The resulting `json` object deserialized from `string`.
             */
            MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char8_t *string, size_t size);

#endif // MYJSON_HAS_CHAR8_T

            /**
             * @brief Deserializes a `char16_t` array into a `json` object.
             *
             * @param string An input `char16_t` array.
             * @param size The size of `string`.
             *
             * @return The resulting `json` object deserialized from `string`.
             */
            MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char16_t *string, size_t size);

            /**
             * @brief Deserializes a `char32_t` array into a `json` object.
             *
             * @param string An input `char32_t` array.
             * @param size The size of `string`.
             *
             * @return The resulting `json` object deserialized from `string`.
             */
            MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char32_t *string, size_t size);

            /**
             * @brief Identify a specific value (`char`) with in a `json` object.
             *
             * @param string An input `char` array.
             * @param size The size of `string`.
             *
             * @return The `json_pointer` object identified from `string`.
             */
            MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char *string, size_t size);

#if MYJSON_HAS_CHAR8_T

            /**
             * @brief Identify a specific value (`char8_t`) with in a `json` object.
             *
             * @param string An input `char8_t` array.
             * @param size The size of `string`.
             *
             * @return The `json_pointer` object identified from `string`.
             */
            MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char8_t *string, size_t size);

#endif // MYJSON_HAS_CHAR8_T

            /**
             * @brief Identify a specific value (`char16_t`) with in a `json` object.
             *
             * @param string An input `char16_t` array.
             * @param size The size of `string`.
             *
             * @return The `json_pointer` object identified from `string`.
             */
            MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char16_t *string, size_t size);

            /**
             * @brief Identify a specific value (`char32_t`) with in a `json` object.
             *
             * @param string An input `char32_t` array.
             * @param size The size of `string`.
             *
             * @return The `json_pointer` object identified from `string`.
             */
            MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char32_t *string, size_t size);

#endif // __INTELLISENSE__

            MYJSON_CLANG_SUPPRESS_WARNING_POP

        } // namespace json_literals
    } // namespace literals

    MYJSON_VERSION_NAMESPACE_END

}; // namespace myjson

#pragma endregion // Literal

//-----------------------------------------------------------------------------

#endif // DJOEZEKE_MYJSON_HPP

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */