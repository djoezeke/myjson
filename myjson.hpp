/**
 * @file myjson.h
 * @brief JSON parser library header for C/C++.
 * This is a  C/C++ Yaml Parser Library Header @c myjson.c.
 * @details This header provides all public API, types, macros, and configuration for JSON and supports both C and C++ usage.
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

#ifndef MY_JSON_H
#define MY_JSON_H

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef __cplusplus

/** C++ Exclusive headers. */
#include <exception>
#include <unordered_map>
#include <vector>
#include <variant>
#include <memory>
#include <string>
#include <ostream>

#endif //__cplusplus

#define MYJSON_DEBUG

#ifdef MYJSON_DEBUG
#endif // MYJSON_DEBUG

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Function Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
#define MYJSON_NO_EXPORT_ATTR
#define MYJSON_API_EXPORT __declspec(dllexport)
#define MYJSON_API_IMPORT __declspec(dllimport)
#define MYJSON_DEPRECATED_ATTR __declspec(deprecated)
#else // _WIN32
#define MYJSON_API_EXPORT __attribute__((visibility("default")))
#define MYJSON_API_IMPORT __attribute__((visibility("default")))
#define MYJSON_NO_EXPORT_ATTR __attribute__((visibility("hidden")))
#define MYJSON_DEPRECATED_ATTR __attribute__((__deprecated__))
#endif // _WIN32

/**
 * @def MYJSON_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct symbol visibility on all platforms.
 */

#if defined(MYJSON_BUILD_STATIC)
#define MYJSON_API
#elif defined(MYJSON_BUILD_SHARED)
/* We are building this library */
#define MYJSON_API MYJSON_API_EXPORT
#elif defined(MYJSON_IMPORT)
/* We are using this library */
#define MYJSON_API MYJSON_API_IMPORT
#else // MYJSON_BUILD_STATIC
#define MYJSON_API
#endif // MYJSON_BUILD_STATIC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for JSON.
 * @{
 */

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#ifdef __cplusplus
}
#endif //__cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace json
{
    enum class Error
    {
        UNKNOWN = -1,
        MISSING_SEPARATOR,
        MISSING_VALUE,
        KEY_NOT_FOUND,
        VALUE_NOT_FOUND,
        NON_BOOL_TYPE,
        NON_NULL_TYPE,
        NON_NUMBER_TYPE,
        NON_OBJECT_TYPE,
        NON_ARRAY_TYPE,
        NON_STRING_TYPE,
        INVALID_OBJECT,
        INVALID_ARRAY,
        INVALID_STRING,
        INVALID_BOOL,
        INVALID_NUMBER,
        INVALID_NULL,
        INVALID_JSON,
        KEY_ALREADY_EXISTS,
        VALUE_CANT_BE_NULL,
        WRONG_TYPE_CAST
    };

    enum class Type
    {
        UNKNOWN = -1,
        NONE,
        OBJECT,
        ARRAY,
        BOOLEAN,
        INTEGER,
        DOUBLE,
        STRING
    };

    class Exception : public std::exception
    {
    public:
        Exception();
        Exception(json::Error type);
        Exception(const std::string &message, json::Error type);
        const char *what() const noexcept override;
        json::Error GetErrType() const noexcept;
        std::string GetErrName(json::Error error) const noexcept;

    private:
        mutable std::string m_Msg;
        json::Error m_ErrType;
    };

    class JSON
    {
    public:
        JSON();
        JSON(json::Type type);
        JSON(json::Type type, std::variant<std::monostate, std::string, int, double, bool> value);
        JSON(const JSON &other);
        JSON(JSON &&other) noexcept;
        ~JSON();

        bool IsArray() const;
        bool IsObject() const;
        bool IsString() const;
        bool IsNumber() const;
        bool IsBool() const;
        bool IsNone() const;
        bool Empty() const;
        std::string String() const;
        json::Type Type() const;
        std::vector<std::string> Keys() const;

        json::Type ValueType(const std::string &key) const;
        json::Type ValueType(int key) const;
        bool HasKey(const std::string &key) const;
        bool HasKey(int key) const;
        void Add(const std::string &key, const json::JSON &value);
        void Add(int key, const json::JSON &value);
        void Replace(const std::string &key, const json::JSON &value);
        void Replace(int key, const json::JSON &value);
        json::JSON Get(const std::string &key) const;
        json::JSON Get(int key) const;
        void Get(const std::string &key, json::JSON &value) const;
        void Get(int key, json::JSON &value) const;
        void Delete(const std::string &key);
        void Delete(int key);
        json::JSON Detach(const std::string &key);
        json::JSON Detach(int key);

        JSON &operator=(const JSON &other);
        JSON &operator=(JSON &&other) noexcept;
        bool operator==(const JSON &other) const;
        bool operator!=(const JSON &other) const;
        JSON &operator[](const std::string &key);
        JSON &operator[](int key);
        std::string operator()(const std::string &key) const;
        std::string operator()(int key) const;

    private:
        void Destroy();
        json::Type m_Type;
        std::variant<std::monostate, std::string, int, double, bool> m_Value;
        std::unordered_map<unsigned int, std::unique_ptr<JSON>> m_Array;
        std::unordered_map<std::string, std::unique_ptr<JSON>> m_Object;
    };

    std::ostream &operator<<(std::ostream &os, const json::JSON &json);
    std::string dump(const json::JSON &json, bool ensure_ascii = true);
    json::JSON load(const std::string &json, char *encoding = nullptr);
    void print(const json::JSON &json, bool indent = true);

} // namespace json
#endif //__cplusplus

#endif // MY_JSON_H