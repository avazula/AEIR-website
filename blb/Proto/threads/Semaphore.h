/*!
 * \class Semaphore
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#ifndef MOD_SEMAPHORE_H
#define MOD_SEMAPHORE_H

#ifdef WIN32_THREADS
#include <windows.h>
#include <list>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

class SemaphoreError;

/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a Semaphore.
///
class Semaphore
{
public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor: initialization of Semaphore
	///
	/// @param tokens initial number of tokens
	///
	Semaphore(unsigned int tokens) throw(SemaphoreError);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor: destruction of Semaphore
	///
	~Semaphore() throw();

	/////////////////////////////////////////////////////////////////////////
	/// @brief Block current thread until a token is available
	///
	void wait() throw(SemaphoreError);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Release a token
	///
	void post() throw(SemaphoreError);

protected:
#ifndef WIN32_THREADS
	sem_t m_sem;
#else
	HANDLE m_handle;
#endif
};
#endif //MOD_SEMAPHORE_H
