#ifndef MY_JSON_H
#define MY_JSON_H

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <variant>

/**
 * @brief Macro to convert an error value to its string representation.
 *
 * This macro is used in a switch-case statement to return the string representation
 * of an error value.
 *
 * @param value The error value to convert to a string.
 */
#define CASEFY_ERROR(value) \
    case value:             \
        name = #value;      \
        break

namespace json
{

    /**
     * @brief JSON exception type for faster exception processing.
     */
    enum class Error
    {
        UNKNOWN = -1,       //!< An unknown error occurred.
        MISSING_SEPARATOR,  //!< Occurs if a ',' is missing before a key.
        MISSING_VALUE,      //!< Occurs if ':' is missing before value.
        KEY_NOT_FOUND,      //!< Occurs if a key is not found.
        VALUE_NOT_FOUND,    //!< Occurs if a key in JSON object is NULL.
        NON_BOOL_TYPE,      //!< Occurs if a bool is expected but not found.
        NON_NULL_TYPE,      //!< Occurs if a null type is expected but not found.
        NON_NUMBER_TYPE,    //!< Occurs if a number is expected but not found.
        NON_OBJECT_TYPE,    //!< Occurs if an object is expected but not found.
        NON_ARRAY_TYPE,     //!< Occurs if an array is expected but not found.
        NON_STRING_TYPE,    //!< Occurs if a string is expected but not found.
        INVALID_OBJECT,     //!< Occurs if a JSON object is not valid.
        INVALID_ARRAY,      //!< Occurs if a JSON array is not valid.
        INVALID_STRING,     //!< Occurs if a JSON string is not valid.
        INVALID_BOOL,       //!< Occurs if a JSON bool is not valid.
        INVALID_NUMBER,     //!< Occurs if a JSON number is not valid.
        INVALID_NULL,       //!< Occurs if a JSON null is not valid.
        KEY_ALREADY_EXISTS, //!< Occurs if a key already exists.
        VALUE_CANT_BE_NULL, //!< Occurs if a value can't be null.
        WRONG_TYPE_CAST     //!< Occurs if a type cast is invalid.
    };

    /**
     * @brief JSON value types.
     */
    typedef enum class Type
    {
        UNKNOWN = -1, //!< An unknown or uninitialized type.
        NIL,          //!< Represents a null value.
        OBJECT,       //!< Represents a JSON object.
        ARRAY,        //!< Represents a JSON array.
        BOOLEAN,      //!< Represents a boolean value.
        INTEGER,      //!< Represents an integer value.
        DOUBLE,       //!< Represents a double (floating-point) value.
        STRING        //!< Represents a string value.
    } Type;

#pragma region json

    /**
     * @brief Represents a JSON value.
     */
    class JSON
    {
    public:
        /**
         * @brief Default constructor.
         * @code
         * json::JSON jsonObject;
         * @endcode
         */
        JSON();

        /**
         * @brief Constructs a JSON value of a specific type.
         * @param type The type of the JSON value.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * @endcode
         */
        JSON(json::Type type);

        /**
         * @brief Constructs a JSON value of a specific type.
         * @param type The type of the JSON value.
         * @param value The value to initialize the JSON object with.
         * @code
         * json::JSON jsonString(json::Type::STRING, "Hello, World!");
         * @endcode
         */
        JSON(json::Type type, std::variant<std::monostate, std::string, int, double, bool> value);

        /**
         * @brief Copy constructor.
         * @param other Pointer to the JSON object to copy.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2(&jsonObject1);
         * @endcode
         */
        JSON(const JSON *other);

        /**
         * @brief Copy constructor.
         * @param other The JSON object to copy.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2(jsonObject1);
         * @endcode
         */
        JSON(const JSON &other);

        /**
         * @brief Move constructor.
         * @param json The JSON object to move.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2(std::move(jsonObject1));
         * @endcode
         */
        JSON(JSON &&json);

        /**
         * @brief Destructor.
         * Frees any allocated memory.
         * @code
         * {
         *     json::JSON jsonObject(json::Type::OBJECT);
         * } // jsonObject is destroyed here
         * @endcode
         */
        ~JSON();

