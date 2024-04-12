cmake_minimum_required(VERSION 3.26)
project(CodeWithMe)

set(CMAKE_CXX_STANDARD 23)

#set(GTEST_ROOT "D:/googletest")
#add_library(gtest STATIC
#        D:/googletest/googletest/src/gtest-all.cc
#        D:/googletest/googletest/src/gtest-internal-inl.h
#        D:/googletest/googletest/include/gtest/gtest.h
#        D:/googletest/googletest/src/gtest-death-test.cc
#        D:/googletest/googletest/src/gtest-printers.cc
#        D:/googletest/googletest/src/gtest-test-part.cc
#        D:/googletest/googletest/src/gtest-typed-test.cc
#        D:/googletest/googletest/src/gtest_main.cc
#)

set(BOOST_ROOT "D:/boost")
include_directories(${BOOST_ROOT})
link_directories(${BOOST_ROOT}/stage/lib)
set(BOOST_LIBRARIES boost_system-mgw13-mt-d-x64-1_84 boost_serialization-mgw13-mt-d-x64-1_84)  # these values may differ from yours!
set(CMAKE_CXX_FLAGS "-lboost_system-mgw13-mt-d-x64-1_84 -lboost_serialization-mgw13-mt-d-x64-1_84 -lws2_32 -fpermissive")

set(OPENSSL_ROOT D:/OpenSSL)
link_directories(${OPENSSL_ROOT}/lib/VC/x64/MD)

# include_directories(${GTEST_ROOT}/googletest/include)
# include_directories(${GTEST_ROOT}/googletest)
include_directories(${OPENSSL_ROOT}/include)
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
add_executable(CodeWithMe_Client ${CLIENT_SOURCE_FILES} ${CLIENT_HEADER_FILES})
target_link_libraries(CodeWithMe_Server ssl crypto)
target_link_libraries(CodeWithMe_Client ssl crypto)
# target_link_libraries(CodeWithMe_Server gtest ssl crypto)
# target_link_libraries(CodeWithMe_Client gtest ssl crypto)
