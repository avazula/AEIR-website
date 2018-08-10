/////////////////////////////////////////////////////////////////////////
/// @file ManageOptions.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///


/////////////////////////////////////////////////////////////////////////
/// @brief This class is used to manage options passed as arguments on
/// command line
///
//
//  Usage:
//
//  Specify the long option (--word) and short ones (-x),
//  following with '=' (the option takes a value among ...)
//  and following by space and comments:
//
//      const char *longOptions[] = {"--config= config file",
//	  	          "--verbose with lot of logs",
//		          "--silent without message",
//		          "--out=",
//		          "--log=",
//		          0};
//
//      const char *shortOpts[] = {"-c", "-l=", 0};
//
//   So an object is defined:
//      ManageOptions opt(longOpts, shortOpts);
//
//   It's possible to specify the program name, help message:
//      opt.setNom(argv[0]);  or opt.setNom("MyprogramName");
//      opt.setUsage("_PROGRAMME_ [options] [file(s)]");
//      opt.setHelp("This is the help message");
//
//   For some options with values, we can define the possible values:
//      opt.limitValues("--out", "XML,ASCII,BOTH");
//
//	 It's possible to specify that one option is mandatory
//      opt.setMandatoryOption("--config");
//
//   Then we check if arguments are correct:
//
//      ManageOptions::resultmap *res;
//      try
//		{
//	  		res = opt.options(argc, argv);
//
//   Now, we can switch the result:
//
//	  		for (ManageOptions::resultmap::iterator mi = res->begin(); mi != res->end(); ++mi)
//			{
//	     		if (mi->first == "--config")
//				{
//	         		configFile = mi->second;
//	     		}
//	     		else // ...
//			}
//
//   Don't forget the catch
//      }
//			catch(ManageOptions::ManageOptionsError &e)
//			{
//	   			cerr << e.what() << endl;
//   	   		throw;
//			}
//       }
//


// System dependencies
//--------------------
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib> // for getenv
using namespace std;



// Provided APIs
//--------------
#include "ManageOptions.h"



////-------- !!! MUST BE THE LAST INCLUDED FILE !!! ------
//
////------------------------------------------------------




/////////////////////////////////////////////////////////////////////////
/// @brief Constructor
///
/// @param legalLongOptions [in] : list of long enabled option
/// @param legalShortOptions [in] : list of short enabled option
///
ManageOptions::ManageOptions(const char *legalLongOptions[], const char *legalShortOptions[])
{
	// For each long options
	for (const char **i = legalLongOptions; *i != 0; ++i)
	{
		string tmp = string(*i);
		string doc = "";
		string option;
		// Search comment  begin
		string::size_type endOption = tmp.find(' ');
		if (endOption != string::npos)
		{
			// Split string in options and comments
			option = tmp.substr(0, endOption);
			doc = tmp.substr(endOption+1);
		}
		else
		{
			option = tmp;
		}
		int olen = option.size();
		struct argDoc atmp;
		atmp.doc = doc;

		// If option is ended with '=', it's an option with value
		if (option[olen-1] == '=')
		{
			// Option with value
			atmp.hasArg = true;
			m_Legal[option.substr(0, olen-1)] = atmp;
		}
		else
		{
			// Option w/o value
			atmp.hasArg = false;
			m_Legal[option] = atmp;
		}

	}

	// For each short options
	for (const char **i = legalShortOptions; *i != 0; ++i)
	{
		string tmp = string(*i);
		string doc = "";
		string option;
		// Search comment  begin
		string::size_type endOption = tmp.find(' ');

		if (endOption != string::npos)
		{
			option = tmp.substr(0, endOption);
			doc = tmp.substr(endOption+1);
		}
		else
		{
			option = tmp;
		}

		int olen = option.size();
		struct argDoc atmp;
		atmp.doc = doc;

		// If option is ended with '=', it's an option with value
		if (option[olen-1] == '=')
		{
			// Option with value
			atmp.hasArg = true;
			m_Legal[option.substr(0, olen-1)] = atmp;
		}
		else
		{
			// Option w/o value
			atmp.hasArg = false;
			m_Legal[option] = atmp;
		}
	}
}


