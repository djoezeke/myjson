#include <catch2/catch_all.hpp>

#include "../../include/myjson/myjson.hpp"

TEST_CASE("json pointer utilities", "[cxx][pointer]")
{
    myjson::json value = myjson::json::parse(R"({"obj":{"arr":[1,2,3],"name":"Ada"}})");

    REQUIRE(value.contains_pointer("/obj/name"));
    REQUIRE_FALSE(value.contains_pointer("/obj/email"));

    REQUIRE(value.erase_pointer("/obj/arr/1"));
    REQUIRE(value["obj"]["arr"].size() == 2);
    REQUIRE(value.at("obj").at("arr").at(static_cast<size_t>(0)).as_integer() == 1);
    REQUIRE(value.at("obj").at("arr").at(static_cast<size_t>(1)).as_integer() == 3);

    REQUIRE_FALSE(value.erase_pointer("/obj/arr/20"));
    REQUIRE_FALSE(value.erase_pointer(""));

    myjson::json_pointer ptr("/obj");
    ptr /= "arr";
    ptr /= 0;

    REQUIRE(ptr.to_string() == "/obj/arr/0");
    REQUIRE(value[ptr].as_integer() == 1);
}
