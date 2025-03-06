#include <iostream>
#include <cassert>

#include "../myjson.hpp"

void test_json_object_methods()
{
    json::JSON jsonObject(json::Type::OBJECT);

    // Test adding values
    jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
    jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    jsonObject.Add("height", json::JSON(json::Type::DOUBLE, 7.5));
    jsonObject.Add("is_student", json::JSON(json::Type::BOOLEAN));
    jsonObject.Add("is_learning", json::JSON(json::Type::NONE));
    jsonObject.Add("books", json::JSON(json::Type::ARRAY));

    assert(jsonObject.Get("name").IsString() == true);
    assert(jsonObject.Get("age").IsNumber() == true);
    assert(jsonObject.Get("height").IsNumber() == true);
    assert(jsonObject.Get("is_learning").IsNone() == true);
    assert(jsonObject.Get("books").IsArray() == true);
    assert(jsonObject.IsObject() == true);

    assert(jsonObject.HasKey("name"));
    assert(jsonObject.HasKey("age"));
    assert(jsonObject.HasKey("height"));
    assert(jsonObject.HasKey("is_student"));
    assert(jsonObject.HasKey("is_learnig"));
    assert(jsonObject.HasKey("books"));

    assert(jsonObject.Get("name").String() == "John");
    // assert(static_cast<int>(jsonObject.Get("age")) == 30);
    // assert(static_cast<bool>(jsonObject.Get("is_student")) == false);

    // Test replacing values
    jsonObject.Replace("age", json::JSON(json::Type::INTEGER, 20));
    assert(jsonObject.Get("age").String() == "20");

    // Test deleting values
    jsonObject.Delete("age");
    assert(!jsonObject.HasKey("age"));

    std::cout << "JSON object methods test passed." << std::endl;
}

void test_json_array_methods()
{
    json::JSON jsonArray(json::Type::ARRAY);

    // Test adding values
    jsonArray.Add(0, json::JSON(json::Type::STRING, "John"));
    jsonArray.Add(1, json::JSON(json::Type::INTEGER, 30));
    jsonArray.Add(2, json::JSON(json::Type::DOUBLE, 7.5));
    jsonArray.Add(3, json::JSON(json::Type::BOOLEAN));
    jsonArray.Add(4, json::JSON(json::Type::NONE));
    jsonArray.Add(5, json::JSON(json::Type::OBJECT));

    assert(jsonObject.Get(0).IsString() == true);
    assert(jsonObject.Get(1).IsNumber() == true);
    assert(jsonObject.Get(2).IsNumber() == true);
    assert(jsonObject.Get(3).IsNone() == true);
    assert(jsonObject.Get(4).IsObject() == true);
    assert(jsonObject.IsArray() == true);

    assert(jsonObject.HasKey(0));
    assert(jsonObject.HasKey(1));
    assert(jsonObject.HasKey(2));
    assert(jsonObject.HasKey(3));
    assert(jsonObject.HasKey(4));
    assert(jsonObject.HasKey(5));

    assert(jsonArray.HasKey(0));
    assert(jsonArray.HasKey(1));
    assert(jsonArray.HasKey(2));

    // assert(jsonArray.Get(0).String() == "Apple");
    // assert(jsonArray.Get(1).String() == "Banana");
    // assert(jsonArray.Get(2).String() == "Cherry");

    // Test replacing values
    jsonArray.Replace(1, json::JSON(json::Type::INTEGER, 20));
    assert(jsonArray.Get(1).String() == "20");

    // Test deleting values
    jsonArray.Delete(2);
    assert(!jsonArray.HasKey(2));

    std::cout << "JSON array methods test passed." << std::endl;
}

int main()
{
    test_json_object_methods();
    test_json_array_methods();

    std::cout << "All JSON methods tests passed!" << std::endl;
    return 0;
}