        /**
         * @brief Checks if the JSON value is an array.
         * @return True if the JSON value is an array, false otherwise.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * bool isArray = jsonArray.IsArray();
         * @endcode
         */
        bool IsArray() const;

        /**
         * @brief Checks if the JSON value is an object.
         * @return True if the JSON value is an object, false otherwise.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * bool isObject = jsonObject.IsObject();
         * @endcode
         */
        bool IsObject() const;

        /**
         * @brief Checks if the JSON value is a number.
         * @return True if the JSON value is a number, false otherwise.
         * @code
         * json::JSON jsonNumber(json::Type::INTEGER, 42);
         * bool isNumber = jsonNumber.IsNumber();
         * @endcode
         */
        bool IsNumber() const;

        /**
         * @brief Checks if the JSON value is a boolean.
         * @return True if the JSON value is a boolean, false otherwise.
         * @code
         * json::JSON jsonBool(json::Type::BOOLEAN, true);
         * bool isBool = jsonBool.IsBool();
         * @endcode
         */
        bool IsBool() const;

        /**
         * @brief Checks if the JSON value is null.
         * @return True if the JSON value is null, false otherwise.
         * @code
         * json::JSON jsonNull(json::Type::NIL);
         * bool isNull = jsonNull.IsNil();
         * @endcode
         */
        bool IsNil() const;

        /**
         * @brief Checks if the JSON value is empty.
         * @return True if the JSON value is empty, false otherwise.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * bool isEmpty = jsonObject.Empty();
         * @endcode
         */
        bool Empty() const;

        /**
         * @brief Converts the JSON value to a string.
         * @return The JSON value as a string.
         * @code
         * json::JSON jsonString(json::Type::STRING, "Hello, World!");
         * std::string str = jsonString.String();
         * @endcode
         */
        std::string String() const;

        /**
         * @brief Gets the type of the JSON value.
         * @return The type of the JSON value.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * json::Type type = jsonObject.Type();
         * @endcode
         */
        json::Type Type() const;

        /**
         * @brief Gets the keys of the JSON object or array.
         * @return Vector of all keys or empty vector if not object or array type.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * std::vector<std::string> keys = jsonObject.Keys();
         * @endcode
         */
        std::vector<std::string> Keys() const;

        // Operators

        /**
         * @brief Copy assignment operator.
         * Copies the contents of the given JSON object to this JSON object.
         * @param json The JSON object to copy.
         * @return A reference to this JSON object.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2 = jsonObject1;
         * @endcode
         */
        JSON &operator=(const JSON &other);

        /**
         * @brief Move assignment operator.
         * Moves the contents of the given JSON object to this JSON object.
         * @param json The JSON object to move.
         * @return A reference to this JSON object.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2 = std::move(jsonObject1);
         * @endcode
         */
        JSON &operator=(JSON &&other);

        /**
         * @brief Equality operator.
         * @param json The JSON object to compare.
         * @return True if the JSON objects are equal, false otherwise.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2(json::Type::OBJECT);
         * bool isEqual = (jsonObject1 == jsonObject2);
         * @endcode
         */
        bool operator==(const JSON &other) const;

        /**
         * @brief None Equality operator.
         * @param json The JSON object to compare.
         * @return True if the JSON objects are  not equal, false otherwise.
         * @code
         * json::JSON jsonObject1(json::Type::OBJECT);
         * json::JSON jsonObject2(json::Type::OBJECT);
         * bool isNotEqual = (jsonObject1 != jsonObject2);
         * @endcode
         */
        bool operator!=(const JSON &other) const;

        operator double();
        operator int();
        operator std::string();
        operator bool();

    public:
        // Methods for ordinary JSON objects or JSON arrays

        /**
         * @brief Gets the type of the value associated with a key.
         * @param key The key to look up.
         * @return The type of the value associated with the key.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * json::Type type = jsonObject.ValueType("name");
         * @endcode
         */
        json::Type ValueType(const std::string &key) const;

        /**
         * @brief Gets the type of the value at an index.
         * @param key The index to look up.
         * @return The type of the value at the index.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * json::Type type = jsonArray.ValueType(0);
         * @endcode
         */
        json::Type ValueType(int key) const;

