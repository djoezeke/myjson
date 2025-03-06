#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>

#include "../myjson.hpp"

// Helper function to write JSON to a file
void write_json_to_file(const std::string &filename, const json::JSON &json)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }
    // file << json::dump(json);
    file.close();
}

// Test writing JSON to a file
void test_write_json_to_file()
{
    json::JSON jsonObject(json::Type::OBJECT);
    jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
    jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    jsonObject.Add("is_student", json::JSON(json::Type::BOOLEAN, false));

    write_json_to_file("test_output.json", jsonObject);

    std::ifstream file("test_output.json");
    assert(file.is_open());
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string expectedOutput = R"({"name":"John","age":30,"is_student":false})";
    assert(buffer.str() == expectedOutput);
    std::cout << "Test write_json_to_file passed." << std::endl;
}

int main()
{
    test_write_json_to_file();
    std::cout << "All file operation tests passed!" << std::endl;
    return 0;
}