/////////////////////////////////////////////////////////////////////////
/// @brief Destructor
///
ManageOptions::~ManageOptions()
{
}



/////////////////////////////////////////////////////////////////////////
/// @brief Operator<<  to display ManageOptions to out stream
///
/// @param out [in] : Stream
/// @param manageOptions [in] : Object
///
/// @return new Stream
///
ostream& operator<<(ostream & out, const ManageOptions &manageOptions)
{
	string nom;
	if (!manageOptions.m_ProgramName.empty())
	{
		string::size_type pos = manageOptions.m_ProgramName.rfind("/");
		if (pos != string::npos)
		{
			// 		out << mo.nomProgramme.substr(pos+1) << endl;
			nom = manageOptions.m_ProgramName.substr(pos+1);
		}
		else
		{
			// 		out << mo.nomProgramme << endl;
			nom = manageOptions.m_ProgramName;
		}
	}
	if (!manageOptions.m_Help.empty())
	{
		unsigned int minLineLen = 60;
		char *envVar = getenv("COLUMNS");
		if (envVar != 0)
		{
			//cerr << "DDDD:" << ChaineCar::visibleString(envVar) << endl << endl;
			int len = atoi(envVar);
			if (len > 20)
			{
				minLineLen = len-15;
			}
		}
		//cerr << "GGGG:" << minLineLen << endl;
		unsigned int start = 0;
		//out << endl;
		string indent = "";
		if (manageOptions.m_Help.size() > minLineLen)
		{
			// Compute "\n" if needed
			string::size_type pos = manageOptions.m_Help.substr(minLineLen).find(" ");
			while (pos != string::npos)
			{
				out //<< start << ' '<< minLineLen+pos << ' '
				<< indent << manageOptions.m_Help.substr(start, minLineLen+pos) << endl;
				start += minLineLen+pos+1;
				//out << "ON CHERCHE DANS [" << go.help.substr(start+minLineLen) <<"]" << endl;
				//out << "start+mll " << start+minLineLen << ' ' << mo.help.size() << endl;

				if (start+minLineLen >= manageOptions.m_Help.size()) break;
				pos = manageOptions.m_Help.substr(start+minLineLen).find(" ");
				//out << "POS " << pos << endl;
			}
		}
		out << indent << manageOptions.m_Help.substr(start) << endl;
	}

	string usage = manageOptions.Replace(manageOptions.m_Usage, "_PROGRAMME_", nom.c_str());
	//if (mo.filteredOption.empty()) {
	out << endl << "usage: " << usage << endl << "\noptions (a [*] indicates an obligatory option):" << endl;
	//}
	for (ManageOptions::legalmap::const_iterator ii = manageOptions.m_Legal.begin(); ii != manageOptions.m_Legal.end(); ++ii)
	{
		if (manageOptions.m_Uncommented.find(ii->first) != manageOptions.m_Uncommented.end())
		{
			// Do not show an option uncommented
			continue;
		}
		else if (!manageOptions.m_FilteredOption.empty() && manageOptions.m_FilteredOption != ii->first)
		{
			continue;
		}
		int olen = ii->first.size() + (ii->second.hasArg ? 6 : 0);
		int rest = 25 - olen;
		if (rest < 1) rest = 1;
		string fill(rest, ' ');

		ManageOptions::valmap vals = manageOptions.m_Values;
		ManageOptions::valmap::iterator vi = vals.find(ii->first);

		out << "  "
				<< (manageOptions.m_MandatoryOptions.find(ii->first) != manageOptions.m_MandatoryOptions.end() ? "[*] " : "")
				<< ii->first
				<< (ii->second.hasArg ? (vi != vals.end() ? " <val>" : " <arg>") : "")
				//<< endl
				;
		map<string,vector<string> >::const_iterator ait = manageOptions.m_Aliases.find(ii->first);
		if (ait != manageOptions.m_Aliases.end())
		{
			for (vector<string>::const_iterator it = ait->second.begin(); it != ait->second.end(); ++it)
			{
				out << ",  "
						//<< (mo.mandatoryoptions.find(ii->first) != mo.mandatoryoptions.end() ? "[*] " : "")
						<< *it
						<< (ii->second.hasArg ? (vi != vals.end() ? " <val>" : " <arg>") : "")
						//<< endl
						;
			}
		}
		if (ii->second.hasArg)
		{
			map<string,string>::const_iterator itd = manageOptions.m_DefaultValues.find(ii->first);
			if (itd != manageOptions.m_DefaultValues.end())
			{
				out << "\n\tdefault argument: " << itd->second << endl;
			}
		}
		out << endl;
		// Add something here to limit the line size to 80 char
		string docline = manageOptions.Replace(ii->second.doc, "\n",  "\n\t");
		out << "\t" << docline << endl << endl;

		if (vi != vals.end()) {
			out << "    possible values for this option:" << endl
					<< "      ";
			int vallen = 0;
			int maxlen = 0;
			// get longest option value
			for (set<string>::iterator si = vi->second.begin(); si != vi->second.end(); ++si)
			{
				int curlen = si->size();
				curlen > maxlen ? maxlen = curlen : maxlen;
			}

			maxlen++;

			for (set<string>::iterator si = vi->second.begin(); si != vi->second.end(); ++si)
			{
				//out << '\t' << *si;
				//vallen += (8 + si->size());

				out.width(maxlen);
				//out.fill('^');
				out.setf(ios::left);
				out << si->c_str();
				vallen += maxlen;
				if (vallen + maxlen > 79)
				{
					out << endl << "      ";
					vallen = 0;
				}
			} // endfor
			out << endl << endl;
		} // endif vi != vals.end()
		map<string,set<string> >::const_iterator incmap = manageOptions.m_Incompatibles.find(ii->first);
		if (incmap != manageOptions.m_Incompatibles.end())
		{
			out << "\toptions which are incompatible with this option\n";
			for (set<string>::const_iterator inc = incmap->second.begin(); inc != incmap->second.end(); ++inc)
			{
				out << "\t  " <<  manageOptions.getOptionName(*inc) << endl;
			}
			out << endl << endl;
		}
		//#ifndef PASDELOG
	} // endelse
	//#endif

	return out;
}


