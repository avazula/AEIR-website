/*!
 * \class SemaphoreError
 *
 */

#ifndef MOD_SEMAPHOREERROR_H
#define MOD_SEMAPHOREERROR_H

#ifdef WIN32_THREADS
#include <windows.h>
#include <list>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

#include <iostream>

////////////////////////////////////////////////////////////////////////
/// @brief This class defines an exception for Semaphore.
///
class SemaphoreError : public std::exception
{
public:
    /////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///
    /// @param message [in] : message of exception
    ///
    SemaphoreError(const std::string & message);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Destructor
    ///
    virtual ~SemaphoreError() throw();

};

#endif //MOD_SEMAPHOREERROR_H
