cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(INCLUDE_FILES
	utils/histogram.hpp
)

add_library(${PROJECT_NAME} INTERFACE)


if(BUILD_TESTS)
    enable_testing()
	add_dependencies(${PROJECT_NAME} catch)
endif()

target_link_libraries(${PROJECT_NAME} INTERFACE)