/////////////////////////////////////////////////////////////////////////
/// @brief Check the option found
///
/// @param ac [in] : Number of arguments
/// @param av [in] : Arguments array
///
/// @return List of Options
///
const ManageOptions::resultmap * ManageOptions::analyzeOptions(int ac, char *av[])
		throw(UnknownOption, IncorrectValue, NoArgumentAllowed, ArgumentWithoutOption, ArgumentRequired, IncompatibleOptions, MissingMandatoryOption)
{
	legalmap::iterator sbi = m_Legal.end();
	map<string,string>::iterator dmi;
	bool expectingOption = true;
	string curopt = "";
	string curarg;
	bool foundDoubleHyphen = false;
	//cout << "legal options: " << legal << endl;

	// resolving short arguments: -sp ==> -s -p
	vector<string>argsExpanded;
	for (int i = 1; i<ac; ++i)
	{
		//cout << "AV[" << i << "]:" << av[i] << endl;
		if (foundDoubleHyphen)
		{
			// We found an option with -- then it's a real option
			curarg = string(av[i]);
			argsExpanded.push_back(curarg);
		}
		//else if (av[i][0] != '-' || (av[i][0] == '-' && av[i][1] == '-'))
		else if (av[i][0] != '-' ||  av[i][1] == '-')
		{
			curarg = string(av[i]);
			//cout << " EXP1:" << curarg << endl;
			if (curarg == "--") foundDoubleHyphen = true;
			argsExpanded.push_back(curarg);
		}
		else
		{
			curarg = string(av[i]);
			string::iterator ii = curarg.begin();
			++ii;
			for (; ii != curarg.end(); ++ii)
			{
				curopt = *ii;
				//cout << " EXP2:" << curopt << endl;
				argsExpanded.push_back("-" + curopt);
			}
			//cout << "EEE " << argsExpanded << endl;
		}
	}

	//cout << "EEE " << argsExpanded << endl;

	for (vector<string>::iterator progarg = argsExpanded.begin(); progarg != argsExpanded.end(); ++progarg)
	{
		//cout << "ARG: " << *progarg << endl;
		// for all arguments passed to the program
		if (*progarg == "--")
		{
			// After --, all things are considered as arguments of option even if we have some - or --
			++progarg;
			for ( ; progarg != argsExpanded.end(); ++progarg)
			{
				m_RestArgs.push_back(*progarg);
			}
			break;
		}
		if (expectingOption)
		{
			// we are looking for an option
			if ((*progarg)[0] == '-')
			{
				// this looks like an option
				int equal = progarg->find('=');
				if (equal > -1)
				{
					// option du type: --option=value
					//cout << " ww " << progarg.substr(0, equal) << endl;
					sbi = m_Legal.find(progarg->substr(0, equal));
					if (sbi == m_Legal.end())
					{
						// may be it's a duplicate
						dmi = m_Duplicates.find(progarg->substr(0, equal));
						if (dmi == m_Duplicates.end())
						{
							// no, it isn't
							throw UnknownOption(*progarg);
						}
						else
						{
							// the option was a double, we look for
							// the original name
							sbi = m_Legal.find(dmi->second);
						}
					}
					// yes it is
					if (sbi->second.hasArg)
					{
						// and it needs an argument
						if (valueOK(sbi->first, progarg->substr(equal+1)))
						{
							m_Results[sbi->first] = progarg->substr(equal+1);
						}
						else
						{
							throw IncorrectValue(getOptionName(sbi->first),
									sbi->first, //progarg->substr(0, equal),
									progarg->substr(equal+1),
									m_Values);
						}

					}
					else
					{
						// we cannot use --option=arg for options
						// which must not have an argument
						throw NoArgumentAllowed(getOptionName(sbi->first), progarg->substr(0, equal));
					}

				}
				else
				{
					// Option type: --option [val]
					// is the found option legal?
					sbi = m_Legal.find(*progarg);
					if (sbi == m_Legal.end())
					{
						// may be it's a duplicates
						//cout << " doublons? " << endl;
						dmi = m_Duplicates.find(*progarg);
						if (dmi == m_Duplicates.end())
						{
							// no, it isn't
							throw UnknownOption(*progarg);
						}
						else
						{
							// the option was a double, we look for
							// the original name
							sbi = m_Legal.find(dmi->second);
						}
					}

					// yes it is
					if (sbi->second.hasArg)
					{
						// and it needs an argument
						// so we stock the option in curopt
						curopt = sbi->first; //*progarg;
						expectingOption = false;
					}
					else
					{
						// no argument required

						m_Results[sbi->first] = "";
					}
				}
			}
			else
			{
				// we did not found an option,
				// but if all following programme arguments
				// are simple arguments it is OK
				bool moreoptions = false;
				for (vector<string>::iterator jj = progarg+1; jj != argsExpanded.end(); ++jj)
				{
					if (*jj == "--")
					{
						// End of options list
						break;
					}
					else if ((*jj)[0] == '-')
					{
						moreoptions = true;
						break;
					}
				}
				//cout << "MO " << moreoptions << endl;

				if (moreoptions)
				{
					// expecting more options since an option was found
					// further down
					if (sbi != m_Legal.end())
						throw NoArgumentAllowed(getOptionName(sbi->first), *(progarg--));
					else
					{
						// No option are found
						throw ArgumentWithoutOption(*(progarg--));
					}
				}
				else
				{
					// in fact, all the rest are arguments

					for ( ; progarg != argsExpanded.end(); ++progarg)
					{
						m_RestArgs.push_back(*progarg);
					}

					break;
				}
			}
		}
		else
		{
			// we are looking for an argument
			if ((*progarg)[0] != '-')
			{
				if (valueOK(curopt, *progarg))
				{
					m_Results[curopt] = *progarg;
				}
				else throw IncorrectValue(getOptionName(curopt), curopt, *progarg, m_Values);

				//results[curopt] = *progarg;
			}
			else
				//throw ExpectingArgument(curopt);
				throw ArgumentRequired(getOptionName(curopt));

			// the next
			expectingOption = true;
		}
	} // endfor


	if (!expectingOption)
	{
		throw ArgumentRequired(curopt);
	}

	for (map<string, set<string> >::iterator it = m_Incompatibles.begin(); it != m_Incompatibles.end(); ++it)
	{
		if (m_Results.find(it->first) != m_Results.end())
		{
			for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if (m_Results.find(*it2) != m_Results.end())
				{
					//throw IncompatibleOptions(it->first, *it2);
					throw IncompatibleOptions(getOptionName(it->first), getOptionName(*it2));
				}
			}
		}
	}

	// To search if one option if a help one
