/*!
 * \class Mutex
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#ifndef MOD_MUTEX_H
#define MOD_MUTEX_H

#include "MutexError.h"

/////////////////////////////////////////////////////////////////////////
/// \brief This class defines a Mutex.
///
class Mutex
{
public:
    /////////////////////////////////////////////////////////////////////////
    /// \brief Constructor: initialization of Mutex
    ///
    Mutex() throw(MutexError);

    /////////////////////////////////////////////////////////////////////////
    /// \brief Destructor: destruction of Mutex
    ///
    ~Mutex() throw();

    /////////////////////////////////////////////////////////////////////////
    /// \brief To get the mutex
    ///
    void enter() throw(MutexError);

    /////////////////////////////////////////////////////////////////////////
    /// \brief To release the mutex
    ///
    void leave() throw(MutexError);

protected:
#ifdef WIN32_THREADS
    typedef struct {
		int        flag;
		HANDLE     handle;
	} pthread_mutex_t;
#endif

    pthread_mutex_t m_sysMutex;		///< To save Mutex
};


#endif //MOD_MUTEX_H
