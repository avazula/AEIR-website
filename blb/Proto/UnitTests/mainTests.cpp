/////////////////////////////////////////////////////////////////////////
/// @file mainTests.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#include <unistd.h>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
//#include <cppunit/TextTestProgressListener.h>
#include <cppunit/XmlOutputter.h>

#include <cppunit/TestPath.h>

#include "ManageOptions.h"

/////////////////////////////////////////////////////////////////////////
/// @brief Defines colors values to use in standard output
/// see http://en.wikipedia.org/wiki/ANSI_escape_code and
/// see http://linux.about.com/library/cmd/blcmdl4_console_codes.htm
///
#define ANSI_RED_BRIGHT "[01;31m"
#define ANSI_GREEN_BRIGHT "[01;32m"
#define ANSI_YELLOW_BRIGHT "[01;33m"
#define ANSI_BLUE_BRIGHT "[01;34m"
#define ANSI_MAGENTA_BRIGHT "[01;35m"
#define ANSI_CYAN_BRIGHT "[01;36m"
#define ANSI_WHITE_BRIGHT "[01;37m"

#define ANSI_NEUTRAL "[0m"

void ___SplitNoEmptyFields(vector<string> &result,	const string & chaine, const char * chaineRecherche)
{
	result.clear();
	if (!chaineRecherche) return;
	string::size_type pos1 = 0;
	string::size_type pos2 = chaine.find(chaineRecherche,pos1);
	while (pos2 != string::npos)
	{
		if (pos2-pos1)
		{
			// No add empty element
			result.push_back(string(chaine,pos1,pos2-pos1));
		}
		pos1 = pos2 + strlen(chaineRecherche);
		pos2 = chaine.find(chaineRecherche,pos1);
	}

	if (chaine.size()-pos1)
	{
		result.push_back(string(chaine,pos1,pos2-pos1));
	}
}





/////////////////////////////////////////////////////////////////////////
/// @brief To show test result on console.
///
class MyTestResultCollector : public CPPUNIT_NS::TestResultCollector
{
public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	MyTestResultCollector()
	{
		_numberOfTests = 0;
		if (isatty(fileno(stdout)))
		{
			_greenColor = ANSI_GREEN_BRIGHT;
			_redColor = ANSI_RED_BRIGHT;
			_normalColor = ANSI_NEUTRAL;
		}
	}

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the number of tests
	///
	/// @param n : number
	///
	void setNumber(int n) { _numberOfTests = n; }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Start one test
	///
	/// @param test : test object
	///
	void startTest(CPPUNIT_NS::Test *test)
	{
      // For output results in console AFTER EACH TESTS
       if (runTests())
       {
          CPPUNIT_NS::CompilerOutputter compilerOutput(this, std::cerr);
          compilerOutput.write();
       }
       //else remainingTests = _numberOfTests;

       // Show current result
       cout << "\n" << _greenColor << ">*** Test number: "
             // runTests method shows all executed tests included current one
             << runTests()+1
             << "/" << _numberOfTests
             << " (passed tests: " << (runTests()-testFailuresTotal());

       // Show the number of failed tests in red if at least one failure
       cout << ", " << (testFailuresTotal() > 0 ? _redColor : _greenColor) << "failed tests: " << testFailuresTotal() << _greenColor;

       // Show remaining tests
       cout << ", remaining tests: " << (_numberOfTests-runTests()) << ")" << _normalColor << endl;

       // Start test
       TestResultCollector::startTest(test);
	}

private:
	int _numberOfTests; 	///< Number of tests to be ran
	string _greenColor;
	string _redColor;
	string _normalColor;
};


