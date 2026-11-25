
cmake_minimum_required(VERSION 3.16)

project(BankCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(BankCore src/main.cpp)

target_link_libraries(BankCore PRIVATE SQLite::SQLite3)
find_package(SQLite3 REQUIRED)

target_link_libraries(BankCore PRIVATE SQLite::SQLite3)