cmake_minimum_required(VERSION 3.25)
project(NetifePluginLib)

set(CMAKE_CXX_STANDARD 23)
find_package(Poco REQUIRED Foundation)
add_library(NetifePluginLib SHARED hook.cpp NetifeBasicLib.h NetifeBasicLib.cpp)
target_link_libraries(NetifePluginLib PRIVATE Poco::Foundation)