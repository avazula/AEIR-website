/////////////////////////////////////////////////////////////////////////
/// @file ManageOptionsTests.h
///
/// Created on: May 2014
/// Author: IT&Labs - Orange Business Services
///

#if !defined(_MANAGE_OPTIONS_TESTS_H)
#define _MANAGE_OPTIONS_TESTS_H

#include <cppunit/extensions/HelperMacros.h>

#include "AbstractTests.h"


class ManageOptions;



/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a set of test cases
///
class ManageOptionsTests: public AbstractTests
{
	CPPUNIT_TEST_SUITE ( ManageOptionsTests );

	CPPUNIT_TEST ( runTest_Help );
	CPPUNIT_TEST ( runTest_Version );
	CPPUNIT_TEST ( runTest_Normal );
	CPPUNIT_TEST ( runTest_Normal_NoArgument );
	CPPUNIT_TEST ( runTest_ShowHelp );

	CPPUNIT_TEST ( runTest_Error_UnknownOption );
	CPPUNIT_TEST ( runTest_Error_IncorrectValue );
	CPPUNIT_TEST ( runTest_Error_ArgumentRequired );
	CPPUNIT_TEST ( runTest_Error_NoArgumentAllowed );
	CPPUNIT_TEST ( runTest_Error_IncompatibleOptions );
	CPPUNIT_TEST ( runTest_Error_UnknownMandatoryOption );
	CPPUNIT_TEST ( runTest_Error_DoubledOption );
	CPPUNIT_TEST ( runTest_Error_MissingMandatoryOption );


	CPPUNIT_TEST_SUITE_END();

public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	ManageOptionsTests() : AbstractTests() {}

	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	///
	virtual ~ManageOptionsTests() {}

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
	/// @brief Run test methods
	///
	void runTest_Help();
	void runTest_Version();
	void runTest_Normal();
	void runTest_Normal_NoArgument();
	void runTest_ShowHelp();

	void runTest_Error_UnknownOption();
	void runTest_Error_IncorrectValue();
	void runTest_Error_ArgumentRequired();
	void runTest_Error_NoArgumentAllowed();
	void runTest_Error_IncompatibleOptions();
	void runTest_Error_UnknownMandatoryOption();
	void runTest_Error_DoubledOption();
	void runTest_Error_MissingMandatoryOption();


	/////////////////////////////////////////////////////////////////////////
	/// @brief Create ManageOptions object
	///
	/// @return object
	///
	ManageOptions *createManageOptions();
};

#endif //_MANAGE_OPTIONS_TESTS_H
