cmake_minimum_required(VERSION 3.5)

project(logging LANGUAGES CXX)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DAPPNAME="${PROJECT_NAME}")
add_executable(logging main.cpp alogger.h )
#add_executable(logging_ut Logging_UT.cpp )
#target_link_libraries(logging_ut ${GTEST_LIBRARIES} Threads::Threads)