        /**
         * @brief Checks if a key exists in the JSON object.
         * @param key The key to check.
         * @return True if the key exists, false otherwise.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * bool hasKey = jsonObject.HasKey("name");
         * @endcode
         */
        bool HasKey(const std::string &key) const;

        /**
         * @brief Checks if an index exists in the JSON array.
         * @param key The index to check.
         * @return True if the index exists, false otherwise.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * bool hasIndex = jsonArray.HasKey(0);
         * @endcode
         */
        bool HasKey(int key) const;

        /**
         * @brief Adds a value to the JSON object.
         * @param key The key to add the value to.
         * @param value The value to add.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * @endcode
         */
        void Add(std::string key, json::JSON value);

        /**
         * @brief Adds a value to the JSON array.
         * @param key The index to add the value to.
         * @param value The value to add.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * @endcode
         */
        void Add(int key, json::JSON value);

        /**
         * @brief Replaces a value in the JSON object.
         * @param key The key to replace the value for.
         * @param value The new value.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * jsonObject.Replace("name", json::JSON(json::Type::STRING, "Doe"));
         * @endcode
         */
        void Replace(std::string key, json::JSON value);

        /**
         * @brief Replaces a value in the JSON array.
         * @param key The index to replace the value at.
         * @param value The new value.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * jsonArray.Replace(0, json::JSON(json::Type::STRING, "Doe"));
         * @endcode
         */
        void Replace(int key, json::JSON value);

        /**
         * @brief Retrieves the value associated with the given key from the JSON object.
         * @param key The key of the value to retrieve.
         * @return The JSON value associated with the key.
         * @throws json::Exception if the key is not found or the JSON type is not an object.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * json::JSON name = jsonObject.Get("name");
         * @endcode
         */
        json::JSON Get(const std::string &key) const;

        /**
         * @brief Retrieves the value at the given index from the JSON array.
         * @param key The index of the value to retrieve.
         * @return The JSON value at the specified index.
         * @throws json::Exception if the index is not found or the JSON type is not an array.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * json::JSON value = jsonArray.Get(0);
         * @endcode
         */
        json::JSON Get(int key) const;

        /**
         * @brief Retrieves the value associated with the given key from the JSON object and stores it in the provided reference.
         * @param key The key of the value to retrieve.
         * @param value Reference to store the retrieved JSON value.
         * @throws json::Exception if the key is not found or the JSON type is not an object.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * json::JSON name;
         * jsonObject.Get("name", name);
         * @endcode
         */
        void Get(const std::string &key, json::JSON &value) const;

        /**
         * @brief Retrieves the value at the given index from the JSON array and stores it in the provided reference.
         * @param key The index of the value to retrieve.
         * @param value Reference to store the retrieved JSON value.
         * @throws json::Exception if the index is not found or the JSON type is not an array.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * json::JSON value;
         * jsonArray.Get(0, value);
         * @endcode
         */
        void Get(int key, json::JSON &value) const;

        /**
         * @brief Deletes a value from the JSON object.
         * @param key The key or index to delete the value from.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * jsonObject.Delete("name");
         * @endcode
         */
        void Delete(std::string key);

        /**
         * @brief Deletes a value from the JSON array.
         * @param key The key or index to delete the value from.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * jsonArray.Delete(0);
         * @endcode
         */
        void Delete(int key);

        /**
         * @brief Detaches the JSON object associated with the given key from the current JSON object.
         * This function removes the key-value pair from the JSON object and returns the detached JSON object.
         * @param key The key of the JSON object to detach.
         * @return The detached JSON object.
         * @throws json::Exception if the key is not found or the JSON type is not an object.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * json::JSON detached = jsonObject.Detach("name");
         * @endcode
         */
        json::JSON Detach(std::string key);

        /**
         * @brief Detaches the JSON object associated with the given index from the current JSON array.
         * This function removes the key-value pair from the JSON array and returns the detached JSON object.
         * @param key The index of the JSON object to detach.
         * @return The detached JSON object.
         * @throws json::Exception if the index is not found or the JSON type is not an array.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * json::JSON detached = jsonArray.Detach(0);
         * @endcode
         */
        json::JSON Detach(int key);

