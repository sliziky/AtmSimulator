cmake_minimum_required(VERSION 3.1)
project(atmSimulator)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -lboost_system -lboost_filesystem -Wextra  -l sqlite3 -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

set (BOOST_ROOT /usr/local/lib/boost_1_61_0)
set (BOOST_LIBRARYDIR /usr/local/lib/boost)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(header)

set(SOURCES main.cpp database.cpp)
add_executable(atmSimulator main.cpp database.h sqlite3.h handler.h handler.cpp ${SOURCES})

