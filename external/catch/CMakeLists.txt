cmake_minimum_required(VERSION 2.8.8)
project(catch_builder CXX)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    UPDATE_DISCONNECTED 1
   )

# Expose required variable (CATCH_INCLUDE_PATH) to parent scope
ExternalProject_Get_Property(catch source_dir)
set(CATCH_MODULE_PATH "${source_dir}" PARENT_SCOPE)
set(CATCH_INCLUDES ${source_dir}/single_include PARENT_SCOPE)
