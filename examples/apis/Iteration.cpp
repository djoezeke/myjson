/**
 * @example Iteration.cpp
 * @brief Demonstrates iterating over JSON structures.
 *
 * This example shows:
 * - Iterating through arrays with range-based for loops
 * - Iterating through objects (key-value pairs)
 * - Nested structure traversal
 * - Filtering and searching during iteration
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Create sample data
    json team = json::object();
    team["name"] = "Engineering";
    team["members"] = json::array();

    json member1 = json::object();
    member1["name"] = "Alice";
    member1["role"] = "Lead";
    member1["years"] = 5;

    json member2 = json::object();
    member2["name"] = "Bob";
    member2["role"] = "Developer";
    member2["years"] = 3;

    json member3 = json::object();
    member3["name"] = "Carol";
    member3["role"] = "Developer";
    member3["years"] = 2;

    team["members"].push_back(member1);
    team["members"].push_back(member2);
    team["members"].push_back(member3);

    // Example 1: Iterate over array using index-based access
    std::cout << "Example 1: Iterate over array using indices" << std::endl;
    std::cout << "Members:" << std::endl;
    for (size_t i = 0; i < team["members"].size(); ++i)
    {
        const auto &member = team["members"][i];
        std::cout << "  - " << member["name"].as_string()
                  << " (" << member["role"].as_string()
                  << ", " << member["years"].as_integer() << " years)" << std::endl;
    }

    // Example 2: Iterate over object
    std::cout << "\nExample 2: Iterate over object" << std::endl;
    std::cout << "Team properties:" << std::endl;
    for (auto &entry : team)
    {
        std::cout << "  " << entry.first << ": ";
        if (entry.second.is_array())
        {
            std::cout << "[array with " << entry.second.size() << " items]" << std::endl;
        }
        else if (entry.second.is_object())
        {
            std::cout << "[object]" << std::endl;
        }
        else
        {
            std::cout << entry.second.dump() << std::endl;
        }
    }

    // Example 3: Filtered iteration over array
    std::cout << "\nExample 3: Filtered iteration (Developers only)" << std::endl;
    const json &members = team["members"];
    for (size_t i = 0; i < members.size(); ++i)
    {
        if (members[i]["role"].as_string() == "Developer")
        {
            std::cout << "  - " << members[i]["name"].as_string() << std::endl;
        }
    }

    // Example 4: Nested iteration - iterate array of objects
    std::cout << "\nExample 4: Nested structure with multiple teams" << std::endl;
    json company = json::array();
    company.push_back(team);

    json marketing = json::object();
    marketing["name"] = "Marketing";
    marketing["members"] = json::array();
    marketing["members"].push_back(json::object()); // placeholder
    company.push_back(marketing);

    for (size_t i = 0; i < company.size(); ++i)
    {
        const auto &dept = company[i];
        std::cout << "\nDepartment: " << dept["name"].as_string() << std::endl;
        std::cout << "  Members: " << dept["members"].size() << std::endl;
    }

    // Example 5: Index-based iteration
    std::cout << "\nExample 5: Index-based iteration" << std::endl;
    json scores = json::array();
    scores.push_back(95);
    scores.push_back(87);
    scores.push_back(92);

    for (size_t i = 0; i < scores.size(); ++i)
    {
        std::cout << "  Score[" << i << "]: " << scores[i].as_integer() << std::endl;
    }

    return 0;
}
