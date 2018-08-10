/////////////////////////////////////////////////////////////////////////
/// @file ManageOptions.h
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///

#ifndef __MANAGE_OPTIONS_H__
#define __MANAGE_OPTIONS_H__

// System dependencies
//--------------------
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
using std::map;
using std::set;
using std::vector;
using std::string;
using std::ostream;



// Requested APIs
//---------------
#include <exception>



/////////////////////////////////////////////////////////////////////////
/// @brief This class is used to manage options passed as arguments on
/// command line
///
class ManageOptions
{
public:

	/////////////////////////////////////////////////////////////////////////
	/// @brief To parse options
	///
	typedef map<string, string> resultmap;

	/////////////////////////////////////////////////////////////////////////
	/// @brief To parse options
	///
	struct argDoc
	{
		bool hasArg;
		string doc;
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief To check if option is valid with or w/o value for option
	///
	typedef map<string, struct argDoc> legalmap;

	/////////////////////////////////////////////////////////////////////////
	/// @brief To check if option is valid with or w/o value for option
	///
	typedef map<string, set<string> > valmap; // option: possible values

	/////////////////////////////////////////////////////////////////////////
	/// @brief To check if option is valid with or w/o value for option
	///
	typedef map<string, bool> valmapcomb;



	/////////////////////////////////////////////////////////////////////////
	/// @brief Basic exception class
	///
	class ManageOptionsError: public exception {
	public:
		explicit ManageOptionsError(string message);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class UnknownOption: public ManageOptionsError {
	public:
		explicit UnknownOption(string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class DuplicatedOption: public ManageOptionsError {
	public:
		explicit DuplicatedOption(string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class UnknownMandatoryOption: public ManageOptionsError {
	public:
		explicit UnknownMandatoryOption(string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class MissingMandatoryOption: public ManageOptionsError {
	public:
		explicit MissingMandatoryOption(string p);
		explicit MissingMandatoryOption(set<string> p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class ArgumentRequired: public ManageOptionsError {
	public:
		explicit ArgumentRequired(string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class IncorrectValue: public ManageOptionsError {
	public:
	    IncorrectValue(string fullname, string o, string v, valmap&values);
	};


	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class NoArgumentAllowed: public ManageOptionsError {
	public:
	    NoArgumentAllowed(string o, string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class ArgumentWithoutOption: public ManageOptionsError {
	public:
		explicit ArgumentWithoutOption(string p);
	};

	/////////////////////////////////////////////////////////////////////////
	/// @brief Exception class
	///
	class IncompatibleOptions: public ManageOptionsError {
	public:
		IncompatibleOptions(string o1, string o2);
	};


	/////////////////////////////////////////////////////////////////////////
	/// @brief Constructor
	///
	/// @param legalLongOptions [in] : list of long enabled option
	/// @param legalShortOptions [in] : list of short enabled option
	///
	ManageOptions(const char *legalLongOptions[], const char *legalShortOptions[]);


	/////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	///
	~ManageOptions();


	/////////////////////////////////////////////////////////////////////////
	/// @brief Operator<<  to display ManageOptions to out stream
	///
	/// @param out [in] : Stream
	/// @param manageOptions [in] : Object
	///
	/// @return new Stream
	///
	friend ostream& operator<<(ostream & out, const ManageOptions &manageOptions);


	/////////////////////////////////////////////////////////////////////////
	/// @brief Check the option found
	///
	/// @param ac [in] : Number of arguments
	/// @param av [in] : Arguments array
	///
	/// @return List of Options
	///
	const resultmap *analyzeOptions(int ac, char *av[]) throw(UnknownOption, IncorrectValue, NoArgumentAllowed, ArgumentWithoutOption, ArgumentRequired, IncompatibleOptions, MissingMandatoryOption);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the limit value for one option
	///
	/// @param option [in] : Option
	/// @param values [in] : Arguments array
	/// @param combination : If true, allow any values
	///
	void setLimitValues(const char *option, const char *values, bool combination=false);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set alias for one option
	///
	/// @param d [in] : Source Option
	/// @param o [in] : Duplicate option
	///
	void setAliasOption(const string &d, const string &o) throw(UnknownOption, DuplicatedOption);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Get the program name and copyright information
	///
	/// @return information
	///
	string getTitle() const;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Get the version information
	///
	/// @return information
	///
	string getVersion() const;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the default value for one option
	///
	/// @param option [in] : Option
	/// @param value [in] : Value
	///
	void setDefaultValue(const string &option, const string &value);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the option as mandatory
	///
	/// @param option [in] : Option
	///
	void specifyOptionAsMandatory(const string &option) throw(UnknownMandatoryOption);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the filter when the help message is shown
	///
	/// @param option [in] : Option
	///
	void setHelpFilter(const string &option) ;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set two option incompatible
	///
	/// @param o1 [in] : Option 1
	/// @param o2 [in] : Option 2
	///
	void setIncompatibles(const string &o1, const string &o2);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Get arguments list
	///
	/// @return list
	///
	vector<string> getArgs() const { return m_RestArgs; };

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the usage message
	///
	/// @param msg [in] : usage message
	///
	void setUsage(const string &msg) { m_Usage = msg; };

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the program name
	///
	/// @param name [in] : program name
	///
	void setName(const string &name) { m_ProgramName = name; }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the long program name
	///
	/// @param name [in] : program name
	///
	void setLongName(const string &name) { m_LongProgramName = name; }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the help message
	///
	/// @param msg [in] : help message
	///
	void setHelp(const string &msg) { m_Help = msg; };

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the option uncommented
	///
	/// @param option [in] : Option long name
	///
	void setUncommented(const string &option) { m_Uncommented.insert(option); }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the version of program
	///
	/// @param vers [in] : version message
	///
	void setVersion(const string &vers) { m_Version = vers; }

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the External Software list of the program
	///
	/// @param extSW [in] : External Software list
	///
	void setExternalSoftware(const string &extSW) { m_ExternalSoftware = extSW; }



private:
	/////////////////////////////////////////////////////////////////////////
	/// @brief Get the option name
	///
	/// @param baseOption [in] : Option
	///
	/// @return List with duplicates option
	///
	string getOptionName(const string &baseOption) const;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Set the limit value for one option
	///
	/// @param opt [in] : Option
	/// @param val [in] : value
	///
	/// @return true if value is correct
	///
	bool valueOK(const string &opt, const string &val);

	/////////////////////////////////////////////////////////////////////////
	/// @brief Split a string ans put result in vector. Empty part are removed
	///
	/// @param result : to save result
	/// @param input : string to split
	/// @param delimit : delimiter
	///
	void SplitNoEmptyFields(vector<string> &result, const string &input, const char *delimit) const;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Split a string ans put result in vector. Empty part are removed
	///
	/// @param result : to save result
	/// @param input : string to split
	/// @param delimit : delimiter
	/// @param numberOfSplits : number of wanted splits. If 0, all parts are split
	///
	void Split(vector<string>&result, const string &input, const char *delimit, unsigned int numberOfSplits=0) const;

	/////////////////////////////////////////////////////////////////////////
	/// @brief Replace string by new one
	///
	/// @param input : Input string
	/// @param oldStr : string to replace
	/// @param newStr : new string
	///
	/// @return result
	///
	string Replace(const string & input, const char *oldStr, const char *newStr) const;



	resultmap m_Results; 							///< Result
	legalmap m_Legal; 								///< List of allowed options
	map<string,string>m_Duplicates;					///< List of duplicated options
	map<string,set<string> >m_Incompatibles; 		///< List of incompatible options
	map<string,vector<string> >m_Aliases; 			///< List of Aliases E.G. -h and --help
	set<string>m_MandatoryOptions; 					///< List of mandatory options
	set<set<string> >m_MandatoryOptionsOneAmongX; 	///< List of mandatory options (one among x)
	//set<string>m_HelpOptions; 					///< List of options which only shows help message

	set<string>m_Uncommented;						///< List of uncommented options : Do not show an option uncommented
	vector<string>m_RestArgs;						///< After --, all things are considered as arguments of option even if we have some - or --

	string m_Usage;									///< Usage message
	string m_Help;									///< Help message to be displayed
	string m_ProgramName;							///< Program name
	string m_LongProgramName;						///< Long program name

	map<string, string> m_DefaultValues;			///< Default values

	string m_FilteredOption;						///< To be shown the help of one option


	string m_Version;								///< Used when the help message is shown
	string m_ExternalSoftware;						///< Used when the help message is shown

	valmap m_Values;								///< List of values
	valmapcomb m_ValueCombination;					///< List of combination values
};

#endif // __MANAGE_OPTIONS_H__
