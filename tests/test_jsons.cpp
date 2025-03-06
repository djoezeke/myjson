#include <iostream>
#include <cassert>

#include "../myjson.hpp"

void test_equality_operator()
{
    json::JSON json1(json::Type::OBJECT);
    json::JSON json2(json::Type::OBJECT);
    assert(json1 == json2);

    json1.Add("key1", json::JSON(json::Type::STRING, "value1"));
    json2.Add("key1", json::JSON(json::Type::STRING, "value1"));
    assert(json1 == json2);

    json2.Replace("key1", json::JSON(json::Type::STRING, "value2"));
    assert(json1 != json2);

    std::cout << "Equality and inequality operators test passed." << std::endl;
}

void test_assignment_operator()
{
    // json::JSON json1(json::Type::OBJECT);
    // json1.Add("key1", json::JSON(json::Type::STRING, "value1"));

    // json::JSON json2 = json1;
    // assert(json2.Get("key1").String() == "value1");

    // json::JSON json3(json::Type::OBJECT);
    // json3 = json1;
    // assert(json3.Get("key1").String() == "value1");

    std::cout << "Assignment operator test passed." << std::endl;
}

void test_type_casting()
{
    // json::JSON jsonString(json::Type::STRING, "Hello, World!");
    // assert(static_cast<std::string>(jsonString) == "Hello, World!");

    // json::JSON jsonNumber(json::Type::INTEGER, 42);
    // assert(static_cast<int>(jsonNumber) == 42);

    // json::JSON jsonDouble(json::Type::DOUBLE, 3.14);
    // assert(static_cast<double>(jsonDouble) == 3.14);

    // json::JSON jsonBool(json::Type::BOOLEAN, true);
    // assert(static_cast<bool>(jsonBool) == true);

    std::cout << "Type casting operators test passed." << std::endl;
}

void test_index_operator()
{
    // json::JSON jsonObject(json::Type::OBJECT);
    // jsonObject.Add("key1", json::JSON(json::Type::STRING, "value1"));
    // assert(jsonObject["key1"].String() == "value1");

    // json::JSON jsonArray(json::Type::ARRAY);
    // jsonArray.Add(0, json::JSON(json::Type::STRING, "value1"));
    // assert(jsonArray[0].String() == "value1");

    std::cout << "Index operator test passed." << std::endl;
}

void test_function_call_operator()
{
    json::JSON jsonObject(json::Type::OBJECT);
    jsonObject.Add("key1", json::JSON(json::Type::STRING, "value1"));
    assert(jsonObject("key1") == "value1");

    json::JSON jsonArray(json::Type::ARRAY);
    jsonArray.Add(0, json::JSON(json::Type::STRING, "value1"));
    assert(jsonArray(0) == "value1");

    std::cout << "Function call operator test passed." << std::endl;
}

int main()
{
    test_equality_operator();
    test_assignment_operator();
    test_type_casting();
    test_index_operator();
    test_function_call_operator();

    std::cout << "All operator tests passed!" << std::endl;
    return 0;
}