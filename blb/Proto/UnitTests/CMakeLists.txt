include_directories(${CPPUNIT_INCLUDE_DIR} ${PROJECT_BINARY_DIR} )

# Specifiy all library source files
# -----------------------------------------------------------------------------
set( UTILITIES_UNIT_TESTS_SRC
	AbstractTests.cpp
	AbstractTests.h
    ManageOptionsTests.cpp
    ManageOptionsTests.h
    threadTests.cpp
    threadTests.h
    )


# Specifiy all dependencies
# -----------------------------------------------------------------------------
set(UTILITIES_UNIT_TESTS_DEPENDENCIES
        ManageOptions
        Threads
        vehicles
        ${CPPUNIT_LIBRARY}
        )


# Build command line exe
# -----------------------------------------------------------------------------
add_executable( unitTests mainTests.cpp ${UTILITIES_UNIT_TESTS_SRC} )
target_link_libraries(unitTests
    ${UTILITIES_UNIT_TESTS_DEPENDENCIES}
    )



# Management of logConfig files for tests
# -----------------------------------------------------------------------------
add_custom_target(logConfigFiles
	ALL ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/LogConfig_Tests_Fatal.xml ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/LogConfig_Tests_Error.xml ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/LogConfig_Tests_Info.xml ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/LogConfig_Tests_Debug.xml ${PROJECT_BINARY_DIR}
	COMMENT "Copying utilities log config files for unit tests"
)



# Create target
# -----------------------------------------------------------------------------
#get_target_property(UNIT_TESTS_EXECUTABLE unitTests-utilities LOCATION)
add_custom_target(tests-utilities
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/unitTests --report-file ./cppunit-report-mod.xml
	DEPENDS unitTests
	DEPENDS logConfigFiles
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Launching tests"
)

#add_dependencies(tests-all tests-utilities)


