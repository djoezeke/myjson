// Example: parsing JSON and converting values to a small C++ model.

#include <iostream>
#include <string>

#include "../../include/myjson/myjson.hpp"

namespace
{
    struct person
    {
        std::string name;
        int age{};
        bool active{};
    };

    person from_json(const myjson::json &value)
    {
        myjson::detail::deserializer input(value);
        return {input.get<std::string>(""), input.get<int>(0), input.get<bool>(false)};
    }

    myjson::json to_json(const person &value)
    {
        myjson::json result = myjson::json::object();
        result["name"] = value.name;
        result["age"] = value.age;
        result["active"] = value.active;
        return result;
    }
}

int main()
{
    const myjson::json input = myjson::json::parse(R"({"name":"Ada","age":37,"active":true})");
    const person ada = from_json(input);
    const myjson::json output = to_json(ada);

    std::cout << output.dump_compact() << '\n';
    return 0;
}
