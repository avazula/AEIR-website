#find_package( CppUnit REQUIRED )
#

    find_path(CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h)
    find_library(CPPUNIT_LIBRARY_RELEASE cppunit)
    find_library(CPPUNIT_LIBRARY_DEBUG cppunitd)

    if(CPPUNIT_LIBRARY_DEBUG)
        set(CPPUNIT_LIBRARY optimized ${CPPUNIT_LIBRARY_RELEASE} debug ${CPPUNIT_LIBRARY_DEBUG})
    else()
        set(CPPUNIT_LIBRARY ${CPPUNIT_LIBRARY_RELEASE})
    endif()

    if(CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)
        set(CPPUNIT_FOUND True)
        message(STATUS "Unit tests are enabled with cppUnit: " ${CPPUNIT_LIBRARY})
    else()
        message(WARNING "Unit tests are not allowed (cppUnit not found)")
    endif()


