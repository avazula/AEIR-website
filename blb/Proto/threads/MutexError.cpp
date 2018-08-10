/*!
 *\class MutexError
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#include <iostream>
#include "MutexError.h"

/////////////////////////////////////////////////////////////////////////
/// \brief This class defines an exception for Mutex.
///

/////////////////////////////////////////////////////////////////////////
/// \brief Constructor
///
/// \param message [in] : message of exception
///
MutexError::MutexError(const std::string & message)
{
    std::cerr << message << std::endl;
}

/////////////////////////////////////////////////////////////////////////
/// \brief Destructor
///
MutexError::~MutexError() throw()
{
}