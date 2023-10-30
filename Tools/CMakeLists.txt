cmake_minimum_required(VERSION 3.27.6)

project(tools VERSION 0.0.1 LANGUAGES C CXX ASM DESCRIPTION "8 Bit Tools")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(ASSEMBLER assembler)
set(OBJDUMP objdump)
set(ASSEMBLER_TEST assembler_test)
set(OBJDUMP_TEST objdump_test)

add_executable(${ASSEMBLER})
add_executable(${ASSEMBLER_TEST})
add_executable(${OBJDUMP})
add_executable(${OBJDUMP_TEST})

target_sources(${ASSEMBLER}
    PRIVATE
    Assembler/Assembler.cpp
    Assembler/main.cpp
    Common/Helpers.cpp
    Common/Instructions.cpp
)
target_include_directories(${ASSEMBLER}
    PUBLIC
    Assembler/
    Common/
)
set(${ASSEMBLER}_PUBLIC_HEADERS
    Assembler/Assembler.h
    Common/Helpers.h
    Common/Instructions.h
)
target_compile_options(${ASSEMBLER}
PRIVATE
    -g
    -Wall
    -Wpedantic
    -Wextra
    -pthread
    --coverage
    -O0
)
target_link_libraries(${ASSEMBLER}
    gcov
)

target_sources(${OBJDUMP}
    PRIVATE
    ObjDump/ObjDump.cpp
    ObjDump/main.cpp
    Common/Helpers.cpp
    Common/Instructions.cpp
)
target_include_directories(${OBJDUMP}
    PUBLIC
    ObjDump/
    Common/
)
set(${OBJDUMP}_PUBLIC_HEADERS
    ObjDump/ObjDump.h
    Common/Helpers.h
    Common/Instructions.h
)
target_compile_options(${OBJDUMP}
PRIVATE
    -g
    -Wall
    -Wpedantic
    -Wextra
    -pthread
    --coverage
    -O0
)
target_link_libraries(${OBJDUMP}
    gcov
)

include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
target_sources(${ASSEMBLER_TEST}
    PRIVATE
    Assembler/Assembler.cpp
    Assembler/test/AssemblerTest.cpp
    Common/Helpers.cpp
    Common/Instructions.cpp
)
target_include_directories(${ASSEMBLER_TEST}
    PUBLIC
    Assembler/
    Common/
)
set(${ASSEMBLER_TEST}_PUBLIC_HEADERS
    Assembler/Assembler.h
    Common/Helpers.h
    Common/Instructions.h
)
target_compile_options(${ASSEMBLER_TEST}
PRIVATE
    -g
    -Wall
    -Wpedantic
    -Wextra
    -pthread
    --coverage
    -O0
)
target_link_libraries(${ASSEMBLER_TEST}
    gcov
    GTest::gtest_main
)

target_sources(${OBJDUMP_TEST}
    PRIVATE
    ObjDump/ObjDump.cpp
    ObjDump/test/ObjDumpTest.cpp
    Common/Helpers.cpp
    Common/Instructions.cpp
)
target_include_directories(${OBJDUMP_TEST}
    PUBLIC
    ObjDump/
    Common/
)
set(${OBJDUMP_TEST}_PUBLIC_HEADERS
    ObjDump/ObjDump.h
    Common/Helpers.h
    Common/Instructions.h
)
target_compile_options(${OBJDUMP_TEST}
PRIVATE
    -g
    -Wall
    -Wpedantic
    -Wextra
    -pthread
    --coverage
    -O0
)
target_link_libraries(${OBJDUMP_TEST}
    gcov
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${ASSEMBLER_TEST})
gtest_discover_tests(${OBJDUMP_TEST})
