/////////////////////////////////////////////////////////////////////////
/// \class MutexError
///
/// \date April 2014
/// \author IT&Labs - Orange Business Services
///

#ifndef MOD_MUTEXERROR_H
#define MOD_MUTEXERROR_H

#include <string>

#ifdef WIN32_THREADS
#include <windows.h>
#include <list>
#else
#include <pthread.h>
#include <semaphore.h>
#endif


////////////////////////////////////////////////////////////////////////
/// \brief This class defines an exception for Mutex.
///
class MutexError : public std::exception
{
public:
    /////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param message [in] : message of exception
    ///
    MutexError(const std::string &);

    /////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    virtual ~MutexError() throw();

};


#endif //MOD_MUTEXERROR_H
