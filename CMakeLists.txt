cmake_minimum_required(VERSION 3.12)
project(ReflectionSystem)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES main.cpp)

find_package(jsoncpp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

add_executable(ReflectionSystem ${SOURCES} "reflection_system.h" "for_each.h" "serializer.h"  "logger.h" "logger.cpp")
target_link_libraries(ReflectionSystem PRIVATE JsonCpp::JsonCpp yaml-cpp::yaml-cpp tinyxml2::tinyxml2)
