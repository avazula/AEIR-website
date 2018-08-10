/////////////////////////////////////////////////////////////////////////
/// @file AbstractTests.h
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///


#if !defined(_ABSTRACT_TESTS_H)
#define _ABSTRACT_TESTS_H


#include <string>
#include <cppunit/TestFixture.h>
using std::string;


/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a set of test cases
///
class AbstractTests: public CppUnit::TestFixture
{


public:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	AbstractTests();

	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	///
	virtual ~AbstractTests() {}

	/////////////////////////////////////////////////////////////////////////
	/// @brief Common setup method for all tests
	///
	virtual void setUp(void);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Common end method for all tests
	///
	virtual void tearDown(void) {}



protected:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Return true if file exists else false
	///	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	/// @param strFilename [in]: filename
	///
	/// @return
	///		<UL>
	///				<LI>true			if the file exists</LI>
	///				<LI>false			either</LI>
	///		</UL>
	///
	virtual bool  isFileExist(const char * strFilename) const;
	bool  isFileExist(const string & strFilename) const { return isFileExist(strFilename.c_str()); }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Remove file if exist
	///
	/// @param strFilename [in]: filename
	///
	/// @return
	///		<UL>
	///				<LI>true			if the file successfully removed</LI>
	///				<LI>false			either</LI>
	///		</UL>
	///
	virtual bool  removeFile(const char * strFilename) const;
	virtual bool  removeFile(const string & strFilename) const { return removeFile(strFilename.c_str()); }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Check if file contains specified message
	///
	/// @param strFilename [in]: filename
	/// @param msg [in]: message to be search
	///
	/// @return
	///		<UL>
	///				<LI>true			if the file contains the input message/LI>
	///				<LI>false			either</LI>
	///		</UL>
	///
	virtual bool isFileContains(const string & strFilename, const string & msg) const;


	/////////////////////////////////////////////////////////////////////////
	/// @brief Compare file contents and return true if equal
	///
	/// @param strFilename1 [in]: filename
	/// @param strFilename2 [in]: filename
	///
	/// @return
	///		<UL>
	///				<LI>true			if the files are equal</LI>
	///				<LI>false			either</LI>
	///		</UL>
	///
	bool  isFilesAreEqual(const char * strFilename1, const char * strFilename2) const;
	bool  isFilesAreEqual(const string & strFilename1, const string & strFilename2) const { return isFilesAreEqual(strFilename1.c_str(), strFilename2.c_str()); }



	/////////////////////////////////////////////////////////////////////////
	/// @brief Replace special char with their logical text representation to be able show it on the console
	///
	/// @param s [in]: Input string
	///
	/// @return
	///		string to be display on the console
	///
	string convertStringForConsole(const string& s) const;


	/////////////////////////////////////////////////////////////////////////
	/// @brief Diff of string
	///
	/// @param ref [in]: reference
	/// @param val [in]: string to compare
	///
	/// @return
	///		0 if string are equals or first char index if difference is found
	///
	unsigned int diffString(const string& ref, const string& val) const;


	//! directory of special test data
	string m_FolderPath;
	//! outpout directory
	string m_OutputFolderPath;

private:

	/////////////////////////////////////////////////////////////////////////
	/// @brief Open output file o first calling and write diff.
	///
	/// @param f [in]: file descriptor for output
	/// @param outFileName [in]: file name
	/// @param line [in]: line number
	/// @param str1 [in]: line content of file1
	/// @param str2 [in]: line content of file2
	///
	/// @return
	///		<UL>
	///				<LI>buffer			if the file successfully read</LI>
	///				<LI>0			either</LI>
	///		</UL>
	///
	FILE * writeDiff(FILE *f, const char *outFileName, unsigned int line, const char *str1, const char *str2) const;


	/////////////////////////////////////////////////////////////////////////
	/// @brief Allocate memory and read file. If buffer is returned, the caller must be release the memory
	///
	/// @param f [in]: file descriptor
	/// @param fSize [in]: file size
	///
	/// @return
	///		<UL>
	///				<LI>buffer			if the file successfully read</LI>
	///				<LI>0			either</LI>
	///		</UL>
	///
	char *readFile(FILE *f, unsigned long & fSize) const;


	/////////////////////////////////////////////////////////////////////////
	/// @brief get the file size
	///
	/// @param f [in]: file descriptor
	///
	/// @return
	///		file size in bytes
	///
	unsigned long getFileSize(FILE *f) const;
};

#endif //_ABSTRACT_TESTS_H
