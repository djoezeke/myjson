/**
 * @file myjson.h
 * @brief JSON parser library header for C/C++.
 * This is a  C/C++ JSON Parser Library Header @c myjson.c.
 * @details This header provides all public API, types, macros, and
 * configuration for JSON and supports both C and C++ usage.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @date Thur 02 12:43:15 Oct GMT 2025
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myjson
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
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
 * Usage:
 * @code
 *  #include <myjson.h>
 * @endcode
 *
 * Index of this file:
 *  [SECTION] Header mess
 *  [SECTION] Configurable macros
 *  [SECTION] Function Macros
 *  [SECTION] Imports/Exports
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/myjson
 * - Releases & changelog ....... https://github.com/djoezeke/myjson/releases
 * - Issues & support ........... https://github.com/djoezeke/myjson/issues
 *
 */

#ifndef DJOEZEKE_MYJSON
#define DJOEZEKE_MYJSON

#ifndef MYJSON_SKIP_VERSION_CHECK
#if defined(MYJSON_VERSION_MAJOR) && defined(MYJSON_VERSION_MINOR) && defined(MYJSON_VERSION_PATCH)
#if MYJSON_VERSION_MAJOR != 0 || MYJSON_VERSION_MINOR != 1 || MYJSON_VERSION_PATCH != 0
#warning "Already included a different version of the library!"
#endif
#endif
#endif  // MYJSON_SKIP_VERSION_CHECK

/**
 * @defgroup version Version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def MYJSON_VERSION_MAJOR
 * @brief Major version number of the library.
 */
#define MYJSON_VERSION_MAJOR 0

/**
 * @def MYJSON_VERSION_MINOR
 * @brief Minor version number of the library.
 */
#define MYJSON_VERSION_MINOR 1

/**
 * @def MYJSON_VERSION_PATCH
 * @brief Patch version number of the library.
 */
#define MYJSON_VERSION_PATCH 0

/**
 * @def MYJSON_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */
#define MYJSON_VERSION "0.1.0"

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus

/** C++ Exclusive headers. */
#include <exception>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#endif  //__cplusplus

#ifdef MYJSON_DEBUG
#endif  // MYJSON_DEBUG

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

/**
 * @def MYJSON_DISABLE_READER
 * @brief Exclude Reading/Deserialization JSON methods.
 * Define as 1 to diable JSON reader if parsing is not required.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 60%.
 */
#ifndef MYJSON_DISABLE_READER
#endif

/**
 * @def MYJSON_DISABLE_WRITER
 * @brief Exclude Writing/Serialization JSON methods.
 * Define as 1 to disable JSON writer if JSON serialization is not required.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 30%.
 */
#ifndef MYJSON_DISABLE_WRITER
#endif

/**
 * @def MYJSON_DISABLE_ENCODING
 * @brief Exclude Encoding/UTF-8 JSON methods.
 * Define as 1 to disable UTF-8 validation at compile time.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 7%.
 */
#ifndef MYJSON_DISABLE_ENCODING
#endif

/**
 * @def MYJSON_ASSERT
 * @brief Apply the default assert.
 */
#ifndef MYJSON_ASSERT
#ifndef NDEBUG
#include <assert.h>
#define MYJSON_ASSERT(x) assert(x)
#else
#define MYJSON_ASSERT(x)
#endif
#endif

#define MYJSON_SUCCESS 1
#define MYJSON_FAILURE 0

//-----------------------------------------------------------------------------
// [SECTION] Function Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Platform
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
 * A preprocessor macro that is only defined if compiling for MacOS.
 */
#define MYJSON_PLATFORM_IS_APPLE 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define MYJSON_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
/**
 * A preprocessor macro that is only defined if compiling for Linux.
 */
#define MYJSON_PLATFORM_IS_LINUX 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define MYJSON_PLATFORM_NAME_IS "Linux"
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__)
/**
 * A preprocessor macro that is only defined if compiling for Windows.
 */
#define MYJSON_PLATFORM_IS_WINDOWS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define MYJSON_PLATFORM_NAME_IS "Windows"
#else
/**
 * A preprocessor macro that is only defined if compiling for others.
 */
