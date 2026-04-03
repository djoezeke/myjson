#include <catch2/catch_all.hpp>

#include <sstream>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("json assignment accepts primitive values", "[cxx][conversion]")
{
    myjson::json value = myjson::json::object();
    value["name"] = "Alice";
    value["age"] = 30;
    value["active"] = true;
    value["note"] = nullptr;

    REQUIRE(value["name"].as_string() == "Alice");
    REQUIRE(value["age"].as_integer() == 30);
    REQUIRE(value["active"].as_bool());
    REQUIRE(value["note"].is_null());
}

TEST_CASE("deserializer reads typed values", "[cxx][conversion]")
{
    const myjson::json value = myjson::json::parse(R"({"name":"Ada","age":37,"active":true})");
    myjson::detail::deserializer input(value);

    REQUIRE(input.get<std::string>("") == "Ada");
    REQUIRE(input.get<int>(0) == 37);
    REQUIRE(input.get<bool>(false));
}

#ifndef MYJSON_NO_STL
TEST_CASE("stream extraction updates json values", "[cxx][conversion]")
{
    std::istringstream stream(R"({"x":1,"y":2})");
    myjson::json value;
    stream >> value;

    REQUIRE(value.is_object());
    REQUIRE(value["x"].as_integer() == 1);
    REQUIRE(value["y"].as_integer() == 2);
}
#endif // MYJSON_NO_STL
