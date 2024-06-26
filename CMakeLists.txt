cmake_minimum_required(VERSION 3.12)
project(ReflectionSystem)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES main.cpp reflection_system.h for_each.h serializer.h logger.h logger.cpp)

enable_testing()

find_package(jsoncpp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(ReflectionSystem ${SOURCES})
target_link_libraries(ReflectionSystem PRIVATE
    JsonCpp::JsonCpp
    yaml-cpp::yaml-cpp
    tinyxml2::tinyxml2)

set(TEST_SOURCES reflection_system_test.cpp)
add_executable(ReflectionSystemTest ${TEST_SOURCES})
target_link_libraries(ReflectionSystemTest PRIVATE
    JsonCpp::JsonCpp
    yaml-cpp::yaml-cpp
    tinyxml2::tinyxml2
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main)

add_test(NAME ReflectionSystemTest COMMAND ReflectionSystemTest)
