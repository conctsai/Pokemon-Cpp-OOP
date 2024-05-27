cmake_minimum_required(VERSION 3.29.2)

project(Pokemon-Cpp-OOP)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(fmt REQUIRED)
find_package(ftxui 5 REQUIRED)

set(LIBHV_LIBRARYS /usr/local/lib/libhv.so)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB TARGET_LIST ${PROJECT_SOURCE_DIR}/target/*.cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

foreach(TARGET_FILE ${TARGET_LIST})
    get_filename_component(TARGET_NAME ${TARGET_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${TARGET_FILE} ${SRC_LIST})
    target_link_libraries(${TARGET_NAME} PUBLIC ${OPENSSL_LIBRARIES})
    target_link_libraries(${TARGET_NAME} PUBLIC ${SQLite3_LIBRARIES})
    target_link_libraries(${TARGET_NAME} PUBLIC fmt::fmt)
    target_link_libraries(${TARGET_NAME} PUBLIC ftxui::screen ftxui::dom ftxui::component)
    target_link_libraries(${TARGET_NAME} PUBLIC ${LIBHV_LIBRARYS})
endforeach(TARGET_FILE ${TARGET_LIST})