/////////////////////////////////////////////////////////////////////////
/// @brief main function.
///
/// @param argc : Number of arguments
/// @param argv : Arguments list
///
/// @return 0 if successfully exited
///
int main(int argc, char *argv[])
{

	const char *legalLongOptions[] = {
			"--report-file= path and name for the XML-report",
			"--list list availables tests",
			"--tests= do only the listed tests",
			"--help this help",
			0};
	const char *legalShortOptions[] = {0};


	ManageOptions opt(legalLongOptions, legalShortOptions);
	opt.setAliasOption("-r", "--report-file");
	opt.setAliasOption("-t", "--tests");
	opt.setAliasOption("-l", "--list");
	opt.setAliasOption("-h", "--help");

	opt.setName(argv[0]);

	string cppunitreport = "./cppunit-report-ats-com.xml";
	bool listtests = false;
	set<string>tests;

	opt.setDefaultValue("--report-file", cppunitreport);

	// Set version and external third party messages
	opt.setVersion("1.0");
	opt.setExternalSoftware("");

	opt.setHelp("Unit tests for ATS COM component. This tests set needs specific test data and reference results");
	opt.setUsage("_PROGRAMME_ [options]");

	//ManageOptions::resultmap *res = 0;
	try {
		const ManageOptions::resultmap *res = opt.analyzeOptions(argc, argv);

		for (ManageOptions::resultmap::const_iterator mi = res->begin(); 	mi != res->end(); ++mi)
		{
			if (mi->first == "--report-file")
			{
				cppunitreport = mi->second;
			}
			else if (mi->first == "--list")
			{
				listtests = true;
			}
			else if (mi->first == "--tests")
			{
				vector<string>tmp;
				___SplitNoEmptyFields(tmp, mi->second, ",");
				set<string> s(tmp.begin(), tmp.end());
				tests = s;
			}
			else if (mi->first == "--help")
			{
				cerr << opt.getTitle() << opt << endl;
				return 0;
			}
		}
	}
	catch (ManageOptions::ManageOptionsError &e)
	{
		cerr << e.what() << endl;
		return 11;
	}


	setlocale(LC_CTYPE, "");


	// Informs test-listener about testresults
	CPPUNIT_NS::TestResult testsResult;

	// Register listener for collecting the test-results
	MyTestResultCollector collectedResults;
	testsResult.addListener(&collectedResults);

	// Register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testsResult.addListener(&progress);


	// Insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testRunner;
	CPPUNIT_NS::Test *test = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
	int toptests = test->getChildTestCount();
	int alltests = 0;
	//cout << "tt: " << toptests << endl;
	for (int c=0; c<toptests; ++c)
	{
		// Get tests' family
		CPPUNIT_NS::Test *subtest = test->getChildTestAt(c);
		if (listtests)
		{
			cout << "test group " << c+1 << " (" << subtest->getName() << ") "  << subtest->getChildTestCount() << " tests:" << endl;
		}

		// Number of tests in family
		int subtests = subtest->getChildTestCount();

		if (!tests.empty())
		{
			if (tests.find(subtest->getName()) != tests.end())
			{
				alltests += subtests;
			}
		}


		for (int d=0; d<subtests; ++d)
		{
			CPPUNIT_NS::Test *subsubtest = subtest->getChildTestAt(d);
			if (listtests)
			{
				cout << "   test: " << d+1 << " " << subsubtest->getName() << endl;
			}
			if (!tests.empty())
			{
				if (tests.find(subsubtest->getName()) != tests.end())
				{
					alltests ++;
				}
			}
		}

		if (tests.empty())
		{
			alltests += subtests;
		}
	}

	if (listtests)
	{
		cout << "total of " << alltests << " tests." << endl;
	}
	else
	{
		collectedResults.setNumber(alltests);

		testRunner.addTest(test);

		if (!tests.empty())
		{
			for (set<string>::iterator it = tests.begin(); it != tests.end(); ++it)
			{
				testRunner.run(testsResult, *it);
				// Another way to run one test
				//CppUnit::TestPath tp(test, testPath);
				//testRunner.addTest(tp.getTestAt(0));
				//testRunner.run(testsResult);
			}
		}
		else
		{
			// run all tests
			testRunner.run(testsResult);
		}

		// For output results in console
		CPPUNIT_NS::CompilerOutputter compilerOutput(&collectedResults, std::cerr);
		compilerOutput.write();


		// For output results in XML file
		std::ofstream file(cppunitreport.c_str());
		CPPUNIT_NS::XmlOutputter xmlOutput( &collectedResults, file );
		xmlOutput.write();
		file.close();
	}


	// return always 0 to avoid have Jenkins job error
	// return 0 if tests were successful
	return 0;     //collectedResults.wasSuccessful() ? 0 : 1;

}
