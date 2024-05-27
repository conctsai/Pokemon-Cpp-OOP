cmake_minimum_required(VERSION 3.29.2)

project(Pokemon-Cpp-OOP)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(fmt REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

add_executable(app ${SRC})

target_link_libraries(app PUBLIC ${OPENSSL_LIBRARIES})
target_link_libraries(app PUBLIC ${SQLite3_LIBRARIES})
target_link_libraries(app PUBLIC fmt::fmt)