//	bool hasHelpOption = false;
//	for (set<string>::iterator it = helpoptions.begin(); it != helpoptions.end(); ++it)
//	{
//		if (m_Results.find(*it) != m_Results.end())
//		{
//			//throw HelpOption(*it);
//			hasHelpOption = true;
//		}
//	}

//	if (!hasHelpOption)
	{
		for (set<set<string> >::iterator it2 = m_MandatoryOptionsOneAmongX.begin(); it2 != m_MandatoryOptionsOneAmongX.end(); ++it2)
		{
			bool foundOneOption = false;
			for (set<string>::iterator it1 = it2->begin(); it1 != it2->end(); ++it1)
			{
				if (m_Results.find(*it1) != m_Results.end())
				{
					foundOneOption = true;
					break;
				}
			}
			if (!foundOneOption)
			{
				ostringstream str;
				for (set<string>::iterator its = it2->begin(); its != it2->end(); ++its)
				{
					if (its != it2->begin()) str << "/";
					str << getOptionName(*its);
				}
				//throw MissingMandatoryOption(*it2);
				throw MissingMandatoryOption(str.str());
			}
		}
	}
	//cout << "RES " << results << endl << restArgs << endl;
	return &m_Results;
}



/////////////////////////////////////////////////////////////////////////
/// @brief Set the limit value for one option
///
/// @param option [in] : Option
/// @param values [in] : Arguments array
/// @param combination : If true, allow any values
///
void ManageOptions::setLimitValues(const char *option, const char *values, bool combination)
{
	string o = string(option);
	string va = string(values);

	vector<string>v;
	Split(v, va, ",");
	for (vector<string>::iterator vi = v.begin(); vi != v.end(); ++vi)
	{
		if (!vi->empty())
		{
			m_Values[o].insert(*vi);
		}
	}
	if (combination)
	{
		m_ValueCombination[o] = true;
	}
}


