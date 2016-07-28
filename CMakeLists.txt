cmake_minimum_required (VERSION 3.2)

set(CMAKE_BUILD_TYPE Release)
# Debugging Options
set (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 otherwise.

project (heat)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )
set(CMAKE_CONFIG_PATH ${PROJECT_SOURCE_DIR}/cmake.config)

include(DownloadProject)
message("-- Downloading GoogleTest")
# Build Google test and google mock no matter what
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1
                 QUIET
)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
include_directories("include"
                    "${gtest_SOURCE_DIR}/include"
                    "${gmock_SOURCE_DIR}/include")

# With CMake, a clean separation can be made between the source tree and the
# build tree.  When all source is compiled, as with pure C/C++, the source is
# no-longer needed in the build tree.  However, with pure *.py source, the
# source is processed directly.  To handle this, we reproduce the availability
# of the source files in the build tree.
add_custom_target( ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReplicatePythonSourceTree.cmake
  ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_subdirectory(${PROJECT_NAME})
add_subdirectory(doc)

include(CTest)
add_subdirectory(tests)