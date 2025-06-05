<p align="center"><h1 align="center">🚀 Jsonfy: Modern C++ JSON Library</h1></p>

<p align="center">
    <em><code>Lightweight, modern, and easy-to-use C++ JSON serializer & deserializer.</code></em>
</p>
<p align="center">
    <img src="https://img.shields.io/github/license/djoezeke/jsonfy?style=flat-square&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
    <img src="https://img.shields.io/github/last-commit/djoezeke/jsonfy?style=flat-square&logo=git&logoColor=white&color=0080ff" alt="last-commit">
    <img src="https://img.shields.io/github/languages/top/djoezeke/jsonfy?style=flat-square&color=0080ff" alt="repo-top-language">
    <img src="https://img.shields.io/github/languages/count/djoezeke/jsonfy?style=flat-square&color=0080ff" alt="repo-language-count">
</p>

---

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

**Jsonfy** is a modern, lightweight JSON parsing and serialization library for C++. It provides an easy-to-use interface for working with JSON data, including parsing JSON strings, creating JSON objects, and serializing JSON objects to strings.It provides a simple, type-safe API for working with JSON data in C++ projects.

---

## ✨ Features

- ⚡ **Fast**: Efficient parsing and serialization
- 🧩 **Type-safe**: Strong C++ type system for all JSON types
- 🛠️ **Easy API**: Intuitive interface for manipulating JSON objects and arrays
- 📝 **Modern C++**: Uses smart pointers, `std::variant`, and other C++17 features
- 🧪 **Tested**: Includes unit tests and examples
- 📦 **Header-only**: Just include and use!

---

## 📦 Supported Types

| Jsonfy Type      | JSON Type   | Example Value      |
|------------------|-------------|--------------------|
| `Type::OBJECT`   | object      | `{ "a": 1 }`       |
| `Type::ARRAY`    | array       | `[1, 2, 3]`        |
| `Type::STRING`   | string      | `"hello"`          |
| `Type::INTEGER`  | number      | `42`               |
| `Type::DOUBLE`   | number      | `3.14`             |
| `Type::BOOLEAN`  | true/false  | `true` / `false`   |
| `Type::NONE`     | null        | `null`             |

---

## 📁 Project Structure

```sh
Jsonfy/
├── CMakeLists.txt
├── LICENSE
├── myjson.hpp
├── myjson.cpp
├── tests/
│   ├── test.c
│   └── test.cpp
└── examples/
    ├── basic.c
    ├── basic.cpp
    └── sample.cpp
```

---


## 🚀 Getting Started

- **Programming Language:** C, Cpp
- **Package Manager:** Cmake

### ☑️ Prerequisites

Before getting started with jsonfy, ensure your runtime environment meets the following requirements:

- **C++17** or newer compiler
- **CMake** (for building examples/tests)

### Installation 🛠️

1. **Clone the repository:**
    ```sh
    git clone https://github.com/djoezeke/jsonfy.git
    ```

2. **Add to your project:**
    - Copy `myjson.hpp` and `myjson.cpp` into your project.
    - Or add as a submodule and include in your build.

3. **Include in your code:**
    ```cpp
    #include "myjson.hpp"
    ```

4. **Compile:**
    ```sh
    g++ my_source.cpp myjson.cpp -std=c++17 -o main
    ```
---

## 🤖 Usage

### Create JSON

```cpp
#include "myjson.hpp"
#include <iostream>

int main() {
    json::JSON obj(json::Type::OBJECT);
    obj.Add("name", json::JSON(json::Type::STRING, "Alice"));
    obj.Add("age", json::JSON(json::Type::INTEGER, 25));
    obj.Add("isStudent", json::JSON(json::Type::BOOLEAN, true));
    std::cout << obj.String() << std::endl;
}
```

### Parse (Deserialize) JSON

```cpp
#include "myjson.hpp"
#include <iostream>

int main() {
    std::string jsonStr = R"({"name": "Bob", "age": 30, "isStudent": false})";
    json::JSON obj = json::load(jsonStr);
    std::cout << "Name: " << obj.Get("name").String() << std::endl;
    std::cout << "Age: " << obj.Get("age").String() << std::endl;
    std::cout << "Is Student: " << obj.Get("isStudent").String() << std::endl;
}
```

### Serialize (Dump) JSON

```cpp
#include "myjson.hpp"
#include <iostream>

int main() {
    json::JSON obj(json::Type::OBJECT);
    obj.Add("project", json::JSON(json::Type::STRING, "Jsonfy"));
    obj.Add("stars", json::JSON(json::Type::INTEGER, 100));
    std::string jsonStr = json::dump(obj);
    std::cout << jsonStr << std::endl;
}
```

### Pretty Print

```cpp
#include "myjson.hpp"
#include <iostream>

int main() {
    json::JSON obj(json::Type::OBJECT);
    obj.Add("foo", json::JSON(json::Type::STRING, "bar"));
    obj.Add("baz", json::JSON(json::Type::INTEGER, 123));
    json::print(obj, true); // pretty print
}
```

Output:
```json
{"foo":"bar","baz":123}
```

---

## 🧪 Testing

To run tests:

```sh
mkdir build
cd build
cmake ..
cmake --build .
# Run the test executable (e.g., ./tests/test)
```

---

## 🛣️ Roadmap

- [ ] Pretty-print with indentation
- [ ] Unicode and UTF-8 support
- [ ] Custom serialization hooks
- [ ] More robust error messages
- [ ] Performance benchmarks

---

## 🐛 Error Handling

Jsonfy throws `json::Exception` for all parsing and runtime errors.  
You can catch and inspect errors as follows:

```cpp
try {
    auto obj = json::load("invalid json");
} catch (const json::Exception& ex) {
    std::cerr << "Jsonfy error: " << ex.what() << std::endl;
}
```

---

## 🤝 Contributing

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


## 📄 License 

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
