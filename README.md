<p align="center"><h1 align="center">🚀 Myjson: Modern C++ JSON Library</h1></p>

<p align="center">
    <em><code>Lightweight, modern, and easy-to-use C++ JSON serializer & deserializer.</code></em>
</p>
<p align="center">
    <img src="https://img.shields.io/github/license/djoezeke/myjson?style=flat-square&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
    <img src="https://img.shields.io/github/last-commit/djoezeke/myjson?style=flat-square&logo=git&logoColor=white&color=0080ff" alt="last-commit">
    <img src="https://img.shields.io/github/languages/top/djoezeke/myjson?style=flat-square&color=0080ff" alt="repo-top-language">
    <img src="https://img.shields.io/github/languages/count/djoezeke/myjson?style=flat-square&color=0080ff" alt="repo-language-count">
</p>

<!-- ## Table of contents -->

<details><summary>Table of Contents</summary>

- [📍 Overview](#-overview)
- [👾 Design Goals](#-design-goals)
- [👾 Features](#-features)
- [📁 Project Structure](#-project-structure)
- [🚀 Getting Started](#-getting-started)
  - [☑️ Prerequisites](#-prerequisites)
  - [🛠️ Integration](#-integration)
  - [🤖 Usage](#🤖-usage)
  - [🧪 Testing](#🧪-testing)
- [📌 Project Roadmap](#-project-roadmap)
- [ Support](#-support)
- [🔰 Contributing](#-contributing)
- [🙌 Acknowledgments](#-acknowledgments)
- [📄 License](#-license)

</details>

## 📍 Overview

<!-- ## About Myjson -->

**Myjson** is a modern, lightweight JSON parsing and serialization library for C++. It provides an easy-to-use interface for working with JSON data, including parsing JSON strings, creating JSON objects, and serializing JSON objects to strings.It provides a simple, type-safe API for working with JSON data in C++ projects.

<!-- ## About json -->

JSON(JavaScript Object Notation) is a light-weight data exchange format. More information about JSON can be obtained at [here](http://json.org/)

## Design Goals

Myjson has been developed with these design goals:

### 💼 **Portable**

The library depends only on C/C++ standards, and is carefully designed to work on many platforms so that Myjson can be imported into existing C or C++ projects written in either C11, C++11 or later.
Furthermore, the project supports [CMake](https://cmake.org/) and provides [the documentation exclusively for CMake integration](https://djoezeke.github.io/myjson/tutorials/cmake_integration).
Those characteristics allow existing C or C++ project using CMake for builds to quickly incorporate JSON support with just a little effort.

### 🪰 **Heavily Tested**

Myjson has been [unit-tested](https://github.com/djoezeke/myjson/tree/main/tests/) and its test suite covers 100% of lines and conditions of the codebase. (You can see the actual coverage [here](#).)  
We check with [Valgrind](https://valgrind.org) and the [Clang Sanitizers](https://clang.llvm.org/docs/index.html) that there are no runtime issues such as memory leak.  
Furthermore, the quality of our codebase has been checked with [Clang-Tidy](https://releases.llvm.org/14.0.0/tools/clang/tools/extra/docs/clang-tidy/index.html), [CodeQL](https://codeql.github.com/docs/) and [Codacy](https://www.codacy.com/).  
[GitHub Actions](https://docs.github.com/en/actions) workflows run against every commit pushed on the main & develop branches to ensure that the fkYAML library can be successfully built/tested with a variety of compilers, operating systems and C/C++ standards.  
See the [prerequisites](#-prerequisites) section for more details.

### 📝 **Well Documented**

[The documentation](https://djoezeke.github.io/myjson/) provides plenty of information so that users can understand what Myjson is and what they can achieve with Myjson.  
For instance, [the tutorial pages](https://djoezeke.github.io/myjson/tutorials/) show how you can read/write/customize using Myjson to handle JSON documents while creating a simple C/C++ project using CMake.  
Also, [API reference pages](https://djoezeke.github.io/myjson/api/) provide more detailed, exclusive descriptions with example usages for each Myjson API.

## ✨ Features

- ⚡ **Fast**: Efficient parsing and serialization
- 🧩 **Type-safe**: Strong C++ type system for all JSON types
- 🛠️ **Easy API**: Intuitive interface for manipulating JSON objects and arrays
- 📝 **Modern C++**: Uses smart pointers, `std::variant`, and other C++17 features
- 🧪 **Tested**: Includes unit tests and examples

More detailed descriptions are to be found on [GitHub Pages](https://djoezeke.github.io/myjson).

Here is the list you might want to know:

- [Tutorial](https://djoezeke.github.io/myjson/tutorials) - getting started
- [API references](https://djoezeke.github.io/myjson/api/) - all the details with examples

### 📓 Note

<!-- #### 📦 Supported Types

| Myjson Type     | JSON Type  | Example Value    |
| --------------- | ---------- | ---------------- |
| `Type::OBJECT`  | object     | `{ "a": 1 }`     |
| `Type::ARRAY`   | array      | `[1, 2, 3]`      |
| `Type::STRING`  | string     | `"hello"`        |
| `Type::INTEGER` | number     | `42`             |
| `Type::DOUBLE`  | number     | `3.14`           |
| `Type::BOOLEAN` | true/false | `true` / `false` |
| `Type::NONE`    | null       | `null`           | -->

<details closed>

<summary> 📁 Project Structure</summary>

```sh
Myjson/
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

</details>

## 🚀 Getting Started

### ☑️ Prerequisites

Please ensure your runtime environment meets the following requirements:

- **C++17** or newer compiler
- **CMake** (for building examples/tests)

Myjson uses following software, tools and services:

- [CMake](https://cmake.org/) as a general build tool
- (optional) [Catch2](https://github.com/catchorg/Catch2.git) for unit and performance testing
- (optional) [Mkdocs](http://) to build web documentation
- (optional) [Doxygen](http://www.doxygen.org) to build code documentation

### 🛠️ Integration

1. **Clone the repository:**

   ```sh
   git clone https://github.com/djoezeke/myjson.git
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

<!-- #### Using [CMake](https://cmake.org/)

<details closed>
<summary>Configuring and Building</summary>

</details>

#### Using [Meson]()

<details closed>
<summary>Configuring and Building</summary>

</details>

#### Using [Makefile](https://www.gnu.org/software/make/)

<details closed>
<summary>Testing and Building</summary>

> [!NOTE]
> Makefile support is limited

</details> -->

<!-- ## 🤖 Usage

Here are some examples to give you an idea how to use the library.

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
    obj.Add("project", json::JSON(json::Type::STRING, "Myjson"));
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
{ "foo": "bar", "baz": 123 }
```

### 🐛 Error Handling

Myjson throws `json::Exception` for all parsing and runtime errors.
You can catch and inspect errors as follows:

```cpp
try {
    auto obj = json::load("invalid json");
} catch (const json::Exception& ex) {
    std::cerr << "Myjson error: " << ex.what() << std::endl;
}
```

More examples are available [here](https://github.com/djoezeke/myjson/tree/main/examples).

Besides the examples above, you may want to:

→ Check the [documentation](https://djoezeke.github.io/myjson/)\
→ Browse the [standalone example files](https://github.com/djoezeke/json/tree/main/examples)\
→ Read the full [API Documentation](https://djoezeke.github.io/myjson/api) with self-contained examples for every function

## 🧪 Testing

> [!NOTE]
> Make sure a CMake executable path has been added to your PATH in advance.

You can execute the unit tests with the following commands :

```sh
mkdir build
cd build
cmake ..
cmake --build .
# Run the test executable (e.g., ./tests/test)
```

### Benchmarking

Though efficiency is not everything, speed and memory consumption are very important characteristics for C++ developers. Regarding speed, benchmarking scores are now available with [the dedicated benchmarking tool](./tests/benchmark/README.md) for the parsing.
The following tables are created from the benchmarking results in the following environment:

- CPU: Intel Core i5-2430M @2.40GHz
- RAM 6.00 GB (5.78 GB usable)
- OS: Windows 11 Pro
- Compiler: GCC 14.2.0

### Parsing [File](https://github.com/djoezeke/myjson/blob/main/tests/json/)

| Benchmark | processed bytes per second (Release) |
| --------- | ------------------------------------ |
| Myjson    | 00.0000Mi/s                          | -->

## Support

🤔 If you have a **question**, please check if it is already answered in the [**FAQ**](https://djoezeke.github.io/myjson/faq/) or the [**Q&A**](https://github.com/djoezeke/myjson/discussions/categories/q-a) section. If not, please [**ask a new question**](https://github.com/djoezeke/myjson/discussions/new) there.

📓 If you want to **learn more** about how to use the library, check out the rest of the [**README**](#examples), have a look at [**code examples**](https://github.com/djoezeke/myjson/tree/main/examples), or browse through the [**help pages**](https://djoezeke.github.io/myjson/faq/).

🚧 If you want to understand the **API** better, check out the [**API Reference**](https://djoezeke.github.io/myjson/api/).
🐞 If you found a **bug**, please check the [**FAQ**](https://djoezeke.github.io/myjson/faq/) if it is a known issue or the result of a design decision. Please also have a look at the [**issue list**](https://github.com/djoezeke/myjson/issues) before you [**create a new issue**](https://github.com/djoezeke/myjson/issues/new/choose). Please provide as much information as possible to help us understand and reproduce your issue.

## 🤝 Contributing

- **💬 [Join the Discussions](https://github.com/djoezeke/myjson/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/djoezeke/myjson/issues)**: Submit bugs found or log feature requests for the `myjson` project.
- **💡 [Submit Pull Requests](https://github.com/djoezeke/myjson/blob/main/.github/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/djoezeke/myjson
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

See the [CONTRIBUTING.md](https://github.com/djoezeke/myjson/blob/main/.github/CONTRIBUTING.md) file for detailed information.

</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/djoezeke/myjson/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=djoezeke/myjson">
   </a>
</p>
</details>

## 🙌 Acknowledgments

We would like to express our gratitude to the following projects and individuals whose work made this project possible:

- [**Catch2**](https://github.com/catchorg/Catch2) as a unit-test framework.
- [**Clang**](https://clang.llvm.org) for coding style checks, and static/runtime analysis.
- [**CMake**](https://cmake.org) for build automation.
- [**Google Benchmark**](https://github.com/google/benchmark) to implement the benchmarks.
- [**Material for MkDocs**](https://squidfunk.github.io/mkdocs-material/) for the style of the documentation site
- [**MkDocs**](https://www.mkdocs.org) for the documentation site.
- [**Valgrind**](https://valgrind.org) for memory leak check & correct memory management.
- [**GitHub Changelog Generator**](https://github.com/skywinder/github-changelog-generator) to generate the [ChangeLog]().

The open-source community for their invaluable libraries, tutorials, and support.

### With thanks to:

<!-- - **[](https://github.com/)** - Fixed a bug -->

> [!NOTE]
> If you feel your work should be acknowledged here, please open an issue or pull request.

### References

- [myxml](https://github.com/djoezeke/myxml/) : A C/C++ XML Library.
- [myyaml](https://github.com/djoezeke/myyaml/) : A C/C++ YAML Library.
- [mytoml](https://github.com/djoezeke/mytoml/) : A C/C++ TOML Library.

### More Reading

## 📄 License

This project is protected under the [MIT](LICENSE) License.

<!-- <picture>
  <source
    media="(prefers-color-scheme: dark)"
    srcset="
      https://api.star-history.com/svg?repos=myjson/djoezeke&type=Date&theme=dark
    "
  />
  <source
    media="(prefers-color-scheme: light)"
    srcset="
      https://api.star-history.com/svg?repos=myjson/djoezeke&type=Date
    "
  />
  <img
    alt="Star History Chart"
    src="https://api.star-history.com/svg?repos=myjson/djoezeke&type=Date"
  />
</picture> -->
