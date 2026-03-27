/**
 * @file nlohmann_compat_examples.cpp
 * @brief Examples showing myjson usage with nlohmann::json compatible API.
 * @author Sackey Ezekiel Etrue
 * @version 0.1.0
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * This file demonstrates how to use myjson as a drop-in replacement for nlohmann/json.
 */

#include <iostream>

#include "../../include/myjson/myjson.hpp"

using json = myjson::json;

static json j_int(int value)
{
    return json(static_cast<json::integer_t>(value));
}

/**
 * Example 1: Basic JSON creation and access (like nlohmann::json)
 */
void example_basic_creation()
{
    std::cout << "=== Example 1: Basic JSON Creation and Access ===" << std::endl;

    // Create empty object
    json obj;
    obj["name"] = "John Doe";
    obj["age"] = j_int(30);
    obj["active"] = true;

    // Alternative: create with object()
    json person = json::object();
    person["name"] = "Jane Smith";
    person["age"] = j_int(28);
    person["email"] = "jane@example.com";

    std::cout << "Person object:\n"
              << person.dump_pretty() << std::endl;

    // Create array
    json arr = json::array();
    arr.push_back(j_int(1));
    arr.push_back("hello");
    arr.push_back(true);
    arr.push_back(json::object());

    std::cout << "\nArray:\n"
              << arr.dump_pretty() << std::endl;
}

/**
 * Example 2: Type conversions and safe access
 */
void example_type_conversions()
{
    std::cout << "\n=== Example 2: Type Conversions ===" << std::endl;

    json data = json::object();
    data["count"] = j_int(42);
    data["ratio"] = 3.14;
    data["enabled"] = true;
    data["message"] = "Hello";

    // Get with defaults
    int count = data["count"].get<int>();
    double ratio = data["ratio"].get<double>(0.0);
    bool enabled = data["enabled"].get<bool>();
    std::string message = data["message"].get<std::string>("default");

    std::cout << "count: " << count << std::endl;
    std::cout << "ratio: " << ratio << std::endl;
    std::cout << "enabled: " << enabled << std::endl;
    std::cout << "message: " << message << std::endl;

    // Type checking
    std::cout << "\nType information:" << std::endl;
    std::cout << "count is_integer: " << data["count"].is_integer() << std::endl;
    std::cout << "ratio is_number: " << data["ratio"].is_number() << std::endl;
    std::cout << "enabled is_boolean: " << data["enabled"].is_boolean() << std::endl;
}

/**
 * Example 3: Container-like operations
 */
void example_container_ops()
{
    std::cout << "\n=== Example 3: Container Operations ===" << std::endl;

    // Array operations (like nlohmann::json)
    json arr = json::array();
    arr.push_back(j_int(10));
    arr.push_back(j_int(20));
    arr.push_back(j_int(30));

    std::cout << "Array size: " << arr.size() << std::endl;
    std::cout << "First element: " << arr[size_t{0}].as_integer() << std::endl;
    std::cout << "Last element: " << arr.back().as_integer() << std::endl;

    // Array iteration
    std::cout << "Array elements: ";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[static_cast<size_t>(i)].as_integer() << " ";
    }
    std::cout << std::endl;

    // Object operations
    json obj = json::object();
    obj["a"] = j_int(1);
    obj["b"] = j_int(2);
    obj["c"] = j_int(3);

    std::cout << "\nObject contains 'b': " << obj.contains("b") << std::endl;
    std::cout << "Object keys: ";
    for (const auto &key : obj.keys())
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    // Erase elements
    obj.erase("b");
    std::cout << "After erasing 'b', size: " << obj.size() << std::endl;
}

/**
 * Example 4: JSON Pointer support (RFC 6901)
 */
void example_json_pointer()
{
    std::cout << "\n=== Example 4: JSON Pointer (RFC 6901) ===" << std::endl;

    json doc = json::object();
    doc["store"]["book"][size_t{0}]["title"] = "Effective C++";
    doc["store"]["book"][size_t{0}]["price"] = 40.50;
    doc["store"]["book"][size_t{1}]["title"] = "Modern C++";
    doc["store"]["book"][size_t{1}]["price"] = 45.99;

    // Access via pointer
    std::string title = doc.at_pointer("/store/book/0/title").as_string();
    std::cout << "Book title via pointer: " << title << std::endl;

    double price = doc.at_pointer("/store/book/1/price").as_number();
    std::cout << "Second book price: " << price << std::endl;

    // Modify via direct nested assignment (equivalent target)
    doc["store"]["book"][size_t{0}]["rating"] = j_int(5);

    // Safe pointer access
    auto result = doc.find_pointer("/store/book/2");
    if (result.has_value())
    {
        std::cout << "Found book 2" << std::endl;
    }
    else
    {
        std::cout << "Book 2 not found (as expected)" << std::endl;
    }
}

