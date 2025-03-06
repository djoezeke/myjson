#include <iostream>
#include <fstream>
#include "../myjson.hpp"

void exampleUsage()
{
    // std::cout << "----------------------------------------------------" << std::endl;

    // std::cout << "Person: " << dump(NULL) << std::endl;

    std::ifstream file("myjson.json");
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    if (!file.is_open())
    {
        std::cerr << "Error: Couldn't open file " << std::endl;
    }

    // Read the file contents into a string
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    json::JSON jsonArray = json::load(code);
    // std::cout << jsonArray.String() << std::endl;
    std::cout << "Name: " << jsonArray.Get("name").String() << std::endl;
    // std::cout << "Second: " << jsonArray.Get(1).String() << std::endl;

    // std::cout << jsonArray["user"]["name"].String() << std::endl;
    // std::cout << jsonArray.String() << std::endl;
    // std::cout << "----------------------------------------------------" << std::endl;
    // json::print(jsonArray, true);
    // std::cout << "\nFirst: " << jsonArray.Get(0).String() << std::endl;
    // std::cout << "Second: " << jsonArray.Get(1).String() << std::endl;
    // std::cout << "Third: " << jsonArray.Get(2).String() << std::endl;

    // std::cout << "----------------------------------------------------" << std::endl;

    // std::cout << "Person: " << dump(jsonArray) << std::endl;

    // // Print the JSON array
    // std::cout << "JSON Array:" << std::endl;
    // // json::print(jsonArray);

    // // Modify a value in the JSON array
    // jsonArray.Replace(1, json::JSON(json::Type::STRING, "mango"));
    // std::cout << "\nUpdated Second Fruit: " << jsonArray.Get(1).String() << std::endl;

    ///////////////////////////////////////////////////////////

    // // Create an empty JSON object
    // json::JSON jsonObject(json::Type::OBJECT);

    // // Add key-value pairs to the JSON object
    // jsonObject.Add("name", json::JSON(json::Type::STRING, "John Doe"));
    // jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    // jsonObject.Add("is_student", json::JSON(json::Type::BOOLEAN, false));

    // std::cout << "----------------TYPE------------------" << std::endl;
    // std::cout << "Type: " << (int)jsonObject.Type() << std::endl;
    // std::cout << "IsArray: " << jsonObject.IsArray() << std::endl;
    // std::cout << "IsBool: " << jsonObject.IsBool() << std::endl;
    // std::cout << "IsNil: " << jsonObject.IsNil() << std::endl;
    // std::cout << "IsNumber: " << jsonObject.IsNumber() << std::endl;
    // std::cout << "IsObject: " << jsonObject.IsObject() << std::endl;

    // std::cout << "----------------OTHERS------------------" << std::endl;
    // std::cout << "Empty: " << jsonObject.Empty() << std::endl;

    // std::cout << "----------------OBJECTS------------------" << std::endl;
    // std::cout << "Haskey: " << jsonObject.HasKey("hello") << std::endl;
    // std::cout << "Value Type: " << (int)jsonObject.ValueType("hello") << std::endl;
    // std::cout << "GetName: " << jsonObject.Get("name").String() << std::endl;
    // std::cout << "Get Age: " << jsonObject.Get("age").String() << std::endl;
    // std::cout << "Is Student: " << jsonObject.Get("is_student").String() << std::endl;

    // // Create a JSON array
    // json::JSON jsonArray(json::Type::ARRAY);

    // // Add key-value pairs to the JSON array
    // jsonArray.Add(0, json::JSON(json::Type::STRING, "apple"));
    // jsonArray.Add(1, json::JSON(json::Type::STRING, "banana"));
    // jsonArray.Add(2, json::JSON(json::Type::STRING, "cherry"));

    // std::cout << "----------------ARRAYS------------------" << std::endl;
    // std::cout << "First: " << jsonArray.Get(0).String() << std::endl;
    // std::cout << "Second: " << jsonArray.Get(1).String() << std::endl;
    // std::cout << "Third: " << jsonArray.Get(2).String() << std::endl;

    // // std::cout << "----------------------------------------------------" << std::endl;
    // // json::print(jsonArray);
    // std::cout << "----------------------------------------------------" << std::endl;
    // std::cout << jsonArray.String();
    // std::cout << "----------------------------------------------------" << std::endl;
    // // std::cout << jsonArray.String();
    // std::cout << "----------------------------------------------------" << std::endl;
    // // std::cout << json::dump(jsonArray) << std::endl;
    // // std::cout << "----------------------------------------------------" << std::endl;

    // std::vector<std::string> ky;
    // ky = jsonArray.Keys();

    // for (size_t i = 0; i < ky.size(); i++)
    // {
    //     std::cout << "Key" << i << ":" << ky[i] << std::endl;
    // }

    // for (auto i : ky)
    // {
    //     std::cout << "Key :" << i << std::endl;
    // }

    // std::cout << "Person: " << dump(jsonObject) << std::endl;

    // // Print the JSON object
    // std::cout << "JSON Object:" << std::endl;
    // // json::print(jsonObject);

    // // Add the array to the JSON object
    // jsonObject.Add("fruits", jsonArray);

    // // Modify a value in the JSON object
    // jsonObject.Replace("age", json::JSON(json::Type::INTEGER, 31));
    // std::cout << "\nUpdated Age: " << jsonObject.Get("age").String() << std::endl;

    // Compare two JSON objects
    // json::JSON jsonObject2(json::Type::OBJECT);

    // jsonObject2.Add("name", json::JSON(json::Type::STRING, "John Doe"));
    // jsonObject2.Add("age", json::JSON(json::Type::INTEGER, 31));
    // jsonObject2.Add("is_student", json::JSON(json::Type::BOOLEAN, false));
    // jsonObject2.Add("fruits", jsonArray);

    // if (jsonObject == jsonObject2)
    // {
    //     std::cout << "\nThe two JSON objects are equal." << std::endl;
    // }
    // else
    // {
    //     std::cout << "\nThe two JSON objects are not equal." << std::endl;
    // }

    // // Retrieve and print values from the JSON array
    // json::JSON fruits = jsonObject.Get("fruits");
    // std::cout << "\nFruits:" << std::endl;
    // // for (int i = 0; i < 3; ++i)
    // // {
    // //     std::cout << "- " << fruits.Get(i).String() << std::endl;
    // // }
}

int main()
{
    exampleUsage();
    return 0;
}

// g++ -o example_usage example_usage.cpp myjson.cpp
// g++ -o test test_myjson.cpp myjson.cpp

// ./example_usage

// add
// dump seg fault
// print seg fault
// replace seg fault
// string seg fault