#define MYJSON_PLATFORM_IS_OTHERS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define MYJSON_PLATFORM_NAME_IS "Others"
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler
//-----------------------------------------------------------------------------

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

/// Compiler is apple
#if !defined(__clang__)
#define MYJSON_COMPILER_IS_APPLE 0
#elif !defined(__apple_build_version__)
#define MYJSON_COMPILER_IS_APPLE 0
#else
#define MYJSON_COMPILER_IS_APPLE 1
#define MYJSON_COMPILER_VERSION_MAJOR __clang_major__
#define MYJSON_COMPILER_VERSION_MINOR __clang_minor__
#define MYJSON_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is clang
#if !defined(__clang__)
#define MYJSON_COMPILER_IS_CLANG 0
#elif MYJSON_COMPILER_IS(APPLE)
#define MYJSON_COMPILER_IS_CLANG 0
#else
#define MYJSON_COMPILER_IS_CLANG 1
#define MYJSON_COMPILER_VERSION_MAJOR __clang_major__
#define MYJSON_COMPILER_VERSION_MINOR __clang_minor__
#define MYJSON_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is intel
#if !defined(__INTEL_COMPILER)
#define MYJSON_COMPILER_IS_INTEL 0
#elif !defined(__INTEL_COMPILER_UPDATE)
#define MYJSON_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define MYJSON_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define MYJSON_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define MYJSON_COMPILER_VERSION_PATCH (__INTEL_COMPILER % 10)
#else
#define MYJSON_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define MYJSON_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define MYJSON_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define MYJSON_COMPILER_VERSION_PATCH __INTEL_COMPILER_UPDATE
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
#define MYJSON_COMPILER_IS_MSVC 0
#elif MYJSON_COMPILER_IS(CLANG)
#define MYJSON_COMPILER_IS_MSVC 0
#elif MYJSON_COMPILER_IS(INTEL)
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

/// Compiler is gcc
#if !defined(__GNUC__)
#define MYJSON_COMPILER_IS_GCC 0
#elif MYJSON_COMPILER_IS(APPLE)
#define MYJSON_COMPILER_IS_GCC 0
#elif MYJSON_COMPILER_IS(CLANG)
#define MYJSON_COMPILER_IS_GCC 0
#elif MYJSON_COMPILER_IS(INTEL)
#define MYJSON_COMPILER_IS_GCC 0
#else
#define MYJSON_COMPILER_IS_GCC 1
#define MYJSON_COMPILER_VERSION_MAJOR __GNUC__
#define MYJSON_COMPILER_VERSION_MINOR __GNUC_MINOR__
#define MYJSON_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

// Compiler Checks

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
#define MYJSON_COMPILER_SINCE(name, x, y, z)     \
    (MYJSON_COMPILER_IS(name) &&                 \
     ((MYJSON_COMPILER_VERSION_MAJOR > (x)) ||   \
      ((MYJSON_COMPILER_VERSION_MAJOR == (x)) && \
       ((MYJSON_COMPILER_VERSION_MINOR > (y)) || \
        ((MYJSON_COMPILER_VERSION_MINOR == (y)) && (MYJSON_COMPILER_VERSION_PATCH >= (z)))))))

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
#define MYJSON_COMPILER_BEFORE(name, x, y, z)    \
    (MYJSON_COMPILER_IS(name) &&                 \
     ((MYJSON_COMPILER_VERSION_MAJOR < (x)) ||   \
      ((MYJSON_COMPILER_VERSION_MAJOR == (x)) && \
       ((MYJSON_COMPILER_VERSION_MINOR < (y)) || \
        ((MYJSON_COMPILER_VERSION_MINOR == (y)) && (MYJSON_COMPILER_VERSION_PATCH < (z)))))))

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if MYJSON_COMPILER_IS(CLANG)
#define MYJSON_PRAGMA_TO_STR(x) _Pragma(#x)
#define MYJSON_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#define MYJSON_CLANG_SUPPRESS_WARNING(w) MYJSON_PRAGMA_TO_STR(clang diagnostic ignored w)
#define MYJSON_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#define MYJSON_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) MYJSON_CLANG_SUPPRESS_WARNING_PUSH MYJSON_CLANG_SUPPRESS_WARNING(w)
#else  // MYJSON_CLANG
#define MYJSON_CLANG_SUPPRESS_WARNING_PUSH
#define MYJSON_CLANG_SUPPRESS_WARNING(w)
#define MYJSON_CLANG_SUPPRESS_WARNING_POP
#define MYJSON_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYJSON_CLANG

