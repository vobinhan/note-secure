# Note Secure

A secure notes desktop application, developed incrementally in C++17.

## Current status

**Step 1 — Project Setup**

- C++17 and CMake project
- Core library separated from the executable
- GoogleTest unit-test target
- Compiler warnings enabled
- Optional AddressSanitizer + UndefinedBehaviorSanitizer

The Note domain model, database, cryptography and Qt UI are intentionally not implemented yet.

## Dependencies (Ubuntu 22.04)

```bash
sudo apt update
sudo apt install -y build-essential cmake git libgtest-dev
```

Ubuntu's `libgtest-dev` package provides GoogleTest CMake files on supported Ubuntu 22.04 package versions.

## Configure and build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j"$(nproc)"
```

## Run the application

```bash
./build/note-secure
```

Expected output:

```text
Note Secure v0.1.0
Project setup is ready.
```

## Run tests

```bash
ctest --test-dir build --output-on-failure
```

## Build with sanitizers

```bash
cmake -S . -B build-asan \
  -DCMAKE_BUILD_TYPE=Debug \
  -DNOTE_SECURE_ENABLE_SANITIZERS=ON

cmake --build build-asan -j"$(nproc)"
ctest --test-dir build-asan --output-on-failure
```

## Project structure

```text
note-secure/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── app/
│   └── main.cpp
├── include/
│   └── note_secure/
│       └── core.hpp
├── src/
│   └── core.cpp
└── tests/
    ├── test_main.cpp
    └── unit/
        └── core_test.cpp
```

## Next step

Step 2 — implement the domain model (`Note`, `NoteId`), validation rules and unit tests.
