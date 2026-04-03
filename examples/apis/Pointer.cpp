/**
 * @example Pointer.cpp
 * @brief Demonstrates JSON Pointer (RFC 6901) for accessing values.
 *
 * This example shows:
 * - Using JSON Pointers to access nested values
 * - Pointer syntax and special characters
 * - Accessing arrays and objects via pointers
 * - Error handling with invalid pointers
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Create a complex nested structure
    json data = json::parse(R"({
        "store": {
            "name": "Tech Store",
            "location": {
                "city": "San Francisco",
                "zip": "94103"
            },
            "products": [
                {"id": 1, "name": "Laptop", "price": 1200},
                {"id": 2, "name": "Mouse", "price": 25},
                {"id": 3, "name": "Keyboard", "price": 75}
            ]
        }
    })");

    std::cout << "Original document:" << std::endl;
    std::cout << data.dump(2) << std::endl;

    // Example 1: Access object properties
    std::cout << "\nExample 1: Access object properties" << std::endl;
    try
    {
        const json &store_name = json_pointer("/store/name").ref(data);
        std::cout << "Store name: " << store_name.as_string() << std::endl;

        const json &city = json_pointer("/store/location/city").ref(data);
        std::cout << "City: " << city.as_string() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Pointer error: " << e.what() << std::endl;
    }

    // Example 2: Access array elements
    std::cout << "\nExample 2: Access array elements" << std::endl;
    try
    {
        const json &first_product = json_pointer("/store/products/0").ref(data);
        std::cout << "First product: " << first_product.dump() << std::endl;

        const json &second_price = json_pointer("/store/products/1/price").ref(data);
        std::cout << "Second product price: " << second_price.as_integer() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Pointer error: " << e.what() << std::endl;
    }

    // Example 3: Manual pointer navigation
    std::cout << "\nExample 3: Manual navigation using pointers" << std::endl;
    try
    {
        // Access all products using loop
        const json &products = json_pointer("/store/products").ref(data);
        for (size_t i = 0; i < products.size(); ++i)
        {
            std::string path = "/store/products/" + std::to_string(i) + "/name";
            const json &product_name = json_pointer(path).ref(data);
            std::cout << "  Product " << i << ": " << product_name.as_string() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Pointer error: " << e.what() << std::endl;
    }

    // Example 4: Escaped pointer tokens
    std::cout << "\nExample 4: Special characters in pointers" << std::endl;
    json special = json::object();
    special["a/b"] = "value1";
    special["c%d"] = "value2";
    special["e\"f"] = "value3";

    try
    {
        // These would require proper escaping: /a~1b, /c%d, /e\"f
        std::cout << "Special document: " << special.dump() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Example 5: Pointer existence checking
    std::cout << "\nExample 5: Safe pointer access with try-catch" << std::endl;
    std::vector<std::string> pointers = {
        "/store/name",
        "/store/products/0/name",
        "/store/products/10/name", // Out of bounds
        "/store/nonexistent"};

    for (const auto &ptr : pointers)
    {
        try
        {
            const json &value = json_pointer(ptr).ref(data);
            std::cout << "  " << ptr << " -> " << value.dump() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "  " << ptr << " -> [Error: " << e.what() << "]" << std::endl;
        }
    }

    return 0;
}
