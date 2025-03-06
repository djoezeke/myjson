#include <sstream>
#include <iostream>
#include "myjson.hpp"

namespace json
{

    /**
     * @brief Parses a JSON value from a string.
     * @param json The JSON string to parse.
     * @param index The current position in the string.
     * @return The parsed JSON value.
     * @throws json::Exception if the JSON is invalid.
     */
    json::JSON parse_value(const std::string &json, size_t &index);

    /**
     * @brief Skips whitespace characters in the JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     */
    void skip_whitespace(const std::string &json, size_t &index);

    /**
     * @brief Parses a null value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a null value.
     * @throws json::Exception if the null value is invalid.
     */
    json::JSON parse_null(const std::string &json, size_t &index);

    /**
     * @brief Parses a boolean value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a boolean value.
     * @throws json::Exception if the boolean value is invalid.
     */
    json::JSON parse_boolean(const std::string &json, size_t &index);

    /**
     * @brief Parses a number (integer or double) from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a number.
     * @throws json::Exception if the number is invalid.
     */
    json::JSON parse_number(const std::string &json, size_t &index);

    /**
     * @brief Parses a string value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a string.
     * @throws json::Exception if the string is invalid.
     */
    json::JSON parse_string(const std::string &json, size_t &index);

    /**
     * @brief Parses an array from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing an array.
     * @throws json::Exception if the array is invalid.
     */
    json::JSON parse_array(const std::string &json, size_t &index);

    /**
     * @brief Parses an object from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing an object.
     * @throws json::Exception if the object is invalid.
     */
    json::JSON parse_object(const std::string &json, size_t &index);

#pragma region json

    JSON::JSON()
    {
        m_Type = json::Type::UNKNOWN;
        m_Value = std::monostate{};
        m_Array = {};
        m_Object = {};
    }

    JSON::JSON(json::Type type)
    {
        m_Type = type;

        if (type == json::Type::ARRAY)
        {
            m_Array = {};
        }
        else if (type == json::Type::OBJECT)
        {
            m_Object = {};
        }
        else
        {
            m_Value = std::monostate{};
        }
    }

    JSON::JSON(json::Type type, std::variant<std::monostate, std::string, int, double, bool> value)
    {
        if (type == json::Type::ARRAY)
        {
            m_Type = json::Type::ARRAY;
            m_Array = {};
            m_Object = {};
        }
        else if (type == json::Type::OBJECT)
        {
            m_Type = json::Type::OBJECT;
            m_Array = {};
            m_Object = {};
        }
        else if (auto _value = std::get_if<std::string>(&value))
        {
            const std::string &v = *_value;
            m_Type = json::Type::STRING;
            m_Value = v;
            m_Array = {};
            m_Object = {};
        }
        else if (auto _value = std::get_if<double>(&value))
        {
            const double &v = *_value;
            m_Type = json::Type::DOUBLE;
            m_Value = v;
            m_Array = {};
            m_Object = {};
        }
        else if (auto _value = std::get_if<bool>(&value))
        {
            const bool &v = *_value;
            m_Type = json::Type::BOOLEAN;
            m_Value = v;
            m_Array = {};
            m_Object = {};
        }
        else if (auto _value = std::get_if<int>(&value))
        {
            const int &v = *_value;
            m_Type = json::Type::INTEGER;
            m_Value = v;
            m_Array = {};
            m_Object = {};
        }
        else
        {
            m_Type = json::Type::UNKNOWN;
            m_Value = std::monostate{};
            m_Array = {};
            m_Object = {};
        }
    }

    JSON::JSON(const JSON *other)
    {
        if (other != nullptr)
        {
            m_Type = other->m_Type;
            m_Value = other->m_Value;
            m_Array = other->m_Array;
            m_Object = other->m_Object;
        }
        else
        {
            m_Type = json::Type::UNKNOWN;
            m_Value = std::monostate{};
        }
    }

    JSON::JSON(const JSON &other)
    {
        m_Type = other.m_Type;
        m_Value = other.m_Value;
        m_Array = other.m_Array;
        m_Object = other.m_Object;
    }

    JSON::JSON(JSON &&other)
    {
        m_Type = std::move(other.m_Type);
        m_Value = std::move(other.m_Value);
        m_Array = std::move(other.m_Array);
        m_Object = std::move(other.m_Object);
    }

    JSON::~JSON()
    {
        Destroy();
    }

