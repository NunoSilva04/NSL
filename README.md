# NSL

NSL is my own standard library project for C++, currently in early development.

## Building on Linux

### Requirements

- CMake 3.25 or newer
- Clang / LLVM (`clang++`)
- Ninja

From the repository root, list the available workflows and run the Linux Debug workflow, currently the only one available.

```sh
cmake --workflow --list-presets
cmake --workflow --preset nsl_linux_debug
```

This configures and builds NSL in Debug mode. The static library is generated at `Lib/libnsl.a`, with build files in `Build/Linux/Debug/`.

## Install

From the repository root, run the following after building.

```sh
sudo cmake --install Build/Linux/Debug
```

This installs the library, headers, and CMake package under `/usr/local/`.

## Use in a project

Create a separate project with these two files.

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(example LANGUAGES CXX)

find_package(nsl CONFIG REQUIRED)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE nsl::nsl)
```

`main.cpp`:

```cpp
#include <iostream>
#include <nsl/nsl_math.hpp>

int main() {
    std::cout << get_4() << '\n';
}
```

From the example project's directory, build and run:

```sh
cmake -S . -B build
cmake --build build
./build/example
```

The example prints `4`.

## Uninstall

From the NSL repository root, run the following.

```sh
sudo cmake --build --preset nsl_linux_debug_build --target uninstall
```
