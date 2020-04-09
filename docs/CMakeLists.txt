find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(documentation ALL
        COMMAND Doxygen::doxygen ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating ${PROJECT_NAME} ${PROJECT_VERSION} documentation"
        VERBATIM)

    message("Documentation build has configured")
else()
    message(WARNING "Doxygen not found. Documentaion hasn't generated.")
endif()
