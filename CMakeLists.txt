cmake_minimum_required(VERSION 2.8)
project(mcomm)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_definitions(-Wall -Wno-unused-parameter -std=c++11)

file(GLOB_RECURSE SOURCES src/*.cc)
file(GLOB_RECURSE VENDOR_SOURCES src/*.cc)
file(GLOB_RECURSE HEADERS src/*.h)

include_directories(src src/3rdparty/include)

# Dependencies
find_package(SFML 2 REQUIRED system window graphics)
find_package(Glog)
find_package(Box2D)
find_package(Lua)

add_executable(${PROJECT_NAME} ${SOURCES} ${VENDOR_SOURCES} ${HEADERS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/precompiled.h")