/////////////////////////////////////////////////////////////////////////
/// @brief Set alias for one option
///
/// @param d [in] : Source Option
/// @param o [in] : Duplicate option
///
void ManageOptions::setAliasOption(const string &d, const string &o) throw(UnknownOption, DuplicatedOption)
{
	//cout << "ddd: '" << d << "' doubles '" << o << "'" << endl;
	// cout << legal << endl;
	if (m_Legal.find(o) == m_Legal.end())
	{
		cerr << "Option '" << o << "' (and its alias '" << d << "') do not exist" << endl;
		throw UnknownOption(o);
	}
	if (m_Legal.find(d) != m_Legal.end())
	{
		cerr << "New duplicated '" << d << "' is a different valid option" << endl;
		throw DuplicatedOption(d);
	}
	if (m_Duplicates.find(d) != m_Duplicates.end())
	{
		cerr << "Duplicated option '" << d << "' (doubles already '" << m_Duplicates[d] << "' and now also '" << o << "')" << endl;
		throw DuplicatedOption(d);
	}
	m_Duplicates[d] = o;
	m_Aliases[o].push_back(d);
}

/////////////////////////////////////////////////////////////////////////
/// @brief Get the program name and copyright information
///
/// @return information
///
string ManageOptions::getTitle() const
{
	ostringstream msg;
	if (!m_LongProgramName.empty())
	{
		msg << m_LongProgramName << endl;
	}
	else if (!m_ProgramName.empty())
	{
		string::size_type pos = m_ProgramName.rfind("/");
		if (pos != string::npos)
		{
			msg << m_ProgramName.substr(pos+1) << endl;
		}
		else
		{
			msg << m_ProgramName << endl;
		}
	}
	msg << endl << m_Version << endl;

	return msg.str();
}


