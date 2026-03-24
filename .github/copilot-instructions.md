# Myjson - AI Coding Agent Guide

## Project Overview

Myjson is a modern, lightweight JSON parsing and serialization library for C/C++. The library is designed for high performance, low memory overhead, and ease of use, with a focus on modern C++ features and best practices. It provides a dual API: a C++11 interface for C++ projects and a C11-compatible interface for C projects, both sharing the same underlying implementation. Myjson supports a wide range of JSON features, including all standard JSON types, user-defined literals for parsing, and customizable serialization options.

## Architecture

This is a modern, JSON parsing and serialization library for C/C++. It provides **dual APIs**: a C++11 interface (`myjson.hpp`,`myjson.cpp`) and a C11-compatible interface (`myjson.h`,`myjsonc.cpp`), both sharing implementation in `src/`. The C API is a thin wrapper around the C++ implementation, allowing C projects to use Myjson without C++ dependencies.

### Dual API Design

- **C++ API** (`include/myjson/myjson.hpp`): Modern interface with `myjson::json` class, exceptions, and user-defined literals
- **C API** (`include/myjson/myjson.h`): C11-compatible wrapper around C++ implementation via `src/myjsonc.cpp`
- **Shared implementation** in `src/myjson.cpp` guarded by `#ifdef MYJSON_IMPLEMENTATION`

### Key Components

- `myjson::json` - Main JSON value class using variant-like design for all JSON types
- `myjson::literals::operator""_json` - String literal parsing (`"[1,2,3]"_json`)
- `myjson::detail` namespace - Internal utilities (encoding, parsing, output)
- C++20 module interface available at `src/modules/myjson.cppm`

## Build System

### Multi-Build Support

The project supports **three build systems** with feature parity:

1. **CMake** (primary) - Full featured, used for CI/CD
2. **Bazel** (`BUILD.bazel`) - Alternative for Bazel users
3. **Meson** (`meson.build`) - Alternative for Meson users

### CMake Workflow (Primary)

```bash
# Configure using presets
cmake --preset develop        # Debug build with tests/examples
cmake --preset default        # Release build only

# Build
cmake --build build/develop

# Run tests
cd build/develop && ctest
```

**CMake Presets** (`CMakePresets.json`):

- `develop` - Debug build with `CMAKE_EXPORT_COMPILE_COMMANDS=ON`, tests and examples enabled
- `default` - Release build, library only

### Custom CMake Macros

The `myjson_make_library()` macro (defined in `CMakeLists.txt:151-238`) standardizes library creation:

- Handles static/shared library selection via `MYJSON_STATIC`
- Sets C11/C++17 requirements automatically
- Configures platform-specific library naming (Windows DLL suffixes, import libraries)
- Applies UTF-8 source encoding for MSVC
- Use pattern: `myjson_make_library(LibName SOURCES src/file.cpp DEPENDS Myjson::OtherLib)`

### Build Options

Key CMake options (use `-D` flag or `ccmake`):

- `MYJSON_BUILD_SHARED=ON/OFF` - Build shared libraries (default: ON)
- `MYJSON_BUILD_TESTS=ON/OFF` - Enable test suite (default: ON for top-level)
- `MYJSON_BUILD_EXAMPLES=ON/OFF` - Build examples (default: ON for top-level)
- `MYJSON_ENABLE_SANITIZERS=ON` - Enable UBSan for development
- `MYJSON_ENABLE_CLANG_FORMAT=ON` - Add clang-format target

## Testing & Quality

### Test Framework

- Uses **Catch2 v3.7.0** (vendored in `tests/vendor/Catch2/` or fetched via FetchContent)
- Test structure: `tests/c/Main.test.cpp` (C API), `tests/cxx/Main.test.cpp` (C++ API)
- Run via `ctest` in build directory or `cmake --build build/develop --target test`

### Code Quality Tools

- **Valgrind** - Memory leak detection (configure with `-DMYJSON_USE_VALGRIND=ON`)
- **Clang-Tidy** - Static analysis (`cmake --build . --target clang-tidy`)
- **Clang-Format** - Code formatting (`cmake --build . --target clang-format`)
- **Sanitizers** - Enable with `MYJSON_ENABLE_SANITIZERS=ON` (adds `-fsanitize=undefined`)

## Coding Conventions

### Namespace Structure

```cpp
namespace myjson {
    inline namespace literals { /* user-defined literals */ }
    namespace detail { /* internal implementation */ }

    class json { /* public API */ };
}
```

### API Patterns

- **Parse**: `myjson::json obj = myjson::load(jsonString);`
- **Serialize**: `std::string str = myjson::dump(obj);`
- **Pretty print**: `myjson::print(obj, /*pretty=*/true);`
- **Error handling**: Throws `myjson::Exception` for all errors
- **Type checking**: JSON types via `Type::OBJECT`, `Type::ARRAY`, `Type::STRING`, etc.

### Version Management

- Version defined in three places: `CMakeLists.txt:21-24`, `meson.build:11`, README
- Uses version namespace pattern: `MYJSON_VERSION_MAJOR/MINOR/PATCH` macros
- Build system must keep versions synchronized

## Development Workflows

### Adding New Tests

1. Add test cases to `tests/cxx/Main.test.cpp` or `tests/c/Main.test.cpp`
2. Use Catch2 macros: `TEST_CASE("description", "[tag]")`
3. Run via `ctest --output-on-failure` in build directory

### Modifying Build Configuration

- Edit `CMakeLists.txt` for CMake (main file ~510 lines with extensive documentation)
- Keep `BUILD.bazel` and `meson.build` in sync for alternative build systems
- Update `CMakePresets.json` for new configuration patterns

### Documentation

- API docs generated with **Doxygen** (`docs/doxygen/Doxyfile.in`)
- User docs with **MkDocs** (`docs/mkdocs/mkdocs.yml`)
- Build docs with `-DMYJSON_BUILD_DOCS=ON`

## Common Pitfalls

### Build System Issues

- **Windows library naming**: Static libs get `lib` prefix on MSVC to avoid conflicts with import libraries
- **UTF-8 encoding**: Required for MSVC (`/utf-8` applied automatically)
- **C++ standard**: Minimum C++11 supported, C++17 recommended and default

### API Usage

- C API (`myjson.h`) requires C11 support minimum
- C++ modules require C++20 and module support
- Both APIs are **thread-safe** for read-only operations, not for concurrent modifications

### Testing

- Catch2 must be built with C++17 to match library (`target_compile_features(Catch2 PRIVATE cxx_std_17)`)
- Tests are not built by default when used as subproject

## File Organization Principles

- `include/myjson/` - Public headers (dual API)
- `src/` - Implementation files (both C++ and C wrapper)
- `src/modules/` - C++20 module interface
- `tests/{c,cxx}/` - Separate test suites for each API
- `examples/` - Usage demonstrations
- `cmake/` - CMake package config templates

## Integration Patterns

When adding Myjson to projects:

- **CMake**: Use `find_package(Myjson)` or `add_subdirectory()`, link `Myjson::Myjson` or `Myjson::MyjsonC`
- **Bazel**: `deps = ["@myjson//:myjson"]` or `@myjson//:myjsonc`
- **Meson**: `myjson_dep = dependency('myjson')`
