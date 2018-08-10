/////////////////////////////////////////////////////////////////////////
/// @file XthreadTests.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///

#include "threadTests.h"

#include <vector>
#include <algorithm>

#include "Mutex.h"
#include "MutexError.h"
#include "CriticalSection.h"
#include "Semaphore.h"
#include "SemaphoreError.h"
#include "Thread.h"
#include "Utils.h"
#include "CSleep.h"


using namespace std;
//using namespace AtsComSolution;

//-------- !!! MUST BE THE LAST INCLUDED FILE !!! ------

//------------------------------------------------------


CPPUNIT_TEST_SUITE_REGISTRATION (XthreadTests);

void XthreadTests::setUp(void)
{
}

void XthreadTests::tearDown(void)
{
}

bool XthreadTests::containsOnly(const vector<int> & vect, int value)
{
	return find_if(vect.begin(), vect.end(), bind2nd(not_equal_to<int>(), value)) == vect.end();
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_LaunchThread_OK()
{
	class TestThread : public Thread
	{
	public:
		TestThread() : value(0) {}
		virtual void runThread()
		{
			value = 3;
		}
		int value;
	};

	TestThread thread;

	// Launch thread
	thread.start();

	// Wait
	thread.wait();

	CPPUNIT_ASSERT_EQUAL(thread.value,3);
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_CriticalSectionThread_OK()
{
	class TestThread : public Thread
	{
	public:
		TestThread()
		{
			vect.assign(100,0);
		}
		void threadA()
		{
			CriticalSection cs(mutex);
			for(vector<int>::iterator it = vect.begin() ; it != vect.end() ; ++it)
			{
				CSleep::sleep(1);
				*it = 1;
			}
		}
		void threadB()
		{
			CriticalSection cs(mutex);
			for(vector<int>::reverse_iterator it = vect.rbegin() ; it != vect.rend() ; ++it)
			{
				CSleep::sleep(1);
				*it = 2;
			}
		}
		virtual void runThread()
		{
			threadB();
		}
		Mutex mutex;
		vector<int> vect;
	};

	TestThread thread;

	// Launch thread
	thread.start();

	thread.threadA();

	// Wait
	thread.wait();

	CPPUNIT_ASSERT(containsOnly(thread.vect,1) || containsOnly(thread.vect,2));
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_Semaphore_OK()
{
	class TestThread : public Thread
	{
	public:
		TestThread() : m_sem(0) {}
		void threadA()
		{
			CSleep::sleep(10);
			text += 'a';
			m_sem.post();
		}
		void threadB()
		{
			m_sem.wait(); // Wait for threadA to finish
			text += 'b';
		}
		virtual void runThread()
		{
			threadB();
		}
		Semaphore m_sem;
		string text;
	};

	TestThread thread;

	// Launch thread
	thread.start();

	thread.threadA();

	// Wait
	thread.wait();

	CPPUNIT_ASSERT_EQUAL(string("ab"),thread.text);
}

/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_2_Semaphores_OK()
{
	class TestThread : public Thread
	{
	public:
		TestThread() : m_semA(0),m_semB(0) {}
		void threadA()
		{
			CSleep::sleep(10);
			text += 'a';
			m_semA.post();
			m_semB.wait(); // Wait for threadB to write 'b'
			text += 'c';
		}
		void threadB()
		{
			m_semA.wait(); // Wait for threadA to write 'a'
			text += 'b';
			CSleep::sleep(10);
			m_semB.post();
		}
		virtual void runThread()
		{
			threadB();
			threadB();
		}
		Semaphore m_semA;
		Semaphore m_semB;
		string text;
	};

	TestThread thread;

	// Launch thread
	thread.start();

	thread.threadA();
	thread.threadA();

	// Wait
	thread.wait();

	CPPUNIT_ASSERT_EQUAL(string("abcabc"),thread.text);
}




/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_Mutex_Error1()
{
	try
	{
		class TestMutex : public Mutex
		{
		public:
			TestMutex() : Mutex() {};

			void enter()
			{
#ifdef WIN32_THREADS
				if (!CloseHandle(m_sysMutex.handle))
					GetLastError();
#else
				pthread_mutex_destroy(&m_sysMutex);
#endif

				Mutex::enter();
			}
		};

		TestMutex mutex;
		mutex.enter();

		CPPUNIT_ASSERT_MESSAGE("No exception MutexError", false);
	}
	catch (MutexError &err)
	{
		CPPUNIT_ASSERT_MESSAGE("MutexError OK", true);
	}
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_Mutex_Error2()
{
	try
	{
		class TestMutex : public Mutex
		{
		public:
			TestMutex() : Mutex() {};

			void leave()
			{
#ifdef WIN32_THREADS
				if (!CloseHandle(m_sysMutex.handle))
					GetLastError();
#else
				pthread_mutex_destroy(&m_sysMutex);
#endif

				Mutex::leave();
			}
		};

		TestMutex mutex;
		mutex.leave();

		CPPUNIT_ASSERT_MESSAGE("No exception MutexError", false);
	}
	catch (MutexError &err)
	{
		CPPUNIT_ASSERT_MESSAGE("MutexError OK", true);
	}
}




/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void XthreadTests::runTest_Semaphore_Error1()
{
#ifndef WIN32_THREADS
	try
	{
		class TestSemaphore : public Semaphore
		{
		public:
			TestSemaphore(unsigned int tokens) : Semaphore(tokens) {}

			void post()
			{
				sem_destroy(&m_sem);

				Semaphore::post();
			}
		};

		TestSemaphore sem(1);
		sem.post();
		sem.wait();

		throw SemaphoreError("Can't wait on semaphore. ");

		CPPUNIT_ASSERT_MESSAGE("No exception SemaphoreError", false);
	}
	catch (SemaphoreError &err)
	{
		CPPUNIT_ASSERT_MESSAGE("SemaphoreError OK", true);
	}

#endif
}

