# MyJSON 🚀

MyJSON is a lightweight JSON parsing and serialization library for C++. It provides an easy-to-use interface for working with JSON data, including parsing JSON strings, creating JSON objects, and serializing JSON objects to strings.

## Features ✨

- Parse JSON strings into JSON objects
- Serialize JSON objects to strings
- Support for JSON types: null, boolean, number, string, array, and object
- Easy-to-use API for manipulating JSON data

## Installation 🛠️

To use MyJSON in your project, simply include the `myjson.hpp` and `myjson.cpp` files in your project.

1. Clone the repository:

   ```sh
   git clone https://github.com/djoezeke/MyJSON.git
   ```

2. Include the header and source files in your project:

   ```cpp
   #include "myjson.hpp"
   ```

3. Compiling your project:

   ```sh
   g++ my_source.cpp myjson.cpp -o main
   ```

## Usage 📚

### Creating JSON

To create a JSON object, use the `json::JSON` class:

```cpp
#include "myjson.hpp"

int main() {
    json::JSON jsonObject(json::Type::OBJECT);
    jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
    jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    jsonObject.Add("isStudent", json::JSON(json::Type::BOOLEAN, false));

    std::cout << jsonObject.String() << std::endl;

    return 0;
}
```

### Deserialization

To parse a JSON string into a JSON object, use the `load` function:
Deserialize a json `str` to a MYJSON `obj`.

```cpp
#include "myjson.hpp"

int main() {
    std::string jsonString = R"({"name": "John", "age": 30, "isStudent": false})";
    json::JSON jsonObject = json::load(jsonString);

    std::cout << "Name: " << jsonObject.Get("name").String() << std::endl;
    std::cout << "Age: " << static_cast<int>(jsonObject.Get("age")) << std::endl;
    std::cout << "Is Student: " << static_cast<bool>(jsonObject.Get("isStudent")) << std::endl;

    return 0;
}
```

### Serialization

To serialize a JSON object to a string, use the `dump` function:
Serialize `obj` to a JSON formatted `str`.

```cpp
    // out        : where to the result string.
    // indent     : whether to indent , for pretty print.
    // skipkeys   : whether to exclude keys in the result string.
    // default    : default string to return if error or null string.
    std::cout << json::dump(jsonObject,out= nullptr ,indent=true,skipkeys=False,default=None, sort_keys=False);
```

```cpp
#include "myjson.hpp"

int main() {
    json::JSON jsonObject(json::Type::OBJECT);
    jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
    jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    jsonObject.Add("isStudent", json::JSON(json::Type::BOOLEAN, false));

    std::string jsonString = json::dump(jsonObject);
    std::cout << jsonString << std::endl;

    return 0;
}
```

## Pretty Printing

code:

```cpp
#include "myjson.hpp"

int main() {
    json::JSON jsonObject(json::Type::OBJECT);
    jsonObject.Add("name", json::JSON(json::Type::STRING, "John"));
    jsonObject.Add("age", json::JSON(json::Type::INTEGER, 30));
    jsonObject.Add("isStudent", json::JSON(json::Type::BOOLEAN, false));

    std::cout << json::dump(jsonObject,indent=true,skipkeys=False);

    return 0;
}
```

output:

```sh
{
    "name": "John",
    "age": 30,
    "isStudent": false
}
```

## Contributing 🤝

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Make your changes and commit them with descriptive messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository.

## License 📄

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact 📧

For any questions or suggestions, please open an issue or contact the repository owner.

## lookup

```
    Supports the following objects and types by default:

    +-------------------+---------------+
    | MYJSON            | JSON          |
    +===================+===============+
    | Type::OBJECT      | object        |
    +-------------------+---------------+
    | Type::ARRAY       | array         |
    +-------------------+---------------+
    | Type::STRING      | string        |
    +-------------------+---------------+
    | Type::INTEGER     | number        |
    +-------------------+---------------+
    | Type::DOUBLE      | number        |
    +-------------------+---------------+
    | Type::BOOLEAN     | true          |
    +-------------------+---------------+
    | Type::BOOLEAN     | false         |
    +-------------------+---------------+
    | Type::NULL        | null          |
    +-------------------+---------------+

```

## Errors

```cpp
throw JSONDecodeError("Illegal trailing comma before end of object", s, comma_idx)
throw JSONDecodeError("Expecting property name enclosed in double quotes", s, end - 1)
throw JSONDecodeError("Expecting ',' delimiter", s, end - 1)
throw JSONDecodeError("Expecting value", s, err.value)
throw JSONDecodeError("Expecting property name enclosed in double quotes", s, end)
throw JSONDecodeError("Extra data", s, end)
throw TypeError(f'keys must be str, int, float, bool or None, 'f'not {key.__class__.__name__}')

```
