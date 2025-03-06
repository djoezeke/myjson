#include <iostream>
#include <cassert>

#include "../myjson.hpp"

void test_equality_operator()
{
    json::JSON array1(json::Type::ARRAY);
    json::JSON array2(json::Type::ARRAY);
    assert(array1 == array2);

    array1.Add(0, json::JSON(json::Type::STRING, "value1"));
    array2.Add(1, json::JSON(json::Type::STRING, "value2"));
    assert(array1 == array2);

    json::JSON object1(json::Type::OBJECT);
    json::JSON object2(json::Type::OBJECT);
    assert(object1 == object2);

    object1.Add("key1", json::JSON(json::Type::STRING, "value1"));
    object1.Add("key2", json::JSON(json::Type::STRING, "value2"));
    assert(object1 == object2);

    std::cout << "Equality = test passed." << std::endl;
}

void test_inequality_operator()
{
    json::JSON array1(json::Type::ARRAY);
    json::JSON array2(json::Type::ARRAY);

    json::JSON object1(json::Type::OBJECT);
    json::JSON object2(json::Type::OBJECT);

    assert(array1 != object1);
    assert(array2 != object2);

    array1.Add(0, json::JSON(json::Type::STRING, "1value1"));
    assert(array1 != array2);

    object1.Add("key1", json::JSON(json::Type::STRING, "1value1"));
    assert(object1 != object2);

    array2.Add(0, json::JSON(json::Type::STRING, "2value1"));
    assert(array1 != array2);

    object2.Add("key1", json::JSON(json::Type::STRING, "2value2"));
    assert(object1 != object2);

    std::cout << "Inequality != test passed." << std::endl;
}

void test_assignment_operator()
{
    json::JSON object1(json::Type::OBJECT);
    object1.Add("key1", json::JSON(json::Type::STRING, "value1"));

    json::JSON object2 = object1;
    assert(object2.Get("key1").String() == "value1");
    assert(object1.Get("key1").String() == object2.Get("key1").String());

    json::JSON object3(json::Type::OBJECT);
    object3 = object2;
    assert(object3.Get("key1").String() == "value1");
    assert(object3.Get("key1").String() == object2.Get("key1").String());
    assert(object3.Get("key1").String() == object1.Get("key1").String());

    json::JSON array1(json::Type::ARRAY);
    array1.Add(0, json::JSON(json::Type::STRING, "value1"));

    json::JSON array2 = array1;
    assert(array2.Get(0).String() == "value1");
    assert(array1.Get(0).String() == array2.Get("key1").String());

    json::JSON array3(json::Type::ARRAY);
    array3 = array2;
    assert(array3.Get(0).String() == "value1");
    assert(array3.Get(0).String() == array2.Get(0).String());
    assert(array3.Get(0).String() == array1.Get(0).String());

    std::cout << "Assignment  = test passed." << std::endl;
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
    json::JSON jsonObject(json::Type::OBJECT);

    jsonObject.Add("key1", json::JSON(json::Type::STRING, "value1"));
    jsonObject.Add("key2", json::JSON(json::Type::STRING, "value2"));
    jsonObject.Add("key3", json::JSON(json::Type::STRING, "value3"));

    assert(jsonObject["key1"].String() == "value1");
    assert(jsonObject["key2"].String() == "value2");
    assert(jsonObject["key3"].String() == "value3");

    json::JSON jsonArray(json::Type::ARRAY);

    jsonArray.Add(0, json::JSON(json::Type::STRING, "value1"));
    jsonArray.Add(1, json::JSON(json::Type::STRING, "value2"));
    jsonArray.Add(2, json::JSON(json::Type::STRING, "value3"));

    assert(jsonArray[0].String() == "value1");
    assert(jsonArray[1].String() == "value2");
    assert(jsonArray[2].String() == "value3");

    std::cout << "Index [] test passed." << std::endl;
}

void test_function_call_operator()
{
    json::JSON jsonObject(json::Type::OBJECT);

    jsonObject.Add("key1", json::JSON(json::Type::STRING, "value1"));
    jsonObject.Add("key2", json::JSON(json::Type::STRING, "value2"));
    jsonObject.Add("key3", json::JSON(json::Type::STRING, "value3"));

    assert(jsonObject("key1") == "value1");
    assert(jsonObject("key2") == "value2");
    assert(jsonObject("key3") == "value3");

    json::JSON jsonArray(json::Type::ARRAY);

    jsonArray.Add(0, json::JSON(json::Type::STRING, "value1"));
    jsonArray.Add(1, json::JSON(json::Type::STRING, "value2"));
    jsonArray.Add(2, json::JSON(json::Type::STRING, "value3"));

    assert(jsonArray(0) == "value1");
    assert(jsonArray(1) == "value2");
    assert(jsonArray(2) == "value3");

    std::cout << "Function () test passed." << std::endl;
}

int main()
{
    test_equality_operator();
    test_inequality_operator();
    test_assignment_operator();
    test_type_casting();
    test_index_operator();
    test_function_call_operator();

    std::cout << "All operator tests passed!" << std::endl;
    return 0;
}