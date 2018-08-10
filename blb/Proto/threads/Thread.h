/*!
 * \class Thread
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#ifndef MOD_THREAD_H
#define MOD_THREAD_H

#ifdef WIN32_THREADS
#include <windows.h>
#include <list>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a thread.
///
class Thread
{
public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief To return the identifier of the current running thread
	///
	/// @return the identifier of the current running thread as unsigned long
	///
	static const unsigned long getThreadId();

	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor: creation of thread
	///
	Thread();

	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor: exit of thread
	///
	virtual ~Thread();

	/////////////////////////////////////////////////////////////////////////
	/// @brief To start the thread
	///
	/// @return 0 If successfully else error code
	///
	int start();

	/////////////////////////////////////////////////////////////////////////
	/// @brief To stop the thread
	///
	void stop();

	/////////////////////////////////////////////////////////////////////////
	/// @brief To wait the end of thread
	///
	void wait();

	/////////////////////////////////////////////////////////////////////////
	/// @brief To cancel a thread
	///
	void cancel();

	/////////////////////////////////////////////////////////////////////////
	/// @brief To detach a thread
	///
	void detach();


#ifdef WIN32_THREADS
	void pushCleanUpHandler(void (*routine)(void *),
                          void *arg);
	void popCleanUpHandler(bool execute);
#endif

private:

#ifdef WIN32_THREADS
	HANDLE m_handle;
	typedef void (*routine)(void *);
	typedef std::pair<routine, void *> CleanUpHandler;
	std::list<CleanUpHandler> m_cleanUpHandlers;
#else
	pthread_t m_thread;		///> To save the thread structure
#endif

	/////////////////////////////////////////////////////////////////////////
	/// @brief Method to implement specific thread code
	///
	virtual void runThread() = 0;


	/////////////////////////////////////////////////////////////////////////
	/// @brief Wrapper to run method
	///
	static void *thread_func(void *args);
};

#endif //MOD_THREAD_H
