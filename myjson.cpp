/**
 * @file myjson.c
 * @brief JSON  parser library header for C/C++.
 * This is a  C/C++ Json Parser Library Source @c myjson.h.
 * @details This header provides all public API, types, macros, and configuration for YAML and supports both C and C++ usage.
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
 *
 *  Internal:
 *
 *  [SECTION] Includes
 *  [SECTION] Macro Defines
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *  [SECTION] C++ Only Classes
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *
 *  Myyaml:
 *
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

//-------------------------------------------------------------------------
// [SECTION] INCLUDES
//-------------------------------------------------------------------------

#include "myjson.hpp"

#include <sstream>
#include <iostream>
#include <cctype>
#include <stdexcept>

#pragma region Internal

//-------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

#define CASEFY_ERROR(value) \
    case value:             \
        name = #value;      \
        break

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    //-----------------------------------------------------------------------------
    // [SECTION] Declarations
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [SECTION] Definations
    //-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#endif //__cplusplus

#pragma endregion

#pragma region Mytoml

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef __cplusplus
}
#endif // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace json
{

    Exception::Exception()
        : m_Msg("(UNKNOWN) -> UNKNOWN ERROR TYPE"), m_ErrType(json::Error::UNKNOWN) {}

    Exception::Exception(json::Error errorType)
        : m_Msg("(" + GetErrName(errorType) + ") -> ERROR MESSAGE EMPTY"), m_ErrType(errorType) {}

    Exception::Exception(const std::string &message, json::Error errorType)
        : m_Msg("(" + GetErrName(errorType) + ") -> " + message), m_ErrType(errorType) {}

    const char *Exception::what() const noexcept { return m_Msg.c_str(); }
    json::Error Exception::GetErrType() const noexcept { return m_ErrType; }
    std::string Exception::GetErrName(json::Error error) const noexcept
    {
        std::string name;
        switch (error)
        {
            CASEFY_ERROR(Error::UNKNOWN);
            CASEFY_ERROR(Error::MISSING_SEPARATOR);
            CASEFY_ERROR(Error::MISSING_VALUE);
            CASEFY_ERROR(Error::KEY_NOT_FOUND);
            CASEFY_ERROR(Error::VALUE_NOT_FOUND);
            CASEFY_ERROR(Error::NON_BOOL_TYPE);
            CASEFY_ERROR(Error::NON_NULL_TYPE);
            CASEFY_ERROR(Error::NON_NUMBER_TYPE);
            CASEFY_ERROR(Error::NON_OBJECT_TYPE);
            CASEFY_ERROR(Error::NON_ARRAY_TYPE);
            CASEFY_ERROR(Error::NON_STRING_TYPE);
            CASEFY_ERROR(Error::INVALID_OBJECT);
            CASEFY_ERROR(Error::INVALID_ARRAY);
            CASEFY_ERROR(Error::INVALID_STRING);
            CASEFY_ERROR(Error::INVALID_BOOL);
            CASEFY_ERROR(Error::INVALID_NUMBER);
            CASEFY_ERROR(Error::INVALID_NULL);
            CASEFY_ERROR(Error::INVALID_JSON);
            CASEFY_ERROR(Error::KEY_ALREADY_EXISTS);
            CASEFY_ERROR(Error::VALUE_CANT_BE_NULL);
            CASEFY_ERROR(Error::WRONG_TYPE_CAST);
        }
        return name;
    }

    JSON::JSON() : m_Type(json::Type::UNKNOWN), m_Value(std::monostate{}) {}

    JSON::JSON(json::Type type) : m_Type(type)
    {
        if (type == json::Type::ARRAY)
            m_Array.clear();
        else if (type == json::Type::OBJECT)
            m_Object.clear();
        else
            m_Value = std::monostate{};
    }

    JSON::JSON(json::Type type, std::variant<std::monostate, std::string, int, double, bool> value)
        : m_Type(type), m_Value(value) {}

    JSON::JSON(const JSON &other)
        : m_Type(other.m_Type), m_Value(other.m_Value)
    {
        for (const auto &kv : other.m_Object)
            m_Object[kv.first] = std::make_unique<JSON>(*kv.second);
        for (const auto &kv : other.m_Array)
            m_Array[kv.first] = std::make_unique<JSON>(*kv.second);
    }

    JSON::JSON(JSON &&other) noexcept
        : m_Type(other.m_Type), m_Value(std::move(other.m_Value)),
          m_Array(std::move(other.m_Array)), m_Object(std::move(other.m_Object)) {}

    JSON::~JSON() { Destroy(); }

    void JSON::Destroy()
    {
        m_Array.clear();
        m_Object.clear();
        m_Value = std::monostate{};
        m_Type = json::Type::UNKNOWN;
    }

    bool JSON::IsArray() const { return m_Type == json::Type::ARRAY; }
    bool JSON::IsObject() const { return m_Type == json::Type::OBJECT; }
    bool JSON::IsString() const { return m_Type == json::Type::STRING; }
    bool JSON::IsNumber() const { return m_Type == json::Type::DOUBLE || m_Type == json::Type::INTEGER; }
    bool JSON::IsBool() const { return m_Type == json::Type::BOOLEAN; }
    bool JSON::IsNone() const { return m_Type == json::Type::NONE; }
    bool JSON::Empty() const
    {
        if (m_Type == json::Type::OBJECT)
            return m_Object.empty();
        if (m_Type == json::Type::ARRAY)
            return m_Array.empty();
        if (m_Type == json::Type::STRING)
            return std::get<std::string>(m_Value).empty();
        return false;
    }

    std::string JSON::String() const
    {
        std::stringstream ss;
        switch (m_Type)
        {
        case json::Type::NONE:
            ss << "null";
            break;
        case json::Type::BOOLEAN:
            ss << (std::get<bool>(m_Value) ? "true" : "false");
            break;
        case json::Type::INTEGER:
            ss << std::get<int>(m_Value);
            break;
        case json::Type::DOUBLE:
            ss << std::get<double>(m_Value);
            break;
        case json::Type::STRING:
            ss << "\"" << std::get<std::string>(m_Value) << "\"";
            break;
        case json::Type::ARRAY:
            ss << "[";
            for (auto it = m_Array.begin(); it != m_Array.end(); ++it)
            {
                if (it != m_Array.begin())
                    ss << ",";
                ss << it->second->String();
            }
            ss << "]";
            break;
        case json::Type::OBJECT:
            ss << "{";
            for (auto it = m_Object.begin(); it != m_Object.end(); ++it)
            {
                if (it != m_Object.begin())
                    ss << ",";
                ss << "\"" << it->first << "\":" << it->second->String();
            }
            ss << "}";
            break;
        default:
            throw json::Exception("Unknown JSON type", json::Error::UNKNOWN);
        }
        return ss.str();
    }

    json::Type JSON::Type() const { return m_Type; }

    std::vector<std::string> JSON::Keys() const
    {
        std::vector<std::string> keys;
        if (m_Type == Type::OBJECT)
            for (const auto &pair : m_Object)
                keys.push_back(pair.first);
        else if (m_Type == Type::ARRAY)
            for (const auto &pair : m_Array)
                keys.push_back(std::to_string(pair.first));
        return keys;
    }

    json::Type JSON::ValueType(const std::string &key) const
    {
        if (m_Type != Type::OBJECT)
            return json::Type::UNKNOWN;
        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
            return iter->second->Type();
        return json::Type::UNKNOWN;
    }

    json::Type JSON::ValueType(int key) const
    {
        if (m_Type != Type::ARRAY)
            return json::Type::UNKNOWN;
        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
            return iter->second->Type();
        return json::Type::UNKNOWN;
    }

    bool JSON::HasKey(const std::string &key) const
    {
        if (m_Type != json::Type::OBJECT)
            return false;
        return m_Object.find(key) != m_Object.end();
    }

    bool JSON::HasKey(int key) const
    {
        if (m_Type != json::Type::ARRAY)
            return false;
        return m_Array.find(key) != m_Array.end();
    }

    void JSON::Add(const std::string &key, const json::JSON &value)
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("Add: Not an object", Error::NON_OBJECT_TYPE);
        m_Object[key] = std::make_unique<json::JSON>(value);
    }

    void JSON::Add(int key, const json::JSON &value)
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("Add: Not an array", Error::NON_ARRAY_TYPE);
        m_Array[key] = std::make_unique<json::JSON>(value);
    }

    void JSON::Replace(const std::string &key, const json::JSON &value)
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("Replace: Not an object", Error::NON_OBJECT_TYPE);
        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
            iter->second = std::make_unique<json::JSON>(value);
        else
            throw json::Exception("Replace: Key not found", Error::KEY_NOT_FOUND);
    }

    void JSON::Replace(int key, const json::JSON &value)
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("Replace: Not an array", Error::NON_ARRAY_TYPE);
        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
            iter->second = std::make_unique<json::JSON>(value);
        else
            throw json::Exception("Replace: Index not found", Error::KEY_NOT_FOUND);
    }

    json::JSON JSON::Get(const std::string &key) const
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("Get: Not an object", Error::NON_OBJECT_TYPE);
        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
            return *(iter->second);
        throw json::Exception("Get: Key not found", Error::KEY_NOT_FOUND);
    }

    json::JSON JSON::Get(int key) const
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("Get: Not an array", Error::NON_ARRAY_TYPE);
        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
            return *(iter->second);
        throw json::Exception("Get: Index not found", Error::KEY_NOT_FOUND);
    }

    void JSON::Get(const std::string &key, json::JSON &value) const
    {
        value = Get(key);
    }

    void JSON::Get(int key, json::JSON &value) const
    {
        value = Get(key);
    }

    void JSON::Delete(const std::string &key)
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("Delete: Not an object", Error::NON_OBJECT_TYPE);
        m_Object.erase(key);
    }

    void JSON::Delete(int key)
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("Delete: Not an array", Error::NON_ARRAY_TYPE);
        m_Array.erase(key);
    }

    json::JSON JSON::Detach(const std::string &key)
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("Detach: Not an object", Error::NON_OBJECT_TYPE);
        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            json::JSON detached = std::move(*iter->second);
            m_Object.erase(iter);
            return detached;
        }
        throw json::Exception("Detach: Key not found", Error::KEY_NOT_FOUND);
    }

    json::JSON JSON::Detach(int key)
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("Detach: Not an array", Error::NON_ARRAY_TYPE);
        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            json::JSON detached = std::move(*iter->second);
            m_Array.erase(iter);
            return detached;
        }
        throw json::Exception("Detach: Index not found", Error::KEY_NOT_FOUND);
    }

    std::string JSON::operator()(const std::string &key) const
    {
        return Get(key).String();
    }

    std::string JSON::operator()(int key) const
    {
        return Get(key).String();
    }

    json::JSON &JSON::operator[](const std::string &key)
    {
        if (m_Type != json::Type::OBJECT)
            throw json::Exception("operator[]: Not an object", Error::NON_OBJECT_TYPE);
        return *(m_Object[key]);
    }

    json::JSON &JSON::operator[](int key)
    {
        if (m_Type != json::Type::ARRAY)
            throw json::Exception("operator[]: Not an array", Error::NON_ARRAY_TYPE);
        return *(m_Array[key]);
    }

    JSON &JSON::operator=(const JSON &other)
    {
        if (this != &other)
        {
            Destroy();
            m_Type = other.m_Type;
            m_Value = other.m_Value;
            for (const auto &kv : other.m_Object)
                m_Object[kv.first] = std::make_unique<JSON>(*kv.second);
            for (const auto &kv : other.m_Array)
                m_Array[kv.first] = std::make_unique<JSON>(*kv.second);
        }
        return *this;
    }

    JSON &JSON::operator=(JSON &&other) noexcept
    {
        if (this != &other)
        {
            Destroy();
            m_Type = other.m_Type;
            m_Value = std::move(other.m_Value);
            m_Object = std::move(other.m_Object);
            m_Array = std::move(other.m_Array);
        }
        return *this;
    }

    bool JSON::operator==(const JSON &other) const
    {
        return this->String() == other.String();
    }

    bool JSON::operator!=(const JSON &other) const
    {
        return !(*this == other);
    }

    std::ostream &operator<<(std::ostream &os, const json::JSON &json)
    {
        os << json.String();
        return os;
    }

    std::string dump(const json::JSON &json, bool /*ensure_ascii*/)
    {
        return json.String();
    }

    void print(const json::JSON &json, bool indent)
    {
        if (indent)
            std::cout << json.String() << std::endl;
        else
            std::cout << json.String();
    }

    namespace
    {

        // Helper: skip whitespace
        void skip_ws(const std::string &s, size_t &i)
        {
            while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i])))
                ++i;
        }

        // Helper: parse literal (true, false, null)
        json::JSON parse_literal(const std::string &s, size_t &i)
        {
            if (s.compare(i, 4, "true") == 0)
            {
                i += 4;
                return json::JSON(json::Type::BOOLEAN, true);
            }
            if (s.compare(i, 5, "false") == 0)
            {
                i += 5;
                return json::JSON(json::Type::BOOLEAN, false);
            }
            if (s.compare(i, 4, "null") == 0)
            {
                i += 4;
                return json::JSON(json::Type::NONE, std::monostate{});
            }
            throw json::Exception("Invalid literal", json::Error::INVALID_JSON);
        }

        // Helper: parse number
        json::JSON parse_number(const std::string &s, size_t &i)
        {
            size_t start = i;
            bool is_double = false;
            if (s[i] == '-')
                ++i;
            while (i < s.size() && std::isdigit(s[i]))
                ++i;
            if (i < s.size() && s[i] == '.')
            {
                is_double = true;
                ++i;
                while (i < s.size() && std::isdigit(s[i]))
                    ++i;
            }
            if (i < s.size() && (s[i] == 'e' || s[i] == 'E'))
            {
                is_double = true;
                ++i;
                if (s[i] == '+' || s[i] == '-')
                    ++i;
                while (i < s.size() && std::isdigit(s[i]))
                    ++i;
            }
            std::string num = s.substr(start, i - start);
            try
            {
                if (is_double)
                {
                    return json::JSON(json::Type::DOUBLE, std::stod(num));
                }
                else
                {
                    return json::JSON(json::Type::INTEGER, std::stoi(num));
                }
            }
            catch (...)
            {
                throw json::Exception("Invalid number", json::Error::INVALID_NUMBER);
            }
        }

        // Helper: parse string (with escapes)
        std::string parse_string(const std::string &s, size_t &i)
        {
            if (s[i] != '"')
                throw json::Exception("Expected '\"'", json::Error::INVALID_STRING);
            ++i;
            std::string result;
            while (i < s.size())
            {
                char c = s[i++];
                if (c == '"')
                    break;
                if (c == '\\')
                {
                    if (i >= s.size())
                        throw json::Exception("Invalid escape", json::Error::INVALID_STRING);
                    char esc = s[i++];
                    switch (esc)
                    {
                    case '"':
                        result += '"';
                        break;
                    case '\\':
                        result += '\\';
                        break;
                    case '/':
                        result += '/';
                        break;
                    case 'b':
                        result += '\b';
                        break;
                    case 'f':
                        result += '\f';
                        break;
                    case 'n':
                        result += '\n';
                        break;
                    case 'r':
                        result += '\r';
                        break;
                    case 't':
                        result += '\t';
                        break;
                    case 'u':
                    {
                        if (i + 4 > s.size())
                            throw json::Exception("Invalid unicode escape", json::Error::INVALID_STRING);
                        unsigned int code = std::stoul(s.substr(i, 4), nullptr, 16);
                        // Basic Unicode BMP only
                        if (code <= 0x7F)
                            result += static_cast<char>(code);
                        // For full unicode, use a library or extend here
                        i += 4;
                        break;
                    }
                    default:
                        throw json::Exception("Unknown escape", json::Error::INVALID_STRING);
                    }
                }
                else
                {
                    result += c;
                }
            }
            return result;
        }

        // Forward declaration
        json::JSON parse_value(const std::string &s, size_t &i);

        // Helper: parse array
        json::JSON parse_array(const std::string &s, size_t &i)
        {
            if (s[i] != '[')
                throw json::Exception("Expected '['", json::Error::INVALID_ARRAY);
            ++i;
            skip_ws(s, i);
            json::JSON arr(json::Type::ARRAY);
            int idx = 0;
            if (s[i] == ']')
            {
                ++i;
                return arr;
            }
            while (i < s.size())
            {
                skip_ws(s, i);
                arr.Add(idx++, parse_value(s, i));
                skip_ws(s, i);
                if (s[i] == ']')
                {
                    ++i;
                    break;
                }
                if (s[i] != ',')
                    throw json::Exception("Expected ',' in array", json::Error::INVALID_ARRAY);
                ++i;
            }
            return arr;
        }

        // Helper: parse object
        json::JSON parse_object(const std::string &s, size_t &i)
        {
            if (s[i] != '{')
                throw json::Exception("Expected '{'", json::Error::INVALID_OBJECT);
            ++i;
            skip_ws(s, i);
            json::JSON obj(json::Type::OBJECT);
            if (s[i] == '}')
            {
                ++i;
                return obj;
            }
            while (i < s.size())
            {
                skip_ws(s, i);
                std::string key = parse_string(s, i);
                skip_ws(s, i);
                if (s[i] != ':')
                    throw json::Exception("Expected ':'", json::Error::MISSING_SEPARATOR);
                ++i;
                skip_ws(s, i);
                obj.Add(key, parse_value(s, i));
                skip_ws(s, i);
                if (s[i] == '}')
                {
                    ++i;
                    break;
                }
                if (s[i] != ',')
                    throw json::Exception("Expected ',' in object", json::Error::INVALID_OBJECT);
                ++i;
            }
            return obj;
        }

        // Main value parser
        json::JSON parse_value(const std::string &s, size_t &i)
        {
            skip_ws(s, i);
            if (i >= s.size())
                throw json::Exception("Unexpected end", json::Error::INVALID_JSON);
            char c = s[i];
            if (c == '{')
                return parse_object(s, i);
            if (c == '[')
                return parse_array(s, i);
            if (c == '"')
                return json::JSON(json::Type::STRING, parse_string(s, i));
            if (std::isdigit(c) || c == '-')
                return parse_number(s, i);
            if (c == 't' || c == 'f' || c == 'n')
                return parse_literal(s, i);
            throw json::Exception("Invalid value", json::Error::INVALID_JSON);
        }

    } // end anonymous namespace

    json::JSON load(const std::string &json_str, char * /*encoding*/)
    {
        size_t i = 0;
        skip_ws(json_str, i);
        json::JSON result = parse_value(json_str, i);
        skip_ws(json_str, i);
        if (i != json_str.size())
            throw json::Exception("Extra data after JSON", json::Error::INVALID_JSON);
        return result;
    }

} // namespace json

#endif //__cplusplus
#pragma endregion
