#include <iostream>

#include "../myjson.hpp"

/**
 * @brief Tests the equality and inequality operators for JSON objects and arrays.
 */
void testEqualityOperator()
{
    // Test case 1: Compare two empty JSON objects
    json::JSON json1(json::Type::OBJECT);
    json::JSON json2(json::Type::OBJECT);
    if (json1 == json2)
    {
        std::cout << "Test case 1 passed: Two empty JSON objects are equal." << std::endl;
    }
    else
    {
        std::cout << "Test case 1 failed: Two empty JSON objects are not equal." << std::endl;
    }

    // Test case 2: Compare two JSON objects with the same key-value pairs
    json1.Add("key1", json::JSON(json::Type::STRING, "value1"));
    json2.Add("key1", json::JSON(json::Type::STRING, "value1"));
    if (json1 == json2)
    {
        std::cout << "Test case 2 passed: Two JSON objects with the same key-value pairs are equal." << std::endl;
    }
    else
    {
        std::cout << "Test case 2 failed: Two JSON objects with the same key-value pairs are not equal." << std::endl;
    }

    // Test case 3: Compare two JSON objects with different key-value pairs
    json2.Replace("key1", json::JSON(json::Type::STRING, "value2"));
    if (json1 != json2)
    {
        std::cout << "Test case 3 passed: Two JSON objects with different key-value pairs are not equal." << std::endl;
    }
    else
    {
        std::cout << "Test case 3 failed: Two JSON objects with different key-value pairs are equal." << std::endl;
    }

    // Test case 4: Compare two JSON arrays with the same elements
    json::JSON array1(json::Type::ARRAY);
    json::JSON array2(json::Type::ARRAY);
    array1.Add(0, json::JSON(json::Type::INTEGER, 1));
    array2.Add(0, json::JSON(json::Type::INTEGER, 1));

    if (array1 == array2)
    {
        std::cout << "Test case 4 passed: Two JSON arrays with the same elements are equal." << std::endl;
    }
    else
    {
        std::cout << "Test case 4 failed: Two JSON arrays with the same elements are not equal." << std::endl;
    }

    // Test case 5: Compare two JSON arrays with different elements
    array2.Replace(0, json::JSON(json::Type::INTEGER, 2));
    if (array1 != array2)
    {
        std::cout << "Test case 5 passed: Two JSON arrays with different elements are not equal." << std::endl;
    }
    else
    {
        std::cout << "Test case 5 failed: Two JSON arrays with different elements are equal." << std::endl;
    }
}

/**
 * @brief Main function to run the tests.
 * @return int Exit status.
 */
int main()
{
    testEqualityOperator();
    return 0;
}