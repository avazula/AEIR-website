/////////////////////////////////////////////////////////////////////////
/// @file XthreadTests.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///


#if !defined(_XTHREAD_TESTS_H_)
#define _XTHREAD_TESTS_H_

#include <vector>
using namespace std;

#include <cppunit/extensions/HelperMacros.h>

#include "AbstractTests.h"

/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a set of test cases
///
class XthreadTests: public AbstractTests
{
	CPPUNIT_TEST_SUITE ( XthreadTests );

	CPPUNIT_TEST ( runTest_LaunchThread_OK );
	CPPUNIT_TEST ( runTest_CriticalSectionThread_OK );
	CPPUNIT_TEST ( runTest_Semaphore_OK );
	CPPUNIT_TEST ( runTest_2_Semaphores_OK );

#ifndef __MINGW32__
	CPPUNIT_TEST ( runTest_Mutex_Error1 );
	CPPUNIT_TEST ( runTest_Mutex_Error2 );
	CPPUNIT_TEST ( runTest_Semaphore_Error1 );
#endif

	CPPUNIT_TEST_SUITE_END();

public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	XthreadTests() : AbstractTests() {}

	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	///
	virtual ~XthreadTests() {}

	/////////////////////////////////////////////////////////////////////////
	/// @brief Common setup method for all tests
	///
	virtual void setUp(void);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Common end method for all tests
	///
	virtual void tearDown(void);



private:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Run test
	///

	void runTest_LaunchThread_OK();
	void runTest_CriticalSectionThread_OK();
	void runTest_Semaphore_OK();
	void runTest_2_Semaphores_OK();

	void runTest_Mutex_Error1();
	void runTest_Mutex_Error2();
	void runTest_Semaphore_Error1();

	bool containsOnly(const vector<int> & vect, int value);

};

#endif //_XTHREAD_TESTS_H_
