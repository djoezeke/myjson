#ifndef MY_JSON_H
#define MY_JSON_H

#include <unordered_map>
#include <vector>
#include <variant>
#include <memory>
#include <string>
#include <ostream>

#define CASEFY_ERROR(value) \
    case value:             \
        name = #value;      \
        break

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

#endif // MY_JSON_H