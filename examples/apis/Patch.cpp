/**
 * @example Patch.cpp
 * @brief Demonstrates JSON Patch (RFC 6902) operations.
 *
 * This example shows:
 * - Applying patches to modify JSON documents
 * - Supported operations: add, remove, replace, move, copy, test
 * - Batch modifications with patches
 * - Validating patch application
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Original document
    json doc = json::parse(R"({
        "title": "Hello World",
        "author": "Alice",
        "tags": ["json", "example"]
    })");

    std::cout << "Original document:" << std::endl;
    std::cout << doc.dump(2) << std::endl;

    // Example 1: Replace operation
    std::cout << "\nExample 1: Replace operation" << std::endl;
    json patch1 = json::array();
    json op1 = json::object();
    op1["op"] = "replace";
    op1["path"] = "/title";
    op1["value"] = "Hello JSON!";
    patch1.push_back(op1);

    json result1 = doc;
    try
    {
        result1 = json_patch(patch1).apply(result1);
        std::cout << "Result after replace:" << std::endl;
        std::cout << result1.dump(2) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Patch apply error: " << e.what() << std::endl;
    }

    // Example 2: Add operation
    std::cout << "\nExample 2: Add operation" << std::endl;
    json patch2 = json::array();
    json op2 = json::object();
    op2["op"] = "add";
    op2["path"] = "/tags/-";
    op2["value"] = "tutorial";
    patch2.push_back(op2);

    json result2 = doc;
    try
    {
        result2 = json_patch(patch2).apply(result2);
        std::cout << "Result after add:" << std::endl;
        std::cout << result2.dump(2) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Patch apply error: " << e.what() << std::endl;
    }

    // Example 3: Remove operation
    std::cout << "\nExample 3: Remove operation" << std::endl;
    json patch3 = json::array();
    json op3 = json::object();
    op3["op"] = "remove";
    op3["path"] = "/tags/1";
    patch3.push_back(op3);

    json result3 = doc;
    try
    {
        result3 = json_patch(patch3).apply(result3);
        std::cout << "Result after remove:" << std::endl;
        std::cout << result3.dump(2) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Patch apply error: " << e.what() << std::endl;
    }

    // Example 4: Multiple operations
    std::cout << "\nExample 4: Multiple operations" << std::endl;
    json patch4 = json::array();

    json op4a = json::object();
    op4a["op"] = "replace";
    op4a["path"] = "/author";
    op4a["value"] = "Bob";
    patch4.push_back(op4a);

    json op4b = json::object();
    op4b["op"] = "add";
    op4b["path"] = "/version";
    op4b["value"] = "1.0";
    patch4.push_back(op4b);

    json result4 = doc;
    try
    {
        result4 = json_patch(patch4).apply(result4);
        std::cout << "Result after multiple operations:" << std::endl;
        std::cout << result4.dump(2) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Patch apply error: " << e.what() << std::endl;
    }

    return 0;
}
