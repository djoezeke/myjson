#include <catch2/catch_all.hpp>

#include <vector>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("json range-based for iterates array values", "[cxx][iteration]")
{
    myjson::json array = myjson::json::array();
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    myjson::json::integer_t sum = 0;
    for (const auto &value : array)
    {
        REQUIRE(value.is_integer());
        sum += value.as_integer();
    }

    REQUIRE(sum == 6);
}

TEST_CASE("json range-based for iterates object values", "[cxx][iteration]")
{
    myjson::json object = myjson::json::object();
    object["a"] = 10;
    object["b"] = 20;
    object["c"] = 30;

    myjson::json::integer_t sum = 0;
    std::size_t count = 0;
    for (const auto &value : object)
    {
        REQUIRE(value.is_integer());
        sum += value.as_integer();
        ++count;
    }

    REQUIRE(count == 3);
    REQUIRE(sum == 60);
}

TEST_CASE("json reverse_iterator exposes key and value for object", "[cxx][iteration]")
{
    myjson::json object = myjson::json::object();
    object["alpha"] = 1;
    object["beta"] = 2;
    object["gamma"] = 3;

    auto it = object.rbegin();
    REQUIRE(it != object.rend());

    REQUIRE(it.key() == "gamma");
    REQUIRE(it.value().as_integer() == 3);

    ++it;
    REQUIRE(it != object.rend());
    REQUIRE(it.key() == "beta");
    REQUIRE(it.value().as_integer() == 2);

    ++it;
    REQUIRE(it != object.rend());
    REQUIRE(it.key() == "alpha");
    REQUIRE(it.value().as_integer() == 1);
}

TEST_CASE("json reverse_iterator traverses array in reverse order", "[cxx][iteration]")
{
    myjson::json array = myjson::json::array();
    array.push_back(4);
    array.push_back(5);
    array.push_back(6);

    std::vector<myjson::json::integer_t> values;
    for (auto it = array.rbegin(); it != array.rend(); ++it)
    {
        values.push_back(it.value().as_integer());
    }

    REQUIRE(values.size() == 3);
    REQUIRE(values[0] == 6);
    REQUIRE(values[1] == 5);
    REQUIRE(values[2] == 4);
}
