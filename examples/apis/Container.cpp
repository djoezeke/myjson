/**
 * @example Container.cpp
 * @brief Demonstrates working with JSON arrays and objects as containers.
 *
 * This example shows:
 * - Array operations (push_back, indexing, iteration)
 * - Object operations (insertion, lookup, iteration)
 * - Container size and element access
 * - Nested structures
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Create and populate an array
    json numbers = json::array();
    for (int i = 1; i <= 5; ++i)
    {
        numbers.push_back(i * 10);
    }
    std::cout << "Numbers array: " << numbers.dump() << std::endl;
    std::cout << "Array size: " << numbers.size() << std::endl;

    // Access array elements
    std::cout << "\nArray element access:" << std::endl;
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        std::cout << "  [" << i << "] = " << numbers[i].as_integer() << std::endl;
    }

    // Create an object with nested data
    json company = json::object();
    company["name"] = "TechCorp";
    company["founded"] = 2010;
    company["locations"] = json::array();
    company["locations"].push_back("New York");
    company["locations"].push_back("San Francisco");
    company["locations"].push_back("London");

    std::cout << "\nCompany info (formatted):" << std::endl;
    std::cout << company.dump(2) << std::endl;

    // Check if key exists
    std::cout << "\nKey existence checks:" << std::endl;
    std::cout << "  Has 'name': " << company.contains("name") << std::endl;
    std::cout << "  Has 'employees': " << company.contains("employees") << std::endl;

    // Get object size (number of key-value pairs)
    std::cout << "\nObject size: " << company.size() << std::endl;

    // Iterate over object entries
    std::cout << "\nObject entries:" << std::endl;
    for (auto &entry : company)
    {
        std::cout << "  " << entry.first << ": " << entry.second.dump() << std::endl;
    }

    return 0;
}