#if MYJSON_COMPILER_IS(GCC)
#define MYJSON_PRAGMA_TO_STR(x) _Pragma(#x)
#define MYJSON_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#define MYJSON_GCC_SUPPRESS_WARNING(w) MYJSON_PRAGMA_TO_STR(GCC diagnostic ignored w)
#define MYJSON_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#define MYJSON_GCC_SUPPRESS_WARNING_WITH_PUSH(w) MYJSON_GCC_SUPPRESS_WARNING_PUSH MYJSON_GCC_SUPPRESS_WARNING(w)
#else  // MYJSON_GCC
#define MYJSON_GCC_SUPPRESS_WARNING_PUSH
#define MYJSON_GCC_SUPPRESS_WARNING(w)
#define MYJSON_GCC_SUPPRESS_WARNING_POP
#define MYJSON_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYJSON_GCC

#if MYJSON_COMPILER_IS(MSVC)
#define MYJSON_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#define MYJSON_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#define MYJSON_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#define MYJSON_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) MYJSON_MSVC_SUPPRESS_WARNING_PUSH MYJSON_MSVC_SUPPRESS_WARNING(w)
#else  // MYJSON_MSVC
#define MYJSON_MSVC_SUPPRESS_WARNING_PUSH
#define MYJSON_MSVC_SUPPRESS_WARNING(w)
#define MYJSON_MSVC_SUPPRESS_WARNING_POP
#define MYJSON_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYJSON_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Checks
//-----------------------------------------------------------------------------

/**
 * @defgroup check Compiler Checks
 * @{
 */

/** C version (STDC) */
#if defined(__STDC__) && (__STDC__ >= 1) && defined(__STDC_VERSION__)
#define MYJSON_STDC_VERSION __STDC_VERSION__
#else
#define MYJSON_STDC_VERSION 0
#endif

/** C++ version */
#if defined(__cplusplus)
#define MYJSON_CPP_VERSION __cplusplus
#else
#define MYJSON_CPP_VERSION 0
#endif

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

/** include check */
#ifndef MYJSON_HAS_INCLUDE
#ifdef __has_include
#define MYJSON_HAS_INCLUDE(x) __has_include(x)
#else
#define MYJSON_HAS_INCLUDE(x) 0
#endif
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Attributes
//-----------------------------------------------------------------------------

/**
 * @defgroup attribute Compiler Attributes
 * @{
 */

/** inline for compiler */
#ifndef MYJSON_INLINE
#if MYJSON_COMPILER_SINCE(MSVC, 12, 0, 0)
#define MYJSON_INLINE __forceinline
#elif MYJSON_COMPILER_IS(INTEL)
#define MYJSON_INLINE __inline
#elif MYJSON_HAS_ATTRIBUTE(always_inline) || MYJSON_COMPILER_SINCE(GCC, 4, 0, 0)
#define MYJSON_INLINE __inline__ __attribute__((always_inline))
#elif MYJSON_COMPILER_IS(CLANG) || MYJSON_COMPILER_IS(GCC)
#define MYJSON_INLINE __inline__
#elif defined(__cplusplus) || MYJSON_STDC_VERSION >= 199901L
#define MYJSON_INLINE inline
#else
#define MYJSON_INLINE
#endif
#endif

/** noinline for compiler */
#ifndef MYJSON_NOINLINE
#if MYJSON_COMPILER_SINCE(MSVC, 14, 0, 0)
#define MYJSON_NOINLINE __declspec(noinline)
#elif MYJSON_HAS_ATTRIBUTE(noinline) || MYJSON_GCC_VER >= 4
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

