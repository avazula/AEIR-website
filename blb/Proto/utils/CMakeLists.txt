set( UTILS_SRC
        Logger.h

        Logger.cpp
        Tools.h
        )

add_library( utils STATIC ${UTILS_SRC} )