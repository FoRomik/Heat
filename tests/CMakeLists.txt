# Target:   rect_test
# Type:     Executable
#========================================================================================
file(GLOB SOURCES *.cxx)

add_executable(cxx_test ${SOURCES}
               ${CMAKE_SOURCE_DIR}/src/ComputeSeries.cxx
               ${CMAKE_SOURCE_DIR}/src/Uniform.cxx
               ${CMAKE_SOURCE_DIR}/src/Misc.cxx
               ${CMAKE_SOURCE_DIR}/src/Exceptions.cxx)

target_link_libraries(cxx_test gtest)

# Register tests
add_test(NAME testCxx COMMAND cxx_test) # test cxx code
add_test (NAME testPython COMMAND tox) # test python code
