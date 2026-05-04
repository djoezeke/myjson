/**
 * @example Basic.cpp
 * @brief Demonstrates basic JSON creation and manipulation.
 *
 * This example shows:
 * - Creating JSON objects and arrays
 * - Accessing and modifying values
 * - Type checking and conversions
 * - Serialization to string
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Create a JSON object
    json person = json::object({{"name", "Rose"}, {"gender", "Female"}, {"id", 23030}});
    // person["name"] = "Alice";
    person["age"] = 30;
    person["email"] = "alice@example.com";
    person["active"] = true;

    std::cout << "Person JSON: " << person.dump() << std::endl;

    // Create a JSON array
    json scores = json::array({23, "Hello", 25, 26});
    scores.push_back("95");
    scores.push_back("87");
    scores.push_back(92);
    scores.push_back(true); // Mixed types are allowed

    std::cout << "Scores: " << scores.dump() << std::endl;

    // Add array to person
    person["test_scores"] = scores;

    // Type checking
    std::cout << "\nType checking:" << std::endl;
    std::cout << "  name is string: " << person["name"].is_string() << std::endl;
    std::cout << "  age is number: " << person["age"].is_floating() << std::endl;
    std::cout << "  active is boolean: " << person["active"].is_boolean() << std::endl;
    std::cout << "  missing_key is null: " << person["missing_key"].is_null() << std::endl;

    // Value access
    std::cout << "\nValue access:" << std::endl;
    std::cout << "  Name: " << person["name"].as_string() << std::endl;
    std::cout << "  Age: " << person["age"].as_floating() << std::endl;
    std::cout << "  Active: " << person["active"].as_boolean() << std::endl;

    // Pretty-print with indentation
    std::cout << "\nFormatted output (indent=2):" << std::endl;
    std::cout << person.dump(2) << std::endl;

    return 0;
}
