set( SOURCES
        Bus.cpp
        Camera.cpp
        Coach.cpp
        Train.cpp
        Tramway.cpp
        Trolleybus.cpp
        Tube.cpp
        Vehicle.cpp
        ../UI/MainWindow.cpp
        ../UI/Entrance.cpp
        )

set( HEADERS
        Bus.h
        Camera.h
        Coach.h
        Factory.h
        Train.h
        Tramway.h
        Trolleybus.h
        Tube.h
        Vehicle.h
        ../UI/MainWindow.h
        ../UI/Entrance.h
        )


add_library(vehicles STATIC ${SOURCES} ${HEADERS} )

add_executable( transport main.cpp ${SOURCES} ${HEADERS} )
target_link_libraries( transport ${OpenCV_LIBS} ${QT_LIBRARIES} vehicles Threads utils )
