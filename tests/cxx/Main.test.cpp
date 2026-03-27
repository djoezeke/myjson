#include <catch2/catch_all.hpp>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("C++ json basic object", "[cxx][json]")
{
    myjson::json value = myjson::json::object();
    value["name"] = "smoke";
    value["count"] = myjson::json(static_cast<myjson::json::integer_t>(1));

    REQUIRE(value.is_object());
    REQUIRE(value.contains("name"));
    REQUIRE(value["count"].as_integer() == 1);
}