/////////////////////////////////////////////////////////////////////////
/// @brief Get the version information
///
/// @return information
///
string ManageOptions::getVersion() const
{
	ostringstream msg;
	msg << endl << m_Version << endl;
	msg << endl << m_ExternalSoftware << endl;

	return msg.str();
}

/////////////////////////////////////////////////////////////////////////
/// @brief Set the default value for one option
///
/// @param option [in] : Option
/// @param value [in] : Value
///
void ManageOptions::setDefaultValue(const string &option, const string &value)
{
	m_DefaultValues[option] = value;
}




/////////////////////////////////////////////////////////////////////////
/// @brief Specify the option as mandatory
///
/// @param option [in] : Option
///
void ManageOptions::specifyOptionAsMandatory(const string &option) throw(UnknownMandatoryOption)
{
	vector<string>tmp;
	Split(tmp, option, ",");
	set<string>opts;
	for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		if (m_Legal.find(*it) == m_Legal.end()) throw UnknownMandatoryOption(option);
		opts.insert(*it);
		m_MandatoryOptions.insert(*it);
	}
	m_MandatoryOptionsOneAmongX.insert(opts);
}



/////////////////////////////////////////////////////////////////////////
/// @brief Set the filter when the help message is shown
///
/// @param option [in] : Option
///
void ManageOptions::setHelpFilter(const string &option)
{
	if (!option.empty())
	{
		if (option[0] == '-') m_FilteredOption = option;
		else
		{
			if (option.size() > 1)
			{
				m_FilteredOption = "--" + option;
			}
			else
			{
				m_FilteredOption = "-" + option;
			}
		}
	}
}



/////////////////////////////////////////////////////////////////////////
/// @brief Set two option incompatible
///
/// @param o1 [in] : Option 1
/// @param o2 [in] : Option 2
///
void ManageOptions::setIncompatibles(const string &o1, const string &o2)
{
	m_Incompatibles[o1].insert(o2);
	m_Incompatibles[o2].insert(o1);
}





/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::ManageOptionsError::ManageOptionsError(string message) : exception()
{
}


/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::UnknownOption::UnknownOption(string p) : ManageOptionsError("[ManageOptions] unknown option: " + p)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::DuplicatedOption::DuplicatedOption(string p) : ManageOptionsError("[ManageOptions] Option name used more than once " + p)
{
}


