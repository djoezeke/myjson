<p align="center"><h1 align="center">MY JSON 🚀</h1></p>
<p align="center">
    <em><code>C/C++ Json Serializer and Deserializer Library.
</code></em>
</p>
<p align="center">
    <img src="https://img.shields.io/github/license/djoezeke/jsonfy?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
    <img src="https://img.shields.io/github/last-commit/djoezeke/jsonfy?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
    <img src="https://img.shields.io/github/languages/top/djoezeke/jsonfy?style=default&color=0080ff" alt="repo-top-language">
    <img src="https://img.shields.io/github/languages/count/djoezeke/jsonfy?style=default&color=0080ff" alt="repo-language-count">
</p>
<p align="center"></p>
<p align="center">
</p>
<br>

<details><summary>Table of Contents</summary>

- [📍 Overview](#-overview)
- [👾 Features](#-features)
- [📁 Project Structure](#-project-structure)
- [🚀 Getting Started](#-getting-started)
  - [☑️ Prerequisites](#-prerequisites)
  - [⚙️ Installation](#-installation)
  - [🤖 Usage](#🤖-usage)
  - [🧪 Testing](#🧪-testing)
- [📌 Project Roadmap](#-project-roadmap)
- [🔰 Contributing](#-contributing)
- [🎗 License](#-license)
- [🙌 Acknowledgments](#-acknowledgments)

</details>

## 📍 Overview

Jsonfy is a lightweight JSON parsing and serialization library for C++. It provides an easy-to-use interface for working with JSON data, including parsing JSON strings, creating JSON objects, and serializing JSON objects to strings.

### lookup

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

---


## Features ✨

- Parse JSON strings into JSON objects
- Serialize JSON objects to strings
- Support for JSON types: null, boolean, number, string, array, and object
- Easy-to-use API for manipulating JSON data

## 📁 Project Structure

```sh
└── Jsonfy/
    ├── CMakeLists.txt
    ├── LICENSE
    │
    ├── myjson.hpp
    ├── myjson.cpp
    │
    ├── tests
    │   ├── test.c
    │   └── test.cpp
    └── examples
        ├── basic.c
        ├── basic.cpp
        └── sample.cpp
```

## 🚀 Getting Started

<div align="center">
<img src="readme/use-this-template-button.png">
</div>

### ☑️ Prerequisites

Before getting started with jsonfy, ensure your runtime environment meets the following requirements:

- **Programming Language:** C, Cpp
- **Package Manager:** Cmake

### Installation 🛠️

To use Jsonfy in your project, simply include the `myjson.hpp` and `myjson.cpp` files in your project.

1. Clone the repository:

```sh
❯ git clone https://github.com/djoezeke/jsonfy.git
```

2. Include the header and source files in your project:

```cpp
   #include "myjson.hpp"
```

3. Compiling your project:

```sh
❯ g++ my_source.cpp myjson.cpp -o main
```

### Usage 📚

#### Creating JSON

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

#### Deserialization

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

#### Serialization

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

#### Pretty Printing

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

### 🧪 Testing

Run the test suite using the following command:
**Using `cmake`** &nbsp; [<img align="center" src="" />]()

```sh
❯ echo 'INSERT-TEST-COMMAND-HERE'
```

## Building

To configure and build the project, do the following from the root directory of the repository:

```bash
mkdir build
cd build
cmake ..
```

This will configure the CMake and will generate platform-specific build files. To build, execute the following from within the build directory:

```bash
cmake --build .
```

Or build using whatever generated build system CMake produced.

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

---

## 🔰 Contributing

- **💬 [Join the Discussions](https://github.com/djoezeke/jsonfy/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/djoezeke/jsonfy/issues)**: Submit bugs found or log feature requests for the `jsonfy` project.
- **💡 [Submit Pull Requests](https://github.com/djoezeke/jsonfy/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/djoezeke/jsonfy
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/djoezeke/jsonfy/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=djoezeke/jsonfy">
   </a>
</p>
</details>

---


## 📄 License 

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## 📧 Contact 

For any questions or suggestions, please open an issue or contact the repository owner.

---
## 🙌 Acknowledgments

### References

---

