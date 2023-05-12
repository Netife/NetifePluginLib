cmake_minimum_required(VERSION 3.25)
project(NetifePluginLib)

set(CMAKE_CXX_STANDARD 23)

find_package(Poco REQUIRED Foundation)
find_package(Poco REQUIRED JSON)
if (WIN32)
add_definitions(/utf-8)
endif()
add_library(NetifePluginLib SHARED hook.cpp NetifeBasicLib.h NetifeBasicLib.cpp TextHelper.cpp)

target_link_libraries(NetifePluginLib PRIVATE Poco::Foundation)
target_link_libraries(NetifePluginLib PRIVATE Poco::JSON)