    bool JSON::IsArray() const
    {
        return m_Type == json::Type::ARRAY;
    }

    bool JSON::IsObject() const
    {
        return m_Type == json::Type::OBJECT;
    }

    bool JSON::IsNumber() const
    {
        return m_Type == json::Type::DOUBLE || m_Type == json::Type::INTEGER;
    }

    bool JSON::IsBool() const
    {
        return m_Type == json::Type::BOOLEAN;
    }

    bool JSON::IsNil() const
    {
        return m_Type == json::Type::NIL;
    }

    bool JSON::Empty() const
    {
        if (m_Type == json::Type::OBJECT)
        {
            return m_Object.empty();
        }
        else if (m_Type == json::Type::ARRAY)
        {
            return m_Array.empty();
        }
        else if (m_Type == json::Type::STRING)
        {
            return std::get<std::string>(m_Value).empty();
        }
        else if (m_Type == json::Type::NIL)
        {
            return true;
        }
        else
        {
            // Check if the variant is in an unset state
            return std::holds_alternative<std::monostate>(m_Value);
        }
    }

    /**
     * @brief Converts the JSON value to a string.
     * @return The JSON value as a string.
     * @throws json::Exception if the JSON type is unknown.
     * @code
     * json::JSON jsonString(json::Type::STRING, "Hello, World!");
     * std::string str = jsonString.String();
     * @endcode
     */
    std::string JSON::String() const
    {
        if (m_Type == Type::UNKNOWN)
            throw json::Exception("Unknown JSON type", Error::UNKNOWN);

        return dump(*this, false);
    }

    json::Type JSON::Type() const
    {
        return m_Type;
    };

    std::vector<std::string> JSON::Keys() const
    {
        std::vector<std::string> keys;

        if (m_Type == Type::OBJECT)
        {
            for (const auto &pair : m_Object)
            {
                keys.push_back(pair.first);
            }
        }
        else if (m_Type == Type::ARRAY)
        {
            for (const auto &pair : m_Array)
            {
                keys.push_back(std::to_string(pair.first));
            }
        }

        return keys;
    };

    json::Type JSON::ValueType(const std::string &key) const
    {
        if (m_Type != Type::OBJECT)
            return json::Type::UNKNOWN;

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            return iter->second->Type();
        }

