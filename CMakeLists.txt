cmake_minimum_required(VERSION 3.26)
project(CodeWithMe)

set(CMAKE_CXX_STANDARD 23)

set(GTEST_ROOT "D:/googletest")
add_library(gtest STATIC
        D:/googletest/googletest/src/gtest-all.cc
        D:/googletest/googletest/src/gtest-internal-inl.h
        D:/googletest/googletest/include/gtest/gtest.h
        D:/googletest/googletest/src/gtest-death-test.cc
        D:/googletest/googletest/src/gtest-printers.cc
        D:/googletest/googletest/src/gtest-test-part.cc
        D:/googletest/googletest/src/gtest-typed-test.cc
        D:/googletest/googletest/src/gtest_main.cc
)
include_directories(${GTEST_ROOT}/googletest/include)
include_directories(${GTEST_ROOT}/googletest)

file(GLOB HEADER_FILES  "include/***/**/*.hpp"
                        "include/**/*.hpp"
                        "include/*.hpp")
file(GLOB SOURCE_FILES  "src/***/**/*.cpp"
                        "src/**/*.cpp"
                        "src/*.cpp")

add_executable(CodeWithMe ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(CodeWithMe gtest)