/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::UnknownMandatoryOption::UnknownMandatoryOption(string p) : ManageOptionsError("[ManageOptions] unknown mandatory option: " + p)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::MissingMandatoryOption::MissingMandatoryOption(string p) : ManageOptionsError("[ManageOptions] missing mandatory option: " + p)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::MissingMandatoryOption::MissingMandatoryOption(set<string> p) : ManageOptionsError("[ManageOptions] one of the following options is mandatory:")
{
	for (set<string>::iterator it = p.begin(); it != p.end(); ++it)
	{
//		appendMessage(" " + *it);
		cout << *it << endl;
	}
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::ArgumentRequired::ArgumentRequired(string p) : ManageOptionsError("[ManageOptions] missing option argument: " + p)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::IncorrectValue::IncorrectValue(string fullname, string o, string v, valmap&values) : ManageOptionsError("[ManageOptions] option : " + fullname + " invalid value: " + v)
{
	cout << "\npossible values: \n";
	for (set<string>::iterator si = values[o].begin(); si != values[o].end(); ++si)
	{
		cout << "\t" + *si + "\n";
	}
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::NoArgumentAllowed::NoArgumentAllowed(string o, string p) : ManageOptionsError("[ManageOptions] option " + o + " does not take argument: " + p)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::ArgumentWithoutOption::ArgumentWithoutOption(string p) : ManageOptionsError("[ManageOptions] argument '" + p + "' not preceeded by any option")
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief Constructor of Exception
///
ManageOptions::IncompatibleOptions::IncompatibleOptions(string o1, string o2) : ManageOptionsError("[ManageOptions] option " + o1 + " cannot be used together with option " + o2)
{
}




///// PRIVATE ////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
/// @brief Get the option name
///
/// @param baseOption [in] : Option
///
/// @return List with duplicates option
///
string ManageOptions::getOptionName(const string &optionDeBase) const
{
	ostringstream nom;
	nom << optionDeBase;
	//map<string,vector<string> >::const_iterator itm = aliases.find(optionDeBase);
	//if (itm != aliases.end()) {
	//nom << " " << itm->second;
	//}
	return nom.str();
}


/////////////////////////////////////////////////////////////////////////
/// @brief Set the limit value for one option
///
/// @param opt [in] : Option
/// @param val [in] : value
///
/// @return true if value is correct
///
bool ManageOptions::valueOK(const string &opt, const string &val)
{
	valmap::iterator vi = m_Values.find(opt);
	if (vi == m_Values.end()) return true;
	else {
		set<string>::iterator si = vi->second.find(val);
		if (si != vi->second.end()) return true;

		// List of values are possible
		if (m_ValueCombination.find(opt) != m_ValueCombination.end())
		{
			vector <string> vals;
			SplitNoEmptyFields(vals, val, ",");
			for (vector<string>::iterator it = vals.begin(); it != vals.end(); ++it) {
				// Check if all values are correct
				if (vi->second.find(*it) == vi->second.end()) {
					// No, one is wrong
					cout << " false " << endl;
					return false;
				}
			}
			return true;
		}

		return false;
	}
}


/////////////////////////////////////////////////////////////////////////
/// @brief Split a string ans put result in vector. Empty part are removed
///
/// @param result : to save result
/// @param input : string to split
/// @param delimit : delimiter
///
void ManageOptions::SplitNoEmptyFields(vector<string> &result, const string &input, const char *delimit) const
{
	result.clear();
	if (!delimit) return;
	string::size_type pos1 = 0;
	string::size_type pos2 = input.find(delimit,pos1);
	while (pos2 != string::npos)
	{
		if (pos2-pos1)
		{
			// on ne rajoute pas des �l�ments de longueur 0
			result.push_back(string(input,pos1,pos2-pos1));
		}
		pos1 = pos2 + strlen(delimit);
		pos2 = input.find(delimit,pos1);
	}

	if (input.size()-pos1)
	{
		result.push_back(string(input,pos1,pos2-pos1));
	}
}

/////////////////////////////////////////////////////////////////////////
/// @brief Split a string ans put result in vector. Empty part are removed
///
/// @param result : to save result
/// @param input : string to split
/// @param delimit : delimiter
/// @param numberOfSplits : number of wanted splits. If 0, all parts are split
///
void ManageOptions::Split(vector<string>&result, const string &input, const char *delimit, unsigned int numberOfSplits) const
{
	result.clear();
	if (!delimit) return;
	if (input.empty()) return;

	string::size_type pos1 = 0;
	string::size_type pos2 = input.find(delimit,pos1);
	unsigned int count = 0;
	while (pos2 != string::npos)
	{
		if (numberOfSplits  && count == numberOfSplits)
		{
			pos2 = string::npos;
			break;
		}
		result.push_back(string(input,pos1,pos2-pos1));
		pos1 = pos2 + strlen(delimit);
		pos2 = input.find(delimit,pos1);
		count++;
	}

	result.push_back(string(input,pos1,pos2-pos1));
}



/////////////////////////////////////////////////////////////////////////
/// @brief Replace string by new one
///
/// @param input : Input string
/// @param oldStr : string to replace
/// @param newStr : new string
///
/// @return result
///
string ManageOptions::Replace(const string & input, const char *oldStr, const char *newStr) const
{
	string result = input;
	if (!oldStr) return result;
	if (!newStr) return result;
	if (strlen(oldStr) == 0) return result;
	string::size_type pos = result.find(oldStr,0);
	while (pos != string::npos)
	{
		result.replace(pos,strlen(oldStr),newStr);
		pos = result.find(oldStr,pos+strlen(newStr));
	}

	return(result);
}


