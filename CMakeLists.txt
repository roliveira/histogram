cmake_minimum_required(VERSION 3.5)
PROJECT(histogram)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

# Set the project directory names
set(HISTOGRAM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Version
file(READ "${HISTOGRAM_INCLUDE_DIR}/histogram.hpp" ver)

string(REGEX MATCH "HISTOGRAM_VERSION_MAJOR ([0-9]*)" _ ${ver})
set(HISTOGRAM_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "HISTOGRAM_VERSION_MINOR ([0-9]*)" _ ${ver})
set(HISTOGRAM_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "HISTOGRAM_VERSION_PATCH ([0-9]*)" _ ${ver})
set(HISTOGRAM_VERSION_PATCH ${CMAKE_MATCH_1})

set(${PROJECT_NAME}_VERSION
    ${HISTOGRAM_VERSION_MAJOR}.${HISTOGRAM_VERSION_MINOR}.${HISTOGRAM_VERSION_PATCH}
)

message(STATUS "Building ${PROJECT_NAME} v${${PROJECT_NAME}_VERSION}")

option(BUILD_ALL      "Build everything."           OFF)
option(BUILD_DOCS     "Build documentation."        OFF)
option(BUILD_EXTERNAL "Build external dependecies." ON )
option(BUILD_TESTS    "Build tests."                OFF)


# Handle build all option
if(BUILD_ALL MATCHES ON)
    set(BUILD_DOCS     ON)
    set(BUILD_EXTERNAL ON)
    set(BUILD_TESTS    ON)
endif()

include_directories(${HISTOGRAM_INCLUDE_DIR})
add_subdirectory(include)

# Build the external requirements
if(BUILD_EXTERNAL)
add_subdirectory(external)
include_directories(
    ${CATCH_INCLUDES}
)    
else()
    find_package(Catch REQUIRED)
    add_subdirectory(external EXCLUDE_FROM_ALL)
endif()

# Build the project documentation
if(BUILD_DOCS)
    add_subdirectory(docs)
else()
    add_subdirectory(docs EXCLUDE_FROM_ALL)
endif()

# Build the tests
if(BUILD_TESTS)
    enable_testing(true)
    add_subdirectory(tests)
else()
    add_subdirectory(tests EXCLUDE_FROM_ALL)
endif()
