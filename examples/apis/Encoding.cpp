/**
 * @example Encoding.cpp
 * @brief Demonstrates UTF encoding support in myjson.
 *
 * This example shows:
 * - Working with UTF-8 strings
 * - Properties of different character encodings
 * - String serialization in JSON
 * - Unicode character handling
 */

#include <iostream>
#include <myjson/myjson.hpp>

int main()
{
    using namespace myjson;

    // Create JSON with UTF-8 strings
    json multilingual = json::object();
    multilingual["english"] = "Hello, World!";
    multilingual["spanish"] = "¡Hola, Mundo!";
    multilingual["french"] = "Bonjour, le monde!";
    multilingual["german"] = "Hallo, Welt!";
    multilingual["japanese"] = "こんにちは、世界!"; // Hello, World in Japanese
    multilingual["emoji"] = "Hello 👋 World 🌍!";

    std::cout << "Multilingual JSON:" << std::endl;
    std::cout << multilingual.dump(2) << std::endl;

    // Verify string types
    std::cout << "\nString verification:" << std::endl;
    for (auto &entry : multilingual)
    {
        const auto &value = entry.second.as_string();
        std::cout << "  " << entry.first << " (length: " << value.length() << " bytes)" << std::endl;
    }

    // UTF-8 string escaping in JSON
    json escaped = json::object();
    escaped["newline"] = "Line 1\nLine 2";
    escaped["tab"] = "Column1\tColumn2";
    escaped["backslash"] = "C:\\Users\\Documents";
    escaped["quote"] = "She said \"Hello!\"";

    std::cout << "\nEscaped characters (compact):" << std::endl;
    std::cout << escaped.dump() << std::endl;

    // Parse UTF-8 JSON string
    std::string json_str = R"({"greeting":"こんにちは","world":"地球"})";
    json parsed = json::parse(json_str);

    std::cout << "\nParsed UTF-8 JSON:" << std::endl;
    std::cout << "  greeting: " << parsed["greeting"].as_string() << std::endl;
    std::cout << "  world: " << parsed["world"].as_string() << std::endl;

    return 0;
}
