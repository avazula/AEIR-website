/*!
 * \class Mutex
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#include "Mutex.h"
#include <sstream>
#include <cstring>
#include "Utils.h"

/////////////////////////////////////////////////////////////////////////
/// \brief This class defines a Mutex.
///

/////////////////////////////////////////////////////////////////////////
/// \brief Constructor: initialization of Mutex
///
Mutex::Mutex()  throw(MutexError)
{
    int ret = 0;

#ifdef WIN32_THREADS
    m_sysMutex.handle = CreateMutex(0, 0, 0);
    if(m_sysMutex.handle == 0)
       ret = GetLastError();
#else
    ret = pthread_mutex_init(&m_sysMutex, 0);
#endif

    if (ret != 0)
    {
        throw MutexError(getErrorMessage(ret));
    }
}

/////////////////////////////////////////////////////////////////////////
/// \brief Destructor: destruction of Mutex
///
Mutex::~Mutex() throw()
{

#ifdef WIN32_THREADS
    if (!CloseHandle(m_sysMutex.handle))
      GetLastError();
#else
    pthread_mutex_destroy(&m_sysMutex);
#endif

}

/////////////////////////////////////////////////////////////////////////
/// \brief To get the mutex
///
void Mutex::enter() throw(MutexError)
{
    int ret = 0;

#ifdef WIN32_THREADS
    if (WaitForSingleObject(m_sysMutex.handle, INFINITE) != WAIT_OBJECT_0)
		ret = GetLastError();
#else
    ret = pthread_mutex_lock(&m_sysMutex);
#endif


    if (ret != 0)
    {
        throw MutexError(getErrorMessage(ret));
    }
}

/////////////////////////////////////////////////////////////////////////
/// \brief To release the mutex
///
void Mutex::leave() throw(MutexError)
{
    int ret = 0;

#ifdef WIN32_THREADS
    if (!ReleaseMutex(m_sysMutex.handle))
		ret = GetLastError();
#else
    ret = pthread_mutex_unlock(&m_sysMutex);
#endif

    if (ret != 0)
    {
        throw MutexError(getErrorMessage(ret));
    }
}