        // Operators
        /**
         * @brief Accesses a value in the JSON object.
         * @param key The key or index to access.
         * @return Reference to the accessed value.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * json::JSON &name = jsonObject["name"];
         * @endcode
         */
        JSON &operator[](const std::string &key) const;

        /**
         * @brief Accesses a value in the JSON array.
         * @param key The key or index to access.
         * @return Reference to the accessed value.
         * @code
         * json::JSON jsonArray(json::Type::ARRAY);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * json::JSON &name = jsonArray[0];
         * @endcode
         */

        JSON &operator[](const int &key) const;

        /**
         * @brief Gets a string representation of a value in the JSON object or array.
         * @param key The key or index to get the value from.
         * @return The string representation of the value.
         * @code
         * json::JSON jsonObject(json::Type::OBJECT);
         * jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
         * std::string nameStr = jsonObject("name");
         * @endcode
         */
        std::string operator()(const std::string &key) const;

        /**
         * @brief Gets a string representation of a value in the JSON array.
         * @param key The key or index to get the value from.
         * @return The string representation of the value.
         * @code
         * json::JSON jsonArray(json::Type::OBJECT);
         * jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
         * std::string nameStr = jsonArray(0);
         * @endcode
         */
        std::string operator()(const int &key) const;

    private:
        /**
         * @brief Destroys the JSON object, freeing any allocated memory.
         */
        void Destroy();

        friend json::JSON parse_array(const std::string &json, size_t &index);
        friend json::JSON parse_object(const std::string &json, size_t &index);

    private:
        json::Type m_Type; //!< The type of the JSON value.

        std::variant<std::monostate, std::string, int, double, bool> m_Value; //!< The value of the JSON object.

        mutable std::unordered_map<unsigned int, JSON *> m_Array; //!< The array elements.

        mutable std::unordered_map<std::string, JSON *> m_Object; //!< The object elements.
    };

#pragma endregion // json

#pragma region exception

    /**
     * @brief Exception class for JSON-related errors.
     */
    class Exception : public std::exception
    {
    public:
        /**
         * @brief Default constructor.
         */
        Exception();

        /**
         * @brief Constructs an exception with a specific error type.
         * @param type The type of the error.
         */
        Exception(json::Error type);

        /**
         * @brief Constructs an exception with a specific message and error type.
         * @param message The error message.
         * @param type The type of the error.
         */
        Exception(const std::string &message, json::Error type);

        /**
         * @brief Gets the error message.
         * @return The error message.
         */
        const char *what() const noexcept override;

        /**
         * @brief Gets the error type.
         * @return The error type.
         */
        json::Error GetErrType() const noexcept;

        /**
         * @brief Gets the name of the error type.
         * @param error The error type.
         * @return The name of the error type.
         */
        const char *GetErrName(json::Error error) const noexcept;

    private:
        void debug(char *file, int line);

    private:
        mutable std::string m_Msg; //!< The error message.
        json::Error m_ErrType;     //!< The error type.
    };

#pragma endregion // exception

#pragma region myjson

    std::ostream &operator<<(std::ostream &cout, json::JSON &json);

    std::string dump(json::JSON &json, bool ensure_ascii = true);

    /**
     * @brief Loads a JSON object from a string.
     *
     * This function parses the given JSON string and returns the corresponding JSON object.
     *
     * @param json The JSON string to load.
     * @param encoding The character encoding of the JSON string.
     * @return The loaded JSON object.
     */
    json::JSON load(const std::string &json, char *encoding = nullptr);

    /**
     * @brief Prints the JSON object to the standard output.
     *
     * This function prints the given JSON object to the standard output (console).
     *
     * @param json The JSON object to print.
     * @param indent If true, prints the JSON object with indentation.
     */
    void print(json::JSON json, bool indent = true);

    /**
     * @brief Creates a new JSON object of the specified type.
     *
     * This function creates and returns a new JSON object of the specified type.
     * It initializes the JSON object based on the provided type.
     *
     * @tparam T The type of the JSON object to create.
     * @return A new JSON object of the specified type.
     */
    template <json::Type T>
    json::JSON create();

#pragma endregion // json

} // namespace json

#endif // MY_JSON_H