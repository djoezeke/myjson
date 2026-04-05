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

#include <iomanip>
#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;
    using namespace myjson::literals::json_literals;

    // create JSON object
    const json object =
        {
            {"the good", "il buono"},
            {"the bad", "il cattivo"},
            {"the ugly", "il brutto"}};

    // output element with key "the ugly"
    std::cout << object.at("the ugly") << '\n';

    // exception type_error.304
    try
    {
        // use at() on a non-object type
        const json str = "I am a string";
        std::cout << str.at("the good") << '\n';
    }
    catch (const json::exception &e)
    {
        std::cout << e.what() << '\n';
    }

    // exception out_of_range.401
    try
    {
        // try to read from a nonexisting key
        std::cout << object.at("the fast") << '\n';
    }
    catch (const json::exception)
    {
        std::cout << "out of range" << '\n';
    }

    return 0;
}
