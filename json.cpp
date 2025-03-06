#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Define JSON value types
enum class JsonType
{
    STRING,
    NUMBER,
    BOOLEAN,
    ARRAY,
    OBJECT
};

// Forward declaration of JsonValue
class JsonValue;

// Define a JSON key-value pair for objects
using JsonKeyValuePair = std::pair<std::string, std::shared_ptr<JsonValue>>;

// Define a JSON value class
class JsonValue
{
public:
    JsonType type;

    // Constructors for different types of JSON values
    JsonValue(const std::string &value) : type(JsonType::STRING), string_value(value) {}
    JsonValue(double value) : type(JsonType::NUMBER), number_value(value) {}
    JsonValue(bool value) : type(JsonType::BOOLEAN), bool_value(value) {}
    JsonValue() : type(JsonType::ARRAY) {}
    JsonValue(std::unordered_map<std::string, std::shared_ptr<JsonValue>> value) : type(JsonType::OBJECT), object_value(value) {}

    // Add an item to a JSON array
    void add_to_array(std::shared_ptr<JsonValue> item)
    {
        if (type != JsonType::ARRAY)
            return;
        array_value.push_back(item);
    }

    // Add a key-value pair to a JSON object
    void add_to_object(const std::string &key, std::shared_ptr<JsonValue> value)
    {
        if (type != JsonType::OBJECT)
            return;
        object_value[key] = value;
    }

    // Print the JSON value (for demonstration purposes)
    void print(int indent = 0) const
    {
        std::string indent_str(indent * 2, ' ');
        switch (type)
        {
        case JsonType::STRING:
            std::cout << indent_str << "\"" << string_value << "\"" << std::endl;
            break;
        case JsonType::NUMBER:
            std::cout << indent_str << number_value << std::endl;
            break;
        case JsonType::BOOLEAN:
            std::cout << indent_str << (bool_value ? "true" : "false") << std::endl;
            break;
        case JsonType::ARRAY:
            std::cout << indent_str << "[" << std::endl;
            for (const auto &item : array_value)
            {
                item->print(indent + 1);
            }
            std::cout << indent_str << "]" << std::endl;
            break;
        case JsonType::OBJECT:
            std::cout << indent_str << "{" << std::endl;
            for (const auto &pair : object_value)
            {
                std::cout << indent_str << "  \"" << pair.first << "\": ";
                pair.second->print(0);
            }
            std::cout << indent_str << "}" << std::endl;
            break;
        }
    }

private:
    std::string string_value;
    double number_value;
    bool bool_value;
    std::vector<std::shared_ptr<JsonValue>> array_value;
    std::unordered_map<std::string, std::shared_ptr<JsonValue>> object_value;
};

int main()
{
    // Create a JSON object
    auto root = std::make_shared<JsonValue>(std::unordered_map<std::string, std::shared_ptr<JsonValue>>{});
    root->add_to_object("name", std::make_shared<JsonValue>("John Doe"));
    root->add_to_object("age", std::make_shared<JsonValue>(30));
    root->add_to_object("is_student", std::make_shared<JsonValue>(false));

    // Create a JSON array and add it to the object
    auto hobbies = std::make_shared<JsonValue>();
    hobbies->add_to_array(std::make_shared<JsonValue>("reading"));
    hobbies->add_to_array(std::make_shared<JsonValue>("swimming"));
    hobbies->add_to_array(std::make_shared<JsonValue>("coding"));
    root->add_to_object("hobbies", hobbies);

    // Print the JSON value
    root->print();

    return 0;
}