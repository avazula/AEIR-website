//
// Created by avazula on 14/06/18.
//

#include "Semaphore.h"
#include "SemaphoreError.h"
#include "Utils.h"
#include <sstream>
#include <cstring>
#include <cerrno>

/////////////////////////////////////////////////////////////////////////
/// \brief Destructor: destruction of Semaphore
///
Semaphore::~Semaphore() throw()
{
#ifndef WIN32_THREADS
	sem_destroy(&m_sem);
#else
	 CloseHandle(m_handle);
#endif
}

Semaphore::Semaphore(unsigned int tokens) throw(SemaphoreError)
{
#ifndef WIN32_THREADS
	int ret = sem_init(&m_sem, 0, tokens);
	if (ret != 0)
	{
		throw SemaphoreError("Semaphore error");
	}
#else
	m_handle = CreateSemaphore(
        NULL,           // default security attributes
        tokens,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore

	if (m_handle == NULL)
	{
		throw SemaphoreError("Can't initialize semaphore");
	}
#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief Block current thread until a token is available
///
void Semaphore::wait() throw(SemaphoreError)
{
#ifndef WIN32_THREADS
	int ret = sem_wait(&m_sem);
	if (ret != 0)
	{
		throw SemaphoreError(getErrorMessage(errno));
	}
#else
	DWORD dwWaitResult = WaitForSingleObject(
            m_handle,   // handle to semaphore
            INFINITE);           // zero-second time-out interval

    switch (dwWaitResult)
    {
        // The semaphore object was signaled.
        case WAIT_OBJECT_0:
            break;

        // The semaphore was nonsignaled, so a time-out occurred.
        case WAIT_TIMEOUT:
            throw SemaphoreError(FATAL_SYSTEM_SEMAPHORE_WAIT_FAILURE.errorMessage + " (timeout)");
            break;
		default:
			throw SemaphoreError(FATAL_SYSTEM_SEMAPHORE_WAIT_FAILURE.errorMessage);
            break;
    }

#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief Release a token
///
void Semaphore::post() throw(SemaphoreError)
{
#ifndef WIN32_THREADS
	int ret = sem_post(&m_sem);
	if (ret != 0)
	{
		throw SemaphoreError(getErrorMessage(errno));
	}
#else
	if (!ReleaseSemaphore(
            m_handle,  // handle to semaphore
            1,            // increase count by one
            NULL) )       // not interested in previous count
    {
        throw SemaphoreError(FATAL_SYSTEM_SEMAPHORE_POST_FAILURE.errorMessage);
    }

#endif
}