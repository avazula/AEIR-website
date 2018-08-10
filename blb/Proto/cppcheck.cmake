# cppcheck rule
# -----------------------------------------------------------------------------
find_program(CPPCHECK_EXECUTABLE cppcheck)

# cppcheck rule
# -----------------------------------------------------------------------------
set(CPPCHECK_INCLUDE_FLAGS ${CPPCHECK_INCLUDE_FLAGS} -I ${CMAKE_CURRENT_SOURCE_DIR})

#    find_program(CPPCHECK_EXECUTABLE cppcheck)
add_custom_target(cppcheck-mod
        COMMAND ${CMAKE_COMMAND} -E remove -f ${PROJECT_BINARY_DIR}/cppcheck-mod.xml
        COMMAND ${CPPCHECK_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR} ${CPPCHECK_INCLUDE_FLAGS} --enable=all --force -v --xml 2> ${PROJECT_BINARY_DIR}/cppcheck_.xml
        COMMAND grep -v "/usr/include" ${PROJECT_BINARY_DIR}/cppcheck_.xml | grep -iv "Soap-Data" | grep -iv "class_x_y" | grep -iv "stub.h" | grep -iv "missingInclude" | grep -iv "UnitTests" | grep -iv "unusedFunction" > ${PROJECT_BINARY_DIR}/cppcheck-mod.xml
        COMMAND ${CMAKE_COMMAND} -E remove -f ${PROJECT_BINARY_DIR}/cppcheck_.xml
        COMMENT "Launching static analysis with cppcheck for mod"
        VERBATIM
        )
