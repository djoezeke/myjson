#include <iostream>
#include <string>

void prettyPrintJson(const std::string &jsonString)
{
    bool inQuotes = false;
    int indentLevel = 0;
    const int indentSize = 4;

    for (size_t i = 0; i < jsonString.length(); ++i)
    {
        char currentChar = jsonString[i];

        if (currentChar == '\"')
        {
            inQuotes = !inQuotes;
            std::cout << currentChar;
        }
        else if (!inQuotes)
        {
            switch (currentChar)
            {
            case '{':
            case '[':
                std::cout << currentChar << "\n";
                indentLevel++;
                std::cout << std::string(indentLevel * indentSize, ' ');
                break;
            case '}':
            case ']':
                std::cout << "\n";
                indentLevel--;
                std::cout << std::string(indentLevel * indentSize, ' ') << currentChar;
                break;
            case ',':
                std::cout << currentChar << "\n"
                          << std::string(indentLevel * indentSize, ' ');
                break;
            case ':':
                std::cout << currentChar << " ";
                break;
            default:
                if (!isspace(currentChar))
                {
                    std::cout << currentChar;
                }
                break;
            }
        }
        else
        {
            std::cout << currentChar;
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::string jsonString = R"({
        "name": "John",
        "age": 30,
        "city": "New York",
        "isStudent": false,
        "courses": ["Math", "Science", "History"]
    })";

    prettyPrintJson(jsonString);

    return 0;
}