/** likely for compiler */
#ifndef MYJSON_LIKELY
#if MYJSON_HAS_BUILTIN(__builtin_expect) || (MYJSON_COMPILER_SINCE(GCC, 4, 0, 0) && MYJSON_COMPILER_VERSION_MAJOR != 5)
#define MYJSON_LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#define MYJSON_LIKELY(expr) (expr)
#endif
#endif

/** unlikely for compiler */
#ifndef MYJSON_UNLIKELY
#if MYJSON_HAS_BUILTIN(__builtin_expect) || (MYJSON_COMPILER_SINCE(GCC, 4, 0, 0) && MYJSON_COMPILER_VERSION_MAJOR != 5)
#define MYJSON_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#define MYJSON_UNLIKELY(expr) (expr)
#endif
#endif

/** compile-time constant check for compiler */
#ifndef MYJSON_CONSTANT_P
#if MYJSON_HAS_BUILTIN(__builtin_constant_p) || (MYJSON_COMPILER_SINCE(GCC, 3, 0, 0))
#define MYJSON_HAS_CONSTANT_P 1
#define MYJSON_CONSTANT_P(value) __builtin_constant_p(value)
#else
#define MYJSON_HAS_CONSTANT_P 0
#define MYJSON_CONSTANT_P(value) 0
#endif
#endif

/** deprecate warning */
#ifndef MYJSON_DEPRECATED
#if MYJSON_COMPILER_SINCE(MSVC, 14, 0, 0)
#define MYJSON_DEPRECATED(msg) __declspec(deprecated(msg))
#elif MYJSON_HAS_FEATURE(attribute_deprecated_with_message) || \
    (MYJSON_COMPILER_SINCE(GCC, 4, 0, 0) ||                    \
     (MYJSON_COMPILER_VERSION_MAJOR == 5 && MYJSON_COMPILER_VERSION_MINOR >= 5))
#define MYJSON_DEPRECATED(msg) __attribute__((deprecated(msg)))
#if MYJSON_COMPILER_SINCE(MSVC, 3, 0, 0)
#define MYJSON_DEPRECATED(msg) __attribute__((deprecated))
#else
#define MYJSON_DEPRECATED(msg)
#endif
#endif
#endif

/** char bit check */
#if defined(CHAR_BIT)
#if CHAR_BIT != 8
#error non 8-bit char is not supported
#endif
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
#define MYJSON_API_EXPORT __declspec(dllexport)
#define MYJSON_API_IMPORT __declspec(dllimport)
#define MYJSON_NO_EXPORT
#else  // _WIN32
#define MYJSON_API_EXPORT __attribute__((visibility("default")))
#define MYJSON_API_IMPORT __attribute__((visibility("default")))
#define MYJSON_NO_EXPORT __attribute__((visibility("hidden")))
#endif  // _WIN32

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

/** inline function export */
#ifndef MYJSON_API_INLINE
#define MYJSON_API_INLINE static MYJSON_INLINE
#endif

