#include <catch2/catch_all.hpp>

#include <cstdio>
#include <cstring>
#include <sstream>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("json::parse parses object from string", "[cxx][parser]")
{
    const std::string text = R"({"name":"alice","age":42,"active":true})";
    const myjson::json value = myjson::json::parse(text);

    REQUIRE(value.is_object());
    REQUIRE(value["name"].as_string() == "alice");
    REQUIRE(value["age"].as_integer() == 42);
    REQUIRE(value["active"].as_bool());
}

TEST_CASE("json::parse decodes escaped and unicode strings", "[cxx][parser]")
{
    const myjson::json value = myjson::json::parse(R"({"msg":"line\n\u0041"})");

    REQUIRE(value["msg"].is_string());
    REQUIRE(value["msg"].as_string() == "line\nA");
}

#ifndef MYJSON_NO_STL
TEST_CASE("json::parse parses from istream", "[cxx][parser]")
{
    std::istringstream stream(R"([1,2,3])");
    const myjson::json value = myjson::json::parse(stream);

    REQUIRE(value.is_array());
    REQUIRE(value.size() == 3);
    REQUIRE(value[static_cast<size_t>(0)].as_integer() == 1);
    REQUIRE(value[static_cast<size_t>(2)].as_integer() == 3);
}
#endif // MYJSON_NO_STL

TEST_CASE("json::parse parses from FILE*", "[cxx][parser]")
{
    std::FILE *file = std::tmpfile();
    REQUIRE(file != nullptr);

    const char *payload = R"({"ok":true,"v":7})";
    std::fwrite(payload, 1, std::strlen(payload), file);
    std::rewind(file);

    const myjson::json value = myjson::json::parse(file);
    std::fclose(file);

    REQUIRE(value.is_object());
    REQUIRE(value["ok"].as_bool());
    REQUIRE(value["v"].as_integer() == 7);
}
