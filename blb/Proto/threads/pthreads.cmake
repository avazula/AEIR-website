find_package( Threads )
if( CMAKE_USE_PTHREADS_INIT )
    find_library( PTHREAD_LIBRARY pthread )
    message( STATUS "Using pthread in " ${PTHREAD_LIBRARY} )

else()
    message( ERROR "No pthread found" )

endif()