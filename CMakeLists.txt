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

set(OPENSSL_ROOT D:/OpenSSL)
link_directories(${OPENSSL_ROOT}/lib/VC/x64/MD)

include_directories(${OPENSSL_ROOT}/include)
include_directories(${GTEST_ROOT}/googletest/include)
include_directories(${GTEST_ROOT}/googletest)
include_directories(dtl)
include_directories(Server/include)
include_directories(Client/include)

file(GLOB SERVER_HEADER_FILES
        "Server/include/***/**/*.hpp"
        "Server/include/**/*.hpp"
        "Server/include/*.hpp")
file(GLOB SERVER_SOURCE_FILES
        "Server/src/***/**/*.cpp"
        "Server/src/**/*.cpp"
        "Server/src/*.cpp")

file(GLOB CLIENT_HEADER_FILES
        "Client/include/***/**/*.hpp"
        "Client/include/**/*.hpp"
        "Client/include/*.hpp")
file(GLOB CLIENT_SOURCE_FILES
        "Client/src/***/**/*.cpp"
        "Client/src/**/*.cpp"
        "Client/src/*.cpp")

add_executable(CodeWithMe_Server ${SERVER_SOURCE_FILES} ${SERVER_HEADER_FILES})
add_executable(CodeWithMe_Client ${CLIENT_SOURCE_FILES} ${CLIENT_HEADER_FILES}
        Client/include/File/File.hpp
        Client/src/File/File.cpp
        Client/include/Request/Request.hpp
        Client/src/Request/Request.cpp)
target_link_libraries(CodeWithMe_Server gtest ssl crypto)
target_link_libraries(CodeWithMe_Client gtest ssl crypto)
