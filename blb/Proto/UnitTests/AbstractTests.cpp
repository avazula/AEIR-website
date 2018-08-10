/////////////////////////////////////////////////////////////////////////
/// @file AbstractTests.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///


// Standard include
//-----------------
#include <sys/stat.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

// Provided interfaces
//--------------------
#include "AbstractTests.h"


//-------- !!! MUST BE THE LAST INCLUDED FILE !!! ------

//------------------------------------------------------





#ifndef _MSC_VER
#define sprintf_s sprintf
#endif

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor
///
AbstractTests::AbstractTests() : CppUnit::TestFixture()
{
}


/////////////////////////////////////////////////////////////////////////
/// @brief Common setup method for all tests
///
void AbstractTests::setUp(void)
{
}



///// PROTECTED //////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
/// @brief Return true if file exists else false
///
/// @param strFilename [in]: filename
///
/// @return
///		<UL>
///				<LI>true			if the file exists</LI>
///				<LI>false			either</LI>
///		</UL>
///
bool  AbstractTests::isFileExist(const char * strFilename) const
{
	struct stat stFileInfo;

	// Attempt to get the file attributes
	if (strFilename && stat(strFilename, &stFileInfo) == 0)
		// We were able to get the file attributes
		// so the file obviously exists.
		return true;
	else
		// We were not able to get the file attributes.
		// This may mean that we don't have permission to
		// access the folder which contains this file. If you
		// need to do that level of checking, lookup the
		// return values of stat which will give you
		// more details on why stat failed.
		return false;
}


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
bool  AbstractTests::removeFile(const char * strFilename) const
{
	if (isFileExist(strFilename))
	{
		if (!remove(strFilename))
		{
			//std::cout << "file " << strFilename << " is removed";
			return true;
		}
	}
	return false;
}



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
bool  AbstractTests::isFilesAreEqual(const char * strFilename1, const char * strFilename2) const
{
   // to be developed
	return (true);
}




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
bool  AbstractTests::isFileContains(const string &strFilename, const string &msg) const
{
   if (isFileExist(strFilename))
   {
      ifstream file(strFilename, ios::in);
      ostringstream wholeFile;

      // If the file is not 0
      if (file.is_open())
      {
         string line;

         while (getline (file, line))
         {
            wholeFile << line << "\n";
         }

         file.close();
      }

      if (wholeFile.str().find(msg) != string::npos)
      {

         // String is found in file
         return true;
      }
      // else Failed because not found

   }
   return false;
}



///// PRIVATE ////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
FILE * AbstractTests::writeDiff(FILE *f, const char *outFileName, unsigned int line, const char *str1, const char *str2) const
{
	//	// Error during read lines
	//	if (!f)
	//	{
	//		unsigned int len = strlen(outFileName) + 6;
	//		char * diffName = new char[len];
	//		strcpy(diffName, outFileName);
	//		strcat(diffName, ".diff");
	//		f = fopen(diffName, "w");
	//		delete[] diffName;
	//	}
	//	if (f)
	//	{
	//		char text[256];
	//		if (line)
	//			sprintf_s(text, "\nDiff at line %d:\n---------------------------Out=\n", line);
	//		else
	//			sprintf_s(text, "\nOut and Ref files are different size:\n---------------------------Out=\n");
	//		fwrite(text, 1, strlen(text), f);
	//		string str = str1;
	//		string visibleStr = ChaineCar::visibleString(str);
	//		fwrite(visibleStr.c_str(), 1, visibleStr.size(), f);
	//		//fwrite(str1, 1, strlen(str1), f);
	//		sprintf_s(text, "\n---------------------------Ref=\n");
	//		fwrite(text, 1, strlen(text), f);
	//		str = str2;
	//		visibleStr = ChaineCar::visibleString(str);
	//		fwrite(visibleStr.c_str(), 1, visibleStr.size(), f);
	//		//fwrite(str2, 1, strlen(str2), f);
	//	}
	return f;
}




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
char *AbstractTests::readFile(FILE *f, unsigned long & fSize) const
{
	char *buffer = (char*) malloc (sizeof(char)*fSize);
	if (buffer)
	{
		// Copy the file into the buffer:
		fSize = fread (buffer,1,fSize,f);
		if (!ferror(f))
		{
			return buffer;
		}
		free (buffer);
		return 0;
	}
	return 0;
}



/////////////////////////////////////////////////////////////////////////
/// @brief get the file size
///
/// @param f [in]: file descriptor
///
/// @return
///		file size in bytes
///
unsigned long AbstractTests::getFileSize(FILE *f) const
{
	fseek (f , 0 , SEEK_END);
	unsigned long fSize = ftell (f);
	rewind (f);

	return fSize;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Replace special char with their logical text representation to be able show it on the console
///
/// @param s [in]: Input string
///
/// @return
///		string to be display on the console
///
string AbstractTests::convertStringForConsole(const string& s) const
{
	string result;
	for (string::const_iterator i = s.begin(); i != s.end(); ++i)
	{
		switch (*i)
		{
		case '"' :
			result += string("\\\"");
			break;
		case '\\' :
			result += string("\\\\");
			break;
		case '\t' :
			result += string("\\t");
			break;
		case '\f' :
			result += string("\\f");
			break;
		case '\r' :
			result += string("\\r");
			break;
		case '\a' :
			result += string("\\a");
			break;
		case '\b' :
			result += string("\\b");
			break;
		case '\n' :
			result += string("\\n");
			break;
		case '_' :
			result += string("\\_");
			break;
		case ' ' :
			result += string("_");
			break;
		default :
			result += *i;
			break;
		}
	}
	return result;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Diff of string
///
/// @param ref [in]: reference
/// @param val [in]: string to compare
///
/// @return
///		0 if string are equals or first char index if difference is found
///
unsigned int AbstractTests::diffString(const string& ref, const string& val) const
{
	unsigned int i = 0;
	while (i < ref.size())
	{
		if (i >= val.size()) return i;
		if (ref[i] != val[i]) return i;

		i++;
	}
	return 0;
}