/** char bit check */
#if defined(CHAR_BIT)
#if CHAR_BIT != 8
#error non 8-bit char is not supported
#endif
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for JSON.
 * @{
 */

/** The character type (UTF-8 octet). */
typedef unsigned char JsonChar_t;

/**
 * @enum JsonErrorType
 * @brief Enumerates error types for JSON.
 * @details Used to classify errors encountered.
 */
typedef enum JsonErrorType {
    /**
     * @name Json error types
     * @{
     */

    JSON_UNKNOWN = -1,  /**< An unknown error type. */
    JSON_NO_ERROR,      /**< No error is produced. */
    JSON_MEMORY_ERROR,  /**  */
    JSON_READER_ERROR,  /**  */
    JSON_SCANNER_ERROR, /**  */
    JSON_PARSER_ERROR,  /**  */
    JSON_WRITER_ERROR,  /**  */
    JSON_EMITTER_ERROR, /**  */
    JSON_ENCODING_ERROR,

    /** @} */

} JsonErrorType;

/**
 * @name JsonError_t data type
 * @{
 */

/**
 * @struct JsonError_t
 * @brief Represents an error encountered.
 * @details Contains error type and message for diagnostics.
 */
typedef struct JsonError_t {
    JsonErrorType type;  /**< Type of error. */
    const char *message; /**< Error message string. */
} JsonError_t;

/** @} */

/** @} */

/** The pointer position. */
typedef struct JsonPosition {
    size_t column; /**< The position column. */
    size_t index;  /**< The position index. */
    size_t line;   /**< The position line. */
} JsonPosition;

/**
 * @enum JsonValueType
 * @brief Enumerates types for JSON value.
 */
typedef enum JsonValueType {

    JSON_NULL,     /**< Null value */
    JSON_ARRAY,    /**< Array (ordered collection of values)   */
    JSON_DOUBLE,   /**< Number value (floating-point) */
    JSON_BINARY,   /**< Binary array (ordered collection of bytes) */
    JSON_OBJECT,   /**< Object (unordered set of name/value pairs */
    JSON_STRING,   /**< String value  */
    JSON_INTEGER,  /**< Number value (signed integer) */
    JSON_BOOLOEAN, /**< Boolean value */

} JsonValueType;

/** @} */

/**
 * @enum JsonEventType
 * @brief Enumerates types for JSON event.
 */
typedef enum JsonEventType {

    JSON_NO_EVENT,             /** An empty event. */
    JSON_STREAM_START_EVENT,   /** A STREAM-START event. */
    JSON_STREAM_END_EVENT,     /** A STREAM-END event. */
    JSON_DOCUMENT_START_EVENT, /** A DOCUMENT-START event. */
    JSON_DOCUMENT_END_EVENT,   /** A DOCUMENT-END event. */
    JSON_SCALAR_EVENT,         /** A SCALAR event. */
    JSON_ARRAY_START_EVENT,    /** A ARRAY-START event. */
    JSON_ARRAY_END_EVENT,      /** A ARRAY-END event. */
    JSON_OBJECT_START_EVENT,   /** A OBJECT-START event. */
    JSON_OBJECT_END_EVENT      /** A OBJECT-END event. */

} JsonEventType;

/** @} */

/**< The event structure. */
typedef struct JsonEvent {
    JsonEventType type; /**< The event type. */

    /** The event data. */
    union {
        /** The stream parameters (for @c YAML_STREAM_START_EVENT). */
        struct {
            /** The document encoding. */
            JsonEncoding encoding;
        } stream_start;

    } data;

    JsonPosition start_pos; /** The beginning of the event. */
    JsonPosition end_pos;   /** The end of the event. */

} JsonEvent;

typedef struct JsonDocument {
} JsonDocument;

typedef struct JsonNode {
} JsonNode;

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

/**
 * @brief Definition of Unicode encoding types
 */
typedef enum JsonEncoding {
    JSON_ANY_ENCODING,     /** Let the parser choose the encoding. */
    JSON_UTF8_ENCODING,    /** The default UTF-8 encoding. */
    JSON_UTF16LE_ENCODING, /** The UTF-16-LE encoding with BOM. */
    JSON_UTF16BE_ENCODING, /** The UTF-16-BE encoding with BOM. */
    JSON_UTF32LE_ENCODING, /** The UTF-32-LE encoding with BOM. */
    JSON_UTF32BE_ENCODING, /** The UTF-32-BE encoding with BOM. */
} JsonEncoding;

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

typedef int JsonReadHandler(void *data, unsigned char *buffer, size_t size, size_t *size_read);

/**
 * @enum JsonParseEvent
 * @brief Enumerates types for JSON parse event.
 */
typedef enum JsonParseEvent {

    JSON_PARSE_SCALAR_EVENT,       /** A SCALAR event. */
    JSON_PARSE_ARRAY_START_EVENT,  /** A ARRAY-START event. */
    JSON_PARSE_ARRAY_END_EVENT,    /** A ARRAY-END event. */
    JSON_PARSE_OBJECT_START_EVENT, /** A OBJECT-START event. */
    JSON_PARSE_OBJECT_END_EVENT    /** A OBJECT-END event. */

} JsonParseEvent;

/** @} */

typedef enum JsonTokenType {

    JSON_EOF_TOKEN,             /**< indicating the end of the input buffer> */
    JSON_TRUE_TOKEN,            /**< the `true` literal. */
    JSON_NULL_TOKEN,            /**< the `null` literal. */
    JSON_FLOAT_TOKEN,           /**< a floating point number actual value. */
    JSON_FALSE_TOKEN,           /**< the `false` literal. */
    JSON_STRING_TOKEN,          /**< a string value. */
    JSON_INTEGER_TOKEN,         /**< a integer value. */
    JSON_ARRAY_END_TOKEN,       /**< the character for array end `]`. */
    JSON_OBJECT_END_TOKEN,      /**< the character for object end `}`. */
    JSON_ARRAY_BEGIN_TOKEN,     /**< the character for array begin `[`. */
    JSON_OBJECT_BEGIN_TOKEN,    /**< the character for object begin `{`. */
    JSON_NAME_SEPERATOR_TOKEN,  /**< the name separator `:` . */
    JSON_VALUE_SEPERATOR_TOKEN, /**< the value separator `,` . */

} JsonTokenType;

/** The token structure. */
typedef struct JsonToken {
    JsonTokenType type; /**< The token type. */

    /** The token data. */
    struct {
        JsonChar_t *value; /**< The value. */
        size_t length;     /**< The length of the value. */
    } data;

    JsonPosition start_pos; /**< The beginning of the token. */
    JsonPosition end_pos;   /**< The end of the token. */

} JsonToken;

/**
 * The parser structure.
 */
typedef struct JsonParser {
    /**
     * @name Error handling
     * @{
     */

    JsonPosition error_pos; /**< The problem position. */
    JsonError_t error;      /**< Error type. */

    /**
     * @}
     */

    /**
     * @name Reader stuff
     * @{
     */

    JsonReadHandler *read_handler; /** Read handler. */
    void *read_handler_data;       /** A pointer for passing to the read handler. */

    /** Standard (string or file) input data. */
    union {
        /** String input data. */
        struct {
            const unsigned char *current; /** The string current position. */
            const unsigned char *start;   /** The string start pointer. */
            const unsigned char *end;     /** The string end pointer. */

        } string;

        FILE *file; /** File input data. */

    } input;

    int eof; /** EOF flag */

    /** The working buffer. */
    struct {
        JsonChar_t *pointer; /** The current position of the buffer. */
        JsonChar_t *start;   /** The beginning of the buffer. */
        JsonChar_t *last;    /** The last filled position of the buffer. */
        JsonChar_t *end;     /** The end of the buffer. */

    } buffer;

    size_t unread; /**< The number of unread characters in the buffer. */

    /** The raw buffer. */
    struct {
        unsigned char *pointer; /** The current position of the buffer. */
        unsigned char *start;   /** The beginning of the buffer. */
        unsigned char *last;    /** The last filled position of the buffer. */
        unsigned char *end;     /** The end of the buffer. */

    } raw_buffer;

    JsonEncoding encoding; /**< The input encoding. */
    JsonPosition position; /**< The mark of the current position. */
    size_t offset;         /**< The offset of the current position (in bytes). */

    /**
     * @}
     */

    /**
     * @name Scanner stuff
     * @{
     */

    int stream_start_produced; /**< Have we started to scan the input stream? */
    int stream_end_produced;   /**< Have we reached the end of the input stream? */

    /** The tokens queue. */
    struct {
        JsonToken *start; /**< The beginning of the tokens queue. */
        JsonToken *head;  /**< The head of the tokens queue. */
        JsonToken *tail;  /**< The tail of the tokens queue. */
        JsonToken *end;   /**< The end of the tokens queue. */

    } tokens;

    size_t tokens_parsed; /** The number of tokens fetched from the queue. */
    int token_available;  /** Does the tokens queue contain a token ready for
                             dequeueing. */

    /**
     * @}
     */

    /**
     * @name Parser stuff
     * @{
     */

    /** The parser states stack. */
    struct {
        JsonParseEvent *start; /**< The beginning of the event. */
        JsonParseEvent *end;   /**< The end of the event. */
        JsonParseEvent *top;   /**< The top of the event. */

    } events;

    JsonParseEvent event; /**< The current parser event. */

    /** The stack of marks. */
    struct {
        JsonPosition *start; /** The beginning of the stack. */
        JsonPosition *end;   /** The end of the stack. */
        JsonPosition *top;   /** The top of the stack. */

    } marks;

    /**
     * @}
     */

} JsonParser;

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

typedef int JsonWriteHandler(void *data, unsigned char *buffer, size_t size);

/**
 * @enum JsonEmitEvent
 * @brief Enumerates types for JSON emit event.
 */
typedef enum JsonEmitterEvent {

    JSON_EMIT_SCALAR_EVENT,       /** A SCALAR event. */
    JSON_EMIT_ARRAY_START_EVENT,  /** A ARRAY-START event. */
    JSON_EMIT_ARRAY_END_EVENT,    /** A ARRAY-END event. */
    JSON_EMIT_OBJECT_START_EVENT, /** A OBJECT-START event. */
    JSON_EMIT_OBJECT_END_EVENT    /** A OBJECT-END event. */

} JsonEmitterEvent;

/** @} */

/**
 * The emitter structure.
 *
 * All members are internal.  Manage the structure using the @c json_emitter_
 * family of functions.
 */
typedef struct JsonEmitter {
    /**
     * @name Error handling
     * @{
     */

    JsonError_t error; /** Error type. */

    /**
     * @}
     */

    /**
     * @name Writer stuff
     * @{
     */

    JsonWriteHandler *write_handler; /** Write handler. */
    void *write_handler_data;        /** A pointer for passing to the write handler. */

    /** Standard (string or file) output data. */
    union {
        /** String output data. */
        struct {
            unsigned char *buffer; /**< The buffer pointer. */
            size_t *size_written;  /**< The number of written bytes. */
            size_t size;           /**< The buffer size. */

        } string;

        FILE *file; /** File output data. */

    } output;

    /** The working buffer. */
    struct {
        JsonChar_t *pointer; /** The current position of the buffer. */
        JsonChar_t *start;   /** The beginning of the buffer. */
        JsonChar_t *last;    /** The last filled position of the buffer. */
        JsonChar_t *end;     /** The end of the buffer. */

    } buffer;

    /** The raw buffer. */
    struct {
        unsigned char *pointer; /** The current position of the buffer. */
        unsigned char *start;   /** The beginning of the buffer. */
        unsigned char *last;    /** The last filled position of the buffer. */
        unsigned char *end;     /** The end of the buffer. */

    } raw_buffer;

    JsonEncoding encoding; /** The stream encoding. */

    /**
     * @}
     */

    /**
     * @name Emitter stuff
     * @{
     */

    /** The stack emitter of events. */
    struct {
        JsonEmitterEvent *start; /**< The beginning of the event. */
        JsonEmitterEvent *end;   /**< The end of the event. */
        JsonEmitterEvent *top;   /**< The top of the event. */

    } states;

    JsonEmitterEvent state; /**< The current emitter state. */

    /** The event queue. */
    struct {
        JsonEvent *start; /**< The beginning of the event queue. */
        JsonEvent *head;  /**< The head of the event queue. */
        JsonEvent *tail;  /**< The tail of the event queue. */
        JsonEvent *end;   /**< The end of the event queue. */

    } events;

    int line;   /**< The current line. */
    int column; /**< The current column. */

    /**
     * @}
     */

    /**
     * @name Dumper stuff
     * @{
     */

     JsonDocument *document; /** The currently emitted document. */

    int opened;         /** If the stream was already opened? */
    int closed;         /** If the stream was already closed? */

    /**
     * @}
     */

} JsonEmitter;

#endif  // MYJSON_DISABLE_WRITER

/** @} */

#pragma region C

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

#pragma region Event

MYJSON_API int json_event_initialize_stream_start(JsonEvent *event, JsonEncoding encoding);
MYJSON_API int json_event_initialize_stream_end(JsonEvent *event);
MYJSON_API int json_event_initialize_document_start(JsonEvent *event);
MYJSON_API int json_event_initialize_document_end(JsonEvent *event);

MYJSON_API int json_event_initialize_scalar(JsonEvent *event, const JsonChar_t *value, int length);
MYJSON_API int json_event_initialize_array_start(JsonEvent *event);
MYJSON_API int json_event_initialize_array_end(JsonEvent *event);
MYJSON_API int json_event_initialize_object_start(JsonEvent *event);
MYJSON_API int json_event_initialize_object_end(JsonEvent *event);

/**
 * Free any memory allocated for an event object.
 *
 * @param[in,out]   event   An event object.
 */
MYJSON_API void json_event_delete(JsonEvent *event);

#pragma endregion  // Event

#pragma region Json

MYJSON_API int json_document_initialize(JsonDocument *document);
MYJSON_API void json_document_delete(JsonDocument *document);

MYJSON_API JsonNode *json_document_get_root_node(JsonDocument *document);
MYJSON_API JsonNode *json_document_get_node(JsonDocument *document, int index);

MYJSON_API int json_document_add_scalar(JsonDocument *document, const JsonChar_t *value, int length);
MYJSON_API int json_document_add_array(JsonDocument *document);
MYJSON_API int json_document_add_object(JsonDocument *document);

MYJSON_API int json_document_append_array_item(JsonDocument *document, int array, int item);
MYJSON_API int json_document_append_object_pair(JsonDocument *document, int object, int key, int value);

MYJSON_API const JsonChar_t *json_document_get_scalar_value(JsonDocument *document, int node_id);
MYJSON_API int json_document_get_scalar_length(JsonDocument *document, int node_id);
MYJSON_API int json_document_array_get_item(JsonDocument *document, int array_node_id, int index);
MYJSON_API int json_document_object_get_value(JsonDocument *document, int object_node_id, const JsonChar_t *key,
                                              int key_length);

MYJSON_API int json_document_get_node_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count);
MYJSON_API const JsonChar_t *json_document_get_value_by_path(JsonDocument *document, const JsonChar_t **keys,
                                                             int key_count);
