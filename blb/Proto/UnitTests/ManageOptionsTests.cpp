/////////////////////////////////////////////////////////////////////////
/// @file ManageOptionsTests.cc
///
/// Created on: May 2014
/// Author: IT&Labs - Orange Business Services
///


// Standard include
//-----------------
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
using namespace std;


// Provided interfaces
//--------------------
#include "ManageOptionsTests.h"


// Requested interfaces
//---------------------
#include "ManageOptions.h"

/// Subset of Library tests: library type
CPPUNIT_TEST_SUITE_REGISTRATION (ManageOptionsTests);



/////////////////////////////////////////////////////////////////////////
/// @brief Setup method
///
void ManageOptionsTests::setUp(void)
{
	AbstractTests::setUp();
}


/////////////////////////////////////////////////////////////////////////
/// @brief Create GetOption object
///
/// @return object
///
ManageOptions *ManageOptionsTests::createManageOptions()
{

	const char *legalLongOptions[] = { "--profil= path for your configuration",
			"--verbose to show debug message",
			"--silent no debug message [default]",
			"--tests= do only the listed tests",
			"--version to show version",
			0};
	const char *legalShortOptions[] = {"-h this help", 0};


	ManageOptions *opt = new ManageOptions(legalLongOptions, legalShortOptions);
	opt->setAliasOption("-p", "--profil");
	opt->setAliasOption("-v", "--verbose");
	opt->setAliasOption("-t", "--tests");
	opt->setAliasOption("-s", "--silent");
	opt->setAliasOption("--help", "-h");

	opt->setIncompatibles("--verbose", "--silent");

	opt->setLimitValues("--tests", "1,2,3");

	opt->setName("test");

	string outdir = ".";
	opt->setDefaultValue("--outdir", outdir);

    // Set version and external third party messages
	opt->setVersion("1.0");
	opt->setExternalSoftware("");

	opt->setHelp("unit tests of ManageOptions class in orange-labs-utilities library");
	opt->setUsage("_PROGRAMME_ [options]");


	return opt;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Setup method
///
void ManageOptionsTests::tearDown(void)
{

}



/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Help(void)
{
	int argc = 2;
	const char *argv[] = {"test", "-h"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			if (mi->first == "-h")
			{
				CPPUNIT_ASSERT_MESSAGE("Help found", true);
			}
			else
			{
				CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
			}
		}
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}





/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Version(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--version"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			if (mi->first == "--version")
			{
				string vers = go->getVersion();
				CPPUNIT_ASSERT_MESSAGE("Version found", true);
				CPPUNIT_ASSERT_MESSAGE("Version content", (vers.find("Solution") != string::npos));
			}
			else
			{
				CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
			}
		}
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}




/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Normal(void)
{
	int argc = 4;
	const char *argv[] = {"test", "--tests=1", "-v", "--profil=path"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			if (mi->first == "--tests")
			{
				CPPUNIT_ASSERT_MESSAGE("Tests found", true);
				CPPUNIT_ASSERT_MESSAGE("Tests value", mi->second == "1");
			}
			else if (mi->first == "--verbose")
			{
				CPPUNIT_ASSERT_MESSAGE("Verbose found", true);
			}
			else if (mi->first == "--profil")
			{
				CPPUNIT_ASSERT_MESSAGE("Profil found", true);
				CPPUNIT_ASSERT_MESSAGE("Profil value", mi->second == "path");
			}
			else
			{
				CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
			}
		}
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Normal_NoArgument(void)
{
	int argc = 2;
	const char *argv[] = {"test", "path"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
				CPPUNIT_ASSERT_MESSAGE("Test no argument", true);
		}
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}



/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_ShowHelp(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--help"};


	ManageOptions *go = createManageOptions();
	CPPUNIT_ASSERT_MESSAGE("Wrong title", (go->getTitle().find("Solution") != string::npos ? true : false));

	try
	{
		go->analyzeOptions(argc, (char **)argv);

		go->setHelpFilter("");
		cerr << *go << endl;

		go->setHelpFilter("tests");
		cerr << *go << endl;

		go->setHelpFilter("--verbose");
		cerr << *go << endl;

		go->setHelpFilter("s");
		cerr << *go << endl;

	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}




/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_UnknownOption(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--vers"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::UnknownOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("UnknownOption exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}



/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_IncorrectValue(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--tests=4"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::IncorrectValue &e)
	{
		CPPUNIT_ASSERT_MESSAGE("IncorrectValue exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}



/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_ArgumentRequired(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--tests"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::ArgumentRequired &e)
	{
		CPPUNIT_ASSERT_MESSAGE("ArgumentRequired exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_NoArgumentAllowed(void)
{
	int argc = 2;
	const char *argv[] = {"test", "--silent=2"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::NoArgumentAllowed &e)
	{
		CPPUNIT_ASSERT_MESSAGE("NoArgumentAllowed exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_IncompatibleOptions(void)
{
	int argc = 3;
	const char *argv[] = {"test", "-v", "-s"};


	ManageOptions *go = createManageOptions();

	try
	{
		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::IncompatibleOptions &e)
	{
		CPPUNIT_ASSERT_MESSAGE("IncompatibleOptions exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}





/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_UnknownMandatoryOption(void)
{
	ManageOptions *go = createManageOptions();

	try
	{
		go->specifyOptionAsMandatory("--vers");
		CPPUNIT_ASSERT_MESSAGE("Wrong UnknownMandatoryOption", false);
	}
	catch (ManageOptions::UnknownMandatoryOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("UnknownMandatoryOption exception found", true);
	}

	delete go;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_DoubledOption(void)
{
	ManageOptions *go = createManageOptions();

	try
	{
		go->setAliasOption("-v", "--vers");
		CPPUNIT_ASSERT_MESSAGE("Wrong UnknownOption", false);
	}
	catch (ManageOptions::UnknownOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("UnknownOption exception found", true);
	}

	try
	{
		go->setAliasOption("--help", "--verbose");
		CPPUNIT_ASSERT_MESSAGE("Wrong DoubledOption 1", false);
	}
	catch (ManageOptions::DuplicatedOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("DoubledOption exception found", true);
	}


	try
	{
		go->setAliasOption("-v", "--version");
		CPPUNIT_ASSERT_MESSAGE("Wrong DoubledOption 2", false);
	}
	catch (ManageOptions::DuplicatedOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("DoubledOption exception found", true);
	}

	delete go;
}



/////////////////////////////////////////////////////////////////////////
/// @brief Run test
///
void ManageOptionsTests::runTest_Error_MissingMandatoryOption(void)
{
	int argc = 2;
	const char *argv[2] = {"test", "--tests=1" };


	ManageOptions *go = createManageOptions();

	try
	{
		go->specifyOptionAsMandatory("--version");

		const ManageOptions::resultmap *res = go->analyzeOptions(argc, (char **)argv);


		for (ManageOptions::resultmap::const_iterator mi = res->begin(); mi != res->end(); ++mi)
		{
			CPPUNIT_ASSERT_MESSAGE("Wrong option found", false);
		}
	}
	catch (ManageOptions::MissingMandatoryOption &e)
	{
		CPPUNIT_ASSERT_MESSAGE("MissingMandatoryOption exception found", true);
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		CPPUNIT_ASSERT_MESSAGE(e.what(), false);
	}

	delete go;
}


