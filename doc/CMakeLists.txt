find_package(Sphinx)
if (SPHINX_FOUND)
    # Add the target to generate docs in the build directory
    add_custom_target(${PROJECT_NAME}_doc
        COMMAND rm -f doc/heat.rst
        COMMAND sphinx-apidoc -o doc/ heat
        COMMAND sphinx-build -b html doc doc/_build/
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Sphinx"
        VERBATIM
        DEPENDS build
    )
    add_custom_target(doc DEPENDS ${PROJECT_NAME}_doc) # make doc
endif()