        return json::Type::UNKNOWN;
    }

    json::Type JSON::ValueType(int key) const
    {
        if (m_Type != Type::ARRAY)
            return json::Type::UNKNOWN;

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            return iter->second->Type();
        }

        return json::Type::UNKNOWN;
    }

    bool JSON::HasKey(const std::string &key) const
    {
        if (m_Type != json::Type::OBJECT)
            return false;

        auto iter = m_Object.find(key);
        return iter != m_Object.end();
    };

    bool JSON::HasKey(int key) const
    {
        if (m_Type != json::Type::ARRAY)
            return false;

        auto iter = m_Array.find(key);
        return iter != m_Array.end();
    };

    void JSON::Add(std::string key, json::JSON value)
    {
        if (m_Type != json::Type::OBJECT)
            return;

        m_Object[key] = new json::JSON(value);
    }

    void JSON::Add(int key, json::JSON value)
    {
        if (m_Type != json::Type::ARRAY)
            return;

        m_Array[key] = new json::JSON(value);
    }

    void JSON::Replace(std::string key, json::JSON value)
    {
        if (m_Type != json::Type::OBJECT)
            return;

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            // Free the memory allocated for the JSON object
            m_Object[key]->Destroy();
            m_Object[key] = new json::JSON(value);
        }
    }

    void JSON::Replace(int key, json::JSON value)
    {
        if (m_Type != json::Type::ARRAY)
            return;

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            // Free the memory allocated for the JSON object
            m_Array[key]->Destroy();
            m_Array[key] = new json::JSON(value); // reassign
        }
    }

    json::JSON JSON::Get(const std::string &key) const
    {
        if (m_Type != json::Type::OBJECT)
        {
            throw json::Exception("Can't Retrieve from a Non-OBJECT Type!", Error::NON_OBJECT_TYPE);
        }

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            return *(iter->second);
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    json::JSON JSON::Get(int key) const
    {
        if (m_Type != json::Type::ARRAY)
        {
            throw json::Exception("Can't Retrieve from a Non-ARRAY Type!", Error::NON_ARRAY_TYPE);
        }

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            return *(iter->second);
        }
        else
        {
            char str[12];
            sprintf(str, "%i", key);
            throw json::Exception("Index [" + std::string(str) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    void JSON::Get(const std::string &key, json::JSON &value) const
    {
        if (m_Type != json::Type::OBJECT)
        {
            throw json::Exception("Can't Retrieve from a Non-OBJECT Type!", Error::NON_OBJECT_TYPE);
        }

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            value = *(iter->second);
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    void JSON::Get(int key, json::JSON &value) const
    {
        if (m_Type != json::Type::ARRAY)
        {
            throw json::Exception("Can't Retrieve from a Non-ARRAY Type!", Error::NON_ARRAY_TYPE);
        }

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            value = *(iter->second);
        }
        else
        {
            char str[12];
            sprintf(str, "%i", key);
            throw json::Exception("Index [" + std::string(str) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    // Fixed the bug: Changed the condition to check for OBJECT type instead of ARRAY type
    void JSON::Delete(std::string key)
    {
        if (m_Type != json::Type::OBJECT)
            return;

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            m_Object[key]->Destroy(); // Free the memory allocated for the JSON object
            m_Object.erase(iter);     // Remove the key-value pair from the object
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    };

    void JSON::Delete(int key)
    {
        if (m_Type != json::Type::ARRAY)
            return;

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            m_Array[key]->Destroy(); // Free the memory allocated for the JSON object
            m_Array.erase(iter);     // Remove the key-value pair from the object
        }
        else
        {
            char *str;
            sprintf(str, "%i", key);
            throw json::Exception("Index [" + std::string(str) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    };

    json::JSON JSON::Detach(std::string key)
    {
        if (m_Type != json::Type::OBJECT)
        {
            throw json::Exception("Can't Detach from a Non-OBJECT Type!", Error::NON_OBJECT_TYPE);
        }

        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            json::JSON detached = new json::JSON(*(iter->second));

            m_Object[key]->Destroy(); // Free the memory allocated for the JSON object
            m_Object.erase(iter);     // Remove the key-value pair from the object

            return detached;
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    json::JSON JSON::Detach(int key)
    {
        if (m_Type != json::Type::ARRAY)
        {
            throw json::Exception("Can't Detach from a Non-ARRAY Type!", Error::NON_ARRAY_TYPE);
        }

        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            json::JSON detached = new json::JSON(*(iter->second));

            m_Array[key]->Destroy(); // Free the memory allocated for the JSON object
            m_Array.erase(iter);     // Remove the key-value pair from the object

            return detached;
        }
        else
        {
            char *str;
            sprintf(str, "%i", key);
            throw json::Exception("Index [" + std::string(str) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    };

    /**
     * @brief Gets a string representation of a value in the JSON object or array.
     * @param key The key or index to get the value from.
     * @return The string representation of the value.
     * @throws json::Exception if the key or index is not found.
     * @code
     * json::JSON jsonObject(json::Type::OBJECT);
     * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
     * std::string nameStr = jsonObject("name");
     * @endcode
     */
    std::string JSON::operator()(const std::string &key) const
    {
        auto iter = m_Object.find(key);

        if (iter != m_Object.end())
        {
            json::JSON *pJSON = NULL;
            pJSON = m_Object[key];

            if (pJSON == NULL)
            {
                throw json::Exception("[" + key + "] : Is Missing a Value!", Error::VALUE_NOT_FOUND);
            }
            else
            {
                return pJSON->String();
            }
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    /**
     * @brief Gets a string representation of a value in the JSON array.
     * @param key The key or index to get the value from.
     * @return The string representation of the value.
     * @throws json::Exception if the key or index is not found.
     * @code
     * json::JSON jsonArray(json::Type::ARRAY);
     * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
     * std::string nameStr = jsonArray(0);
     * @endcode
     */
    std::string JSON::operator()(const int &key) const
    {
        auto iter = m_Array.find(key);

        if (iter != m_Array.end())
        {

            json::JSON *pJSON = NULL;
            pJSON = m_Array[key];

            if (pJSON == NULL)
            {
                char *str;
                sprintf(str, "%i", key);
                throw json::Exception("Index [" + std::string(str) + "]: Is Missing a Value!", Error::MISSING_VALUE);
            }
            else
            {
                return pJSON->String();
            }
        }
        else
        {
            char *str;
            sprintf(str, "%i", key);
            throw json::Exception("Index [" + std::string(str) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    /**
     * @brief Accesses a value in the JSON object.
     * @param key The key to access.
     * @return Reference to the accessed value.
     * @throws json::Exception if the key is not found or the JSON type is not an object.
     * @code
     * json::JSON jsonObject(json::Type::OBJECT);
     * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
     * json::JSON &name = jsonObject["name"];
     * @endcode
     */
    json::JSON &JSON::operator[](const std::string &key) const
    {
        auto iter = m_Object.find(key);
        if (iter != m_Object.end())
        {
            return *(iter->second);
        }
        else
        {
            throw json::Exception("[" + key + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    /**
     * @brief Accesses a value in the JSON array.
     * @param key The index to access.
     * @return Reference to the accessed value.
     * @throws json::Exception if the index is not found or the JSON type is not an array.
     * @code
     * json::JSON jsonArray(json::Type::ARRAY);
     * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
     * json::JSON &name = jsonArray[0];
     * @endcode
     */
    json::JSON &JSON::operator[](const int &key) const
    {
        auto iter = m_Array.find(key);
        if (iter != m_Array.end())
        {
            return *(iter->second);
        }
        else
        {
            throw json::Exception("Index [" + std::to_string(key) + "]: Is Not a Valid key!", Error::KEY_NOT_FOUND);
        }
    }

    json::JSON &JSON::operator=(const JSON &json)
    {
        if (this != &json)
        {
            // Free existing resources
            Destroy();

            // Copy the type, value, array, and object from the source JSON object
            m_Type = json.m_Type;
            m_Value = json.m_Value;

            // Deep copy the array elements
            for (const auto &[key, value] : json.m_Array)
            {
                m_Array[key] = new JSON(*value);
            }

            // Deep copy the object elements
            for (const auto &[key, value] : json.m_Object)
            {
                m_Object[key] = new JSON(*value);
            }
        }
        return *this;
    }

    JSON &JSON::operator=(JSON &&json)
    {
        if (this != &json)
        {
            // Free existing resources
            Destroy();

            // Move the type, value, array, and object from the source JSON object
            m_Type = std::move(json.m_Type);
            m_Value = std::move(json.m_Value);
            m_Array = std::move(json.m_Array);
            m_Object = std::move(json.m_Object);

            // Reset the source JSON object
            json.m_Type = json::Type::UNKNOWN;
            json.m_Value = std::monostate{};
            json.m_Array.clear();
            json.m_Object.clear();
        }
        return *this;
    }

    bool JSON::operator==(const JSON &json) const
    {
        return this->String() == json.String();
    }

    bool JSON::operator!=(const JSON &json) const
    {
        return !(this->operator==(json));
        // >
        // <
        // <=
        // >=
        // <<
    }

    JSON::operator double()
    {
        if (m_Type != json::Type::DOUBLE)
        {
            throw json::Exception("Can't Cast from a Non-DOUBLE Type!", Error::WRONG_TYPE_CAST);
        }

        return std::get<double>(m_Value);
    };

    JSON::operator int()
    {
        if (m_Type != json::Type::INTEGER)
        {
            throw json::Exception("Can't Cast from a Non-INTEGER Type!", Error::WRONG_TYPE_CAST);
        }

        return std::get<int>(m_Value);
    };

    JSON::operator std::string()
    {
        if (m_Type != json::Type::STRING)
        {
            throw json::Exception("Can't Cast from a Non-STRING Type!", Error::WRONG_TYPE_CAST);
        }

        return std::get<std::string>(m_Value);
    };

    JSON::operator bool()
    {
        if (m_Type != json::Type::BOOLEAN)
        {
            throw json::Exception("Can't Cast from a Non-BOOLEAN Type!", Error::WRONG_TYPE_CAST);
        }

        return std::get<bool>(m_Value);
    };

    void JSON::Destroy()
    {
        if (m_Type == json::Type::ARRAY)
        {
            // Iterate through the array elements
            for (auto &[key, value] : m_Array)
            {
                // If the element is not null, delete it
                if (value != nullptr)
                {
                    value->Destroy();
                    delete value;
                    value = nullptr;
                }
            }
            // Clear the array
            m_Array.clear();
        }
        else if (m_Type == json::Type::OBJECT)
        {
            // Iterate through the object elements
            for (auto &[key, value] : m_Object)
            {
                // If the element is not null, delete it
                if (value != nullptr)
                {
                    value->Destroy();
                    delete value;
                    value = nullptr;
                }
            }
            // Clear the object
            m_Object.clear();
        }
        // Reset the variant
        m_Value = std::variant<std::monostate, std::string, int, double, bool>();
        m_Type = json::Type::UNKNOWN;
    }

#pragma endregion // json

#pragma region exception

    Exception::Exception()
    {
        m_ErrType = json::Error::UNKNOWN;
        m_Msg = std::string("(") + GetErrName(json::Error::UNKNOWN) + std::string(") -> ") + std::string("UNKNOWN ERROR TYPE");
    };

    Exception::Exception(json::Error errorType)
    {
        m_ErrType = errorType;
        m_Msg = std::string("(") + GetErrName(errorType) + std::string(") -> ") + std::string("ERROR MESSAGE EMPTY");
    };

    Exception::Exception(const std::string &message, json::Error errorType)
    {
        m_ErrType = errorType;
        m_Msg = std::string("(") + GetErrName(errorType) + std::string(") -> ") + message;
    };

    const char *Exception::what() const noexcept
    {
        return m_Msg.c_str();
    };

    json::Error Exception::GetErrType() const noexcept
    {
        return m_ErrType;
    };

    const char *Exception::GetErrName(json::Error error) const noexcept
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

            CASEFY_ERROR(Error::INVALID_BOOL);
            CASEFY_ERROR(Error::INVALID_NULL);
            CASEFY_ERROR(Error::INVALID_NUMBER);
            CASEFY_ERROR(Error::INVALID_OBJECT);
            CASEFY_ERROR(Error::INVALID_ARRAY);
            CASEFY_ERROR(Error::INVALID_STRING);

            CASEFY_ERROR(Error::KEY_ALREADY_EXISTS);
            CASEFY_ERROR(Error::VALUE_CANT_BE_NULL);

            CASEFY_ERROR(Error::WRONG_TYPE_CAST);
        }

        return name.c_str();
    };

#pragma endregion // exception

#pragma region myjson

    /**
     * @brief Converts a JSON object to a string representation.
     * @param json The JSON object to convert.
     * @param ensure_ascii If true, ensures that the output is ASCII-encoded.
     * @return The string representation of the JSON object.
     * @code
     * json::JSON jsonObject(json::Type::OBJECT);
     * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
     * std::string jsonString = json::dump(jsonObject);
     * @endcode
     */
    std::string dump(const json::JSON &json, bool ensure_ascii)
    {
        std::stringstream ss;
        dump_helper(json, ss, ensure_ascii);
        return ss.str();
    }

    /**
     * @brief Helper function to recursively convert a JSON object to a string representation.
     * @param json The JSON object to convert.
     * @param ss The stringstream to write the output to.
     * @param ensure_ascii If true, ensures that the output is ASCII-encoded.
     */
    void dump_helper(const json::JSON &json, std::stringstream &ss, bool ensure_ascii)
    {
        switch (json.Type())
        {
        case json::Type::NIL:
            ss << "null";
            break;
        case json::Type::BOOLEAN:
            ss << (std::get<bool>(json.m_Value) ? "true" : "false");
            break;
        case json::Type::INTEGER:
            ss << std::get<int>(json.m_Value);
            break;
        case json::Type::DOUBLE:
            ss << std::get<double>(json.m_Value);
            break;
        case json::Type::STRING:
            ss << "\"" << std::get<std::string>(json.m_Value) << "\"";
            break;
        case json::Type::ARRAY:
            ss << "[";
            for (auto it = json.m_Array.begin(); it != json.m_Array.end(); ++it)
            {
                if (it != json.m_Array.begin())
                {
                    ss << ",";
                }
                dump_helper(*it->second, ss, ensure_ascii);
            }
            ss << "]";
            break;
        case json::Type::OBJECT:
            ss << "{";
            for (auto it = json.m_Object.begin(); it != json.m_Object.end(); ++it)
            {
                if (it != json.m_Object.begin())
                {
                    ss << ",";
                }
                ss << "\"" << it->first << "\"" << ":";
                dump_helper(*it->second, ss, ensure_ascii);
            }
            ss << "}";
            break;
        default:
            throw json::Exception("Unknown JSON type", json::Error::UNKNOWN);
        }
    }

    /**
     * @brief Loads a JSON object from a string.
     * @param json The JSON string to load.
     * @param encoding The character encoding of the JSON string (optional).
     * @return The loaded JSON object.
     * @throws json::Exception if the JSON string is invalid.
     * @code
     * std::string jsonString = "{\"name\": \"John\", \"age\": 30}";
     * json::JSON jsonObject = json::load(jsonString);
     * @endcode
     */
    json::JSON load(const std::string &json, char *encoding)
    {
        size_t index = 0;
        return parse_value(json, index);
    }

    /**
     * @brief Prints the JSON object to the standard output.
     * @param json The JSON object to print.
     * @param indent If true, prints the JSON object with indentation.
     * @code
     * json::JSON jsonObject(json::Type::OBJECT);
     * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
     * json::print(jsonObject, true);
     * @endcode
     */
    void print(json::JSON json, bool indent)
    {
        std::string jsonString = dump(json);

        if (indent)
        {
            std::stringstream ss(jsonString);
            std::string line;
            int indentLevel = 0;
            while (std::getline(ss, line))
            {
                if (line.find('}') != std::string::npos || line.find(']') != std::string::npos)
                {
                    indentLevel--;
                }
                for (int i = 0; i < indentLevel; ++i)
                {
                    std::cout << "    "; // 4 spaces for each indent level
                }
                std::cout << line << std::endl;
                if (line.find('{') != std::string::npos || line.find('[') != std::string::npos)
                {
                    indentLevel++;
                }
            }
        }
        else
        {
            std::cout << jsonString << std::endl;
        }
    }

    /**
     * @brief Overloads the stream insertion operator to output a JSON object to an output stream.
     * @param cout The output stream.
     * @param json The JSON object to output.
     * @return The output stream.
     * @code
     * json::JSON jsonObject(json::Type::OBJECT);
     * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
     * std::cout << jsonObject << std::endl;
     * @endcode
     */
    std::ostream &operator<<(std::ostream &cout, const json::JSON &json)
    {
        cout << json.String();
        return cout;
    }

#pragma endregion // myjson

#pragma region dumpload

    std::ostream &operator<<(std::ostream &cout, json::JSON &json)
    {
        cout << json.String();
        return cout;
    };

    /**
     * @brief Parses a JSON value from a string.
     * @param json The JSON string to parse.
     * @param index The current position in the string.
     * @return The parsed JSON value.
     * @throws json::Exception if the JSON is invalid.
     */
    json::JSON parse_value(const std::string &json, size_t &index)
    {
        skip_whitespace(json, index);

        if (index >= json.size())
        {
            throw json::Exception("Unexpected end of input", json::Error::INVALID_OBJECT);
        }

        char ch = json[index];

        if (ch == 'n')
        {
            return parse_null(json, index);
        }
        else if (ch == 't' || ch == 'f')
        {
            return parse_boolean(json, index);
        }
        else if (ch == '-' || std::isdigit(ch))
        {
            return parse_number(json, index);
        }
        else if (ch == '"')
        {
            return parse_string(json, index);
        }
        else if (ch == '[')
        {
            return parse_array(json, index);
        }
        else if (ch == '{')
        {
            return parse_object(json, index);
        }
        else
        {
            throw json::Exception("Invalid character in JSON", json::Error::INVALID_OBJECT);
        }
    }

    /**
     * @brief Skips whitespace characters in the JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     */
    void skip_whitespace(const std::string &json, size_t &index)
    {
        while (index < json.size() && std::isspace(json[index]))
        {
            ++index;
        }
    }

    /**
     * @brief Parses a null value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a null value.
     * @throws json::Exception if the null value is invalid.
     */
    json::JSON parse_null(const std::string &json, size_t &index)
    {
        if (json.substr(index, 4) == "null")
        {
            index += 4;
            return json::JSON(json::Type::NIL);
        }
        throw json::Exception("Invalid null value", json::Error::INVALID_NULL);
    }

    /**
     * @brief Parses a boolean value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a boolean value.
     * @throws json::Exception if the boolean value is invalid.
     */
    json::JSON parse_boolean(const std::string &json, size_t &index)
    {
        if (json.substr(index, 4) == "true")
        {
            index += 4;
            return json::JSON(json::Type::BOOLEAN, true);
        }
        else if (json.substr(index, 5) == "false")
        {
            index += 5;
            return json::JSON(json::Type::BOOLEAN, false);
        }
        throw json::Exception("Invalid boolean value", json::Error::INVALID_BOOL);
    }

    /**
     * @brief Parses a number (integer or double) from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a number.
     * @throws json::Exception if the number is invalid.
     */
    json::JSON parse_number(const std::string &json, size_t &index)
    {
        size_t start = index;
        if (json[index] == '-')
        {
            ++index;
        }
        while (index < json.size() && std::isdigit(json[index]))
        {
            ++index;
        }
        if (index < json.size() && json[index] == '.')
        {
            ++index;
            while (index < json.size() && std::isdigit(json[index]))
            {
                ++index;
            }
            return json::JSON(json::Type::DOUBLE, std::stod(json.substr(start, index - start)));
        }
        return json::JSON(json::Type::INTEGER, std::stoi(json.substr(start, index - start)));
    }

    /**
     * @brief Parses a string value from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing a string.
     * @throws json::Exception if the string is invalid.
     */
    json::JSON parse_string(const std::string &json, size_t &index)
    {
        ++index; // Skip the opening quote
        size_t start = index;
        while (index < json.size() && json[index] != '"')
        {
            if (json[index] == '\\')
            {
                ++index; // Skip the escape character
            }
            ++index;
        }
        if (index >= json.size())
        {
            throw json::Exception("Unterminated string", json::Error::INVALID_STRING);
        }
        std::string value = json.substr(start, index - start);
        ++index; // Skip the closing quote
        return json::JSON(json::Type::STRING, value);
    }

    std::string get_parse_string(const std::string &json, size_t &index)
    {
        ++index; // Skip the opening quote
        size_t start = index;
        while (index < json.size() && json[index] != '"')
        {
            if (json[index] == '\\')
            {
                ++index; // Skip the escape character
            }
            ++index;
        }
        if (index >= json.size())
        {
            throw json::Exception("Unterminated string", json::Error::INVALID_STRING);
        }
        std::string value = json.substr(start, index - start);
        ++index; // Skip the closing quote
        return value;
    }

    /**
     * @brief Parses an array from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing an array.
     * @throws json::Exception if the array is invalid.
     */
    json::JSON parse_array(const std::string &json, size_t &index)
    {
        ++index; // Skip the opening bracket
        json::JSON array(json::Type::ARRAY);
        skip_whitespace(json, index);
        if (json[index] == ']')
        {
            ++index; // Skip the closing bracket
            return array;
        }
        // int key = -1;
        while (index < json.size())
        {
            // array.m_Array[key] = new json::JSON(parse_value(json, index));

            array.m_Array[array.m_Array.size()] = new json::JSON(parse_value(json, index));
            skip_whitespace(json, index);
            if (json[index] == ']')
            {
                ++index; // Skip the closing bracket
                return array;
            }
            if (json[index] != ',')
            {
                throw json::Exception("Expected ',' in array", json::Error::MISSING_SEPARATOR);
            }
            ++index; // Skip the comma
            skip_whitespace(json, index);
        }
        throw json::Exception("Unterminated array", json::Error::INVALID_ARRAY);
    }

    /**
     * @brief Parses an object from a JSON string.
     * @param json The JSON string.
     * @param index The current position in the string.
     * @return A JSON object representing an object.
     * @throws json::Exception if the object is invalid.
     */
    json::JSON parse_object(const std::string &json, size_t &index)
    {
        ++index; // Skip the opening brace
        json::JSON object(json::Type::OBJECT);
        skip_whitespace(json, index);
        if (json[index] == '}')
        {
            ++index; // Skip the closing brace
            return object;
        }
        while (index < json.size())
        {
            std::string key = get_parse_string(json, index);
            skip_whitespace(json, index);
            if (json[index] != ':')
            {
                throw json::Exception("Expected ':' in object", json::Error::MISSING_VALUE);
            }
            ++index; // Skip the colon
            skip_whitespace(json, index);
            object.m_Object[key] = new json::JSON(parse_value(json, index));
            skip_whitespace(json, index);
            if (json[index] == '}')
            {
                ++index; // Skip the closing brace
                return object;
            }
            if (json[index] != ',')
            {
                throw json::Exception("Expected ',' in object", json::Error::MISSING_SEPARATOR);
            }
            ++index; // Skip the comma
            skip_whitespace(json, index);
        }
        throw json::Exception("Unterminated object", json::Error::INVALID_OBJECT);
    }

#pragma endregion // dumpload

} // namespace json
