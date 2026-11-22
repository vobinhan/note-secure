cmake_minimum_required(VERSION 3.28)

project(note_secure
    VERSION 0.1.0
    DESCRIPTION "A secure notes application"
    LANGUAGES CXX
)

option(NOTE_SECURE_BUILD_TESTS "Build unit tests" ON)
option(NOTE_SECURE_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(note_secure_core
    src/core.cpp
)

target_include_directories(note_secure_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(note_secure_core
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(note-secure
    app/main.cpp
)

target_link_libraries(note-secure
    PRIVATE
        note_secure_core
)

if(NOTE_SECURE_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(SANITIZER_FLAGS -fsanitize=address,undefined -fno-omit-frame-pointer)

    target_compile_options(note_secure_core PRIVATE ${SANITIZER_FLAGS})
    target_link_options(note_secure_core PRIVATE ${SANITIZER_FLAGS})

    target_compile_options(note-secure PRIVATE ${SANITIZER_FLAGS})
    target_link_options(note-secure PRIVATE ${SANITIZER_FLAGS})
endif()

if(NOTE_SECURE_BUILD_TESTS)
    enable_testing()

    find_package(GTest CONFIG QUIET)
    if(NOT GTest_FOUND)
        find_package(GTest REQUIRED)
    endif()

    add_executable(note-secure-tests
        tests/test_main.cpp
        tests/unit/core_test.cpp
    )

    target_link_libraries(note-secure-tests
        PRIVATE
            note_secure_core
            GTest::gtest_main
    )

    target_compile_options(note-secure-tests
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

    if(NOTE_SECURE_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(note-secure-tests PRIVATE ${SANITIZER_FLAGS})
        target_link_options(note-secure-tests PRIVATE ${SANITIZER_FLAGS})
    endif()

    include(GoogleTest)
    gtest_discover_tests(note-secure-tests)
endif()
