cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

project(mod)

set(CMAKE_AUTOMOC ON)

# Setup ccpcheck
# -----------------------------------------------------------------------------
include(cppcheck.cmake)

# Setup openCV
# -----------------------------------------------------------------------------
include(opencv.cmake)

#Setup pthreads
# -----------------------------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/threads/pthreads.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/UnitTests/cppunit.cmake)

# Setup Qt
# -----------------------------------------------------------------------------
find_package(Qt4)

include_directories( ${QT_INCLUDES}
        /usr/include/qt4
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ManageOptions
        transport
        threads
        utils
#        UI
        )

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )


#set( UI_FORMS_${SIM_UI}
#        UI/Qt/entrance.ui
#        UI/Qt/mainwindow.ui
#        )
#
#QT4_WRAP_UI( UI_FORMS_HEADERS_${SIM_UI} ${UI_FORMS_${SIM_UI}} )

#add_executable(mod)

add_subdirectory(transport)
add_subdirectory(threads)
add_subdirectory(ManageOptions)
add_subdirectory(UnitTests)
add_subdirectory(utils)