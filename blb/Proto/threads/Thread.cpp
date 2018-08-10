/*!
 * \class Thread
 */

#include "Thread.h"

/////////////////////////////////////////////////////////////////////////
/// \brief This class defines a thread.
///

/////////////////////////////////////////////////////////////////////////
/// \brief To return the identifier of the current running thread
///
/// \return the identifier of the current running thread as unsigned long
///
const unsigned long Thread::getThreadId()
{
#ifdef WIN32_THREADS
	DWORD threadId = ::GetCurrentThreadId();
	return static_cast<unsigned long>(threadId);
#else
	pthread_t threadId = pthread_self();
	return static_cast<unsigned long>(threadId);
#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief Constructor: creation of thread
///
Thread::Thread()
#ifdef WIN32_THREADS
	: m_handle(0)
#else
#ifdef __LINUX__
	: m_thread(0)
#endif
#endif
{
}

/////////////////////////////////////////////////////////////////////////
/// \brief Destructor: exit of thread
///
Thread::~Thread()
{
#ifdef WIN32_THREADS
	if (m_handle != 0)
	{
		CloseHandle(m_handle);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief To start the thread
///
/// \return 0 If successfully else error code
///
int Thread::start()
{
	int ret = 0;

#ifdef WIN32_THREADS
	DWORD id = 0;
	m_handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread::thread_func, this, 0, &id);
	if (m_handle == 0)
		ret = GetLastError();
#else
	ret = pthread_create(&m_thread, 0, Thread::thread_func, (void*)this);
#endif

	return(ret);
}

/////////////////////////////////////////////////////////////////////////
/// \brief To stop the thread
///
void Thread::stop()
{
#ifdef WIN32_THREADS
	DWORD exitCode = 0;
	GetExitCodeThread(m_handle,&exitCode);
	ExitThread(exitCode);
#else
	void * dummy = 0;
	pthread_exit(dummy);
#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief To wait the end of thread
///
void Thread::wait()
{
#ifdef WIN32_THREADS
	WaitForSingleObject(m_handle, INFINITE);
#else
	pthread_yield();
	pthread_join(m_thread, 0);
#endif
}

/////////////////////////////////////////////////////////////////////////
/// \brief To cancel a thread
///
void Thread::cancel()
{
#ifdef WIN32_THREADS
	DWORD exitCode = 0;
	GetExitCodeThread(m_handle,&exitCode);
	TerminateThread(m_handle,exitCode);

	// Execute cleanup handlers
	while(!m_cleanUpHandlers.empty())
	{
		CleanUpHandler & handler = m_cleanUpHandlers.back();
		(handler.first)(handler.second);
		m_cleanUpHandlers.pop_back();
	}
#else
	pthread_cancel(m_thread);
#endif
}
/////////////////////////////////////////////////////////////////////////
/// \brief To detach a thread
///
void Thread::detach()
{
#ifdef WIN32_THREADS
#else
	// Detach the thread
	pthread_detach(pthread_self());
#endif
}

#ifdef WIN32_THREADS
void Thread::pushCleanUpHandler(void (*routine)(void *),
				void *arg)
{
	m_cleanUpHandlers.push_back(std::make_pair(routine,arg));
}

void Thread::popCleanUpHandler(bool execute)
{
	if (!m_cleanUpHandlers.empty())
	{
		if (execute)
		{
			CleanUpHandler & handler = m_cleanUpHandlers.back();
			(handler.first)(handler.second);
		}
		m_cleanUpHandlers.pop_back();
	}
}
#endif



///// PRIVATE ////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
/// \brief Wrapper to run method
///
void *Thread::thread_func(void *arg)
{
	Thread *th = reinterpret_cast<Thread *>(arg);
	th->runThread();
	return 0;
};
