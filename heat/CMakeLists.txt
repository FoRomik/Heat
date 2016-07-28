add_custom_target(build ALL
    COMMAND python setup.py build_ext -i
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "-- Building"
    VERBATIM
    DEPENDS ReplicatePythonSourceTree
)
