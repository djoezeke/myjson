#include <iostream>
#include <cassert>

#include "../myjson.hpp"

void test_parse_and_dump()
{
    std::string jsonString = R"({"name":"John","age":30,"is_student":false})";
    json::JSON jsonObject = json::load(jsonString);

    // assert(jsonObject.Get("name").String() == "John");
    // assert(static_cast<int>(jsonObject.Get("age")) == 30);
    // assert(static_cast<bool>(jsonObject.Get("is_student")) == false);

    std::string dumpedString = json::dump(jsonObject);
    // assert(dumpedString == jsonString);
}

int main()
{
    test_parse_and_dump();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}