MYJSON_API int json_document_get_value_length_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count);

#pragma endregion  // Json

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region Encoding

#pragma endregion  // Encoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

MYJSON_API int json_parser_initialize(JsonParser *parser);
MYJSON_API int json_parser_parse(JsonParser *parser, JsonEvent *event);
MYJSON_API int json_parser_load(JsonParser *parser, JsonDocument *document);
MYJSON_API int json_parser_delete(JsonParser *parser);

MYJSON_API int json_parser_set_input_file(JsonParser *parser, FILE *file);
MYJSON_API int json_parser_set_input_string(JsonParser *parser, const unsigned char *input, size_t size);
MYJSON_API int json_parser_set_input(JsonParser *parser, JsonReadHandler *handler, void *data);

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

MYJSON_API int json_emitter_initialize(JsonEmitter *emitter);
MYJSON_API int json_emitter_emit(JsonEmitter *emitter, JsonEvent *event);
MYJSON_API int json_emitter_delete(JsonEmitter *emitter);

MYJSON_API int json_emitter_set_output_file(JsonEmitter *emitter, FILE *file);
MYJSON_API int json_emitter_set_output_string(JsonEmitter *emitter, const unsigned char *output, size_t size,
                                              size_t *size_written);
MYJSON_API int json_emitter_set_output(JsonEmitter *emitter, JsonWriteHandler *handler, void *data);
MYJSON_API int json_emitter_set_encoding(JsonEmitter *emitter, JsonEncoding encoding);

MYJSON_API int json_emitter_open(JsonEmitter *emitter);
MYJSON_API int json_emitter_close(JsonEmitter *emitter);
MYJSON_API int json_emitter_flush(JsonEmitter *emitter);

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

#ifdef __cplusplus
}
#endif  //__cplusplus

#pragma endregion  // C

#pragma region Cpp

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace json {

#pragma region Json

#pragma endregion  // Json

#pragma region Conversion

#pragma endregion  // Conversion

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region Encoding

#pragma endregion  // Encoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

}  // namespace json

#endif  //__cplusplus

#pragma endregion  // Cpp

//-----------------------------------------------------------------------------
// [SECTION] Compiler Hint End
//-----------------------------------------------------------------------------

#endif  // DJOEZEKE_MYJSON