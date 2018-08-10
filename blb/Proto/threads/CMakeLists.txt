# ---------------------------------------------------
# ----------------- THREADS -------------------------
# ---------------------------------------------------

set( THREADS_SRC
        CSleep.cpp
        CriticalSection.cpp
        Mutex.cpp
        MutexError.cpp
        Semaphore.cpp
        SemaphoreError.cpp
        Thread.cpp
        Utils.cpp
        )

set( THREADS_H
        CSleep.h
        CriticalSection.h
        Mutex.h
        MutexError.h
        Semaphore.h
        SemaphoreError.h
        Thread.h
        Utils.h
        )

add_library(Threads STATIC ${THREADS_SRC} ${THREADS_H} )
target_link_libraries(Threads  ${PTHREAD_LIBRARY})