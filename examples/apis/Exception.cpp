/**
 * @example Exception.cpp
 * @brief Demonstrates error handling with myjson.
 *
 * This example shows:
 * - Parsing invalid JSON and catching exceptions
 * - Type safety with safe conversions
 * - Error reporting and recovery
 * - Defensive programming patterns
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Example 1: Parsing invalid JSON
    std::cout << "Example 1: Invalid JSON parsing" << std::endl;
    try
    {
        std::string invalid_json = "{invalid json}";
        json result = json::parse(invalid_json);
    }
    catch (const std::exception &e)
    {
        std::cout << "  Caught exception: " << e.what() << std::endl;
    }

    // Example 2: Type mismatch handling
    std::cout << "\nExample 2: Type mismatch handling" << std::endl;
    json data = json::object();
    data["count"] = "not a number";
    data["name"] = 42;

    // Safe conversion with defaults
    try
    {
        int count = data["count"].as_integer();
        std::cout << "  Count: " << count << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "  Cannot convert 'count' to integer: " << e.what() << std::endl;
        // Use a safe default
        int count = 0;
        std::cout << "  Using default count: " << count << std::endl;
    }

    // Example 3: Empty file handling
    std::cout << "\nExample 3: Accessing missing keys" << std::endl;
    json obj = json::object();
    obj["present"] = "value";

    // Access missing key (returns null)
    if (obj["missing"].is_null())
    {
        std::cout << "  Key 'missing' not found (returned null)" << std::endl;
    }

    // Example 4: Safe array access
    std::cout << "\nExample 4: Array access validation" << std::endl;
    json arr = json::array();
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    size_t index = 10;
    if (index < arr.size())
    {
        std::cout << "  Element at [" << index << "]: " << arr[index].dump() << std::endl;
    }
    else
    {
        std::cout << "  Index " << index << " out of range (array size: " << arr.size() << ")" << std::endl;
    }

    // Example 5: Invalid numeric operations
    std::cout << "\nExample 5: Type checking before conversion" << std::endl;
    json values = json::array();
    values.push_back(42);
    values.push_back("text");
    values.push_back(3.14);

    for (size_t i = 0; i < values.size(); ++i)
    {
        if (values[i].is_number())
        {
            std::cout << "  [" << i << "] is a number: " << values[i].as_number() << std::endl;
        }
        else if (values[i].is_string())
        {
            std::cout << "  [" << i << "] is a string: " << values[i].as_string() << std::endl;
        }
        else
        {
            std::cout << "  [" << i << "] is type: " << static_cast<int>(values[i].type()) << std::endl;
        }
    }

    return 0;
}
