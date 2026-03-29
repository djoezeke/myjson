#include <catch2/catch_all.hpp>

#include <sstream>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("json::dump serializes escaped string values", "[cxx][serializer]")
{
    myjson::json value = myjson::json::object();
    value["text"] = "line\n\"x\"";

    const std::string dumped = value.dump();
    REQUIRE(dumped == R"({"text":"line\n\"x\""})");
}

TEST_CASE("json::dump pretty prints with indentation", "[cxx][serializer]")
{
    myjson::json value = myjson::json::object();
    value["n"] = 1;
    value["a"] = myjson::json::array();
    value["a"].push_back(true);

    const std::string pretty = value.dump_pretty();
    REQUIRE(pretty.find("\n  \"a\": [") != std::string::npos);
    REQUIRE(pretty.find("\n    true") != std::string::npos);
}

#ifndef MYJSON_NO_STL
TEST_CASE("stream operators round-trip JSON", "[cxx][serializer]")
{
    std::istringstream input(R"({"k":"v"})");
    myjson::json value;
    input >> value;

    std::ostringstream output;
    output << value;

    REQUIRE(output.str() == R"({"k":"v"})");
}
#endif // MYJSON_NO_STL