/**
 * Example 5: JSON Patch support (RFC 6902)
 */
void example_json_patch()
{
    std::cout << "\n=== Example 5: JSON Patch (RFC 6902) ===" << std::endl;

    json original = json::object();
    original["name"] = "Alice";
    original["age"] = j_int(30);
    original["city"] = "New York";

    std::cout << "Original:\n"
              << original.dump_pretty() << std::endl;

    // Create patch operations
    json patch = json::array();
    patch.push_back(myjson::json_patch::replace_operation("/city", "Boston"));
    patch.push_back(myjson::json_patch::replace_operation("/age", j_int(31)));
    patch.push_back(myjson::json_patch::test_operation("/name", "Alice"));

    std::cout << "\nPatch operations:\n"
              << patch.dump_pretty() << std::endl;

    // Apply patch
    json modified = original.apply_patch(patch);
    std::cout << "\nAfter applying patch:\n"
              << modified.dump_pretty() << std::endl;
}

/**
 * Example 6: JSON Merge Patch support (RFC 7386)
 */
void example_json_merge_patch()
{
    std::cout << "\n=== Example 6: JSON Merge Patch (RFC 7386) ===" << std::endl;

    json original = json::object();
    original["name"] = "Bob";
        original["age"] = j_int(25);
    original["tags"] = json::array();

    // Merge patch (simpler than JSON Patch)
    json patch = json::object();
    patch["age"] = j_int(26);
    patch["email"] = "bob@example.com";
    patch["tags"] = nullptr; // null value deletes the field

    json merged = original.apply_merge_patch(patch);

    std::cout << "Original:\n"
              << original.dump_pretty() << std::endl;
    std::cout << "\nMerge patch:\n"
              << patch.dump_pretty() << std::endl;
    std::cout << "\nAfter merge:\n"
              << merged.dump_pretty() << std::endl;
}

/**
 * Example 7: Iteration like nlohmann::json
 */
void example_iteration()
{
    std::cout << "\n=== Example 7: Iteration ===" << std::endl;

    json config = json::object();
    config["database"]["host"] = "localhost";
    config["database"]["port"] = j_int(5432);
    config["database"]["user"] = "admin";

    // Iterate over object members
    std::cout << "Database config:" << std::endl;
    for (auto &[key, value] : config["database"])
    {
        if (value.is_string())
            std::cout << "  " << key << ": " << value.as_string() << std::endl;
        else
            std::cout << "  " << key << ": " << value.as_integer() << std::endl;
    }
}

/**
 * Example 8: Comparison and deep copy
 */
void example_comparison_copy()
{
    std::cout << "\n=== Example 8: Comparison and Deep Copy ===" << std::endl;

    json a = json::object();
    a["x"] = j_int(10);
    a["y"] = j_int(20);

    json b = a.clone();
    b["z"] = j_int(30);

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a size: " << a.size() << ", b size: " << b.size() << std::endl;

    // Ordering
    json c = j_int(10);
    json d = j_int(20);
    std::cout << "10 < 20: " << (c < d) << std::endl;
}

/**
 * Example 9: Encoding support (different from nlohmann)
 */
void example_encoding_support()
{
    std::cout << "\n=== Example 9: Encoding Support ===" << std::endl;
    std::cout << "myjson supports UTF-8, UTF-16, UTF-32 encodings" << std::endl;
    std::cout << "This is beyond nlohmann::json capabilities!" << std::endl;

    // UTF-8 string
    json utf8_data = json::object();
    utf8_data["greeting"] = "Hello, 世界";
    utf8_data["emoji"] = "😊";

    std::cout << "\nUTF-8 JSON: " << utf8_data.dump_pretty() << std::endl;
}

/**
 * Example 10: From/to string with error handling
 */
void example_error_handling()
{
    std::cout << "\n=== Example 10: Error Handling ===" << std::endl;

    // Valid JSON
    auto valid = json::try_parse(R"({"name": "John", "age": 30})");
    if (valid.has_value())
    {
        std::cout << "Parsed valid JSON successfully" << std::endl;
    }

    // Invalid JSON
    auto invalid = json::try_parse(R"({"invalid": undefined})");
    if (!invalid.has_value())
    {
        std::cout << "Failed to parse invalid JSON (expected)" << std::endl;
    }

    // Safe type conversion
    json data = json::object();
    data["value"] = "not a number";
    try
    {
        int num = data["value"].get_safe<int>();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught expected conversion error" << std::endl;
    }
}

int main()
{
    try
    {
        example_basic_creation();
        example_type_conversions();
        example_container_ops();
        example_json_pointer();
        example_json_patch();
        example_json_merge_patch();
        example_iteration();
        example_comparison_copy();
        example_encoding_support();
        example_error_handling();

        std::cout << "\n=== All Examples Completed Successfully ===" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
