/*!
 *
 */

#include "CriticalSection.h"
#include <iostream>
#include "Mutex.h"

using std::cout;
using std::cerr;
using std::endl;

/////////////////////////////////////////////////////////////////////////
/// \brief This class defines a Critical section.
///

/////////////////////////////////////////////////////////////////////////
/// \brief Constructor: Create and enter in critical section
///
CriticalSection::CriticalSection(Mutex & mutex) throw() : m_mutex(mutex)
{
	// Enter in Mutex
	try
	{
		m_mutex.enter();
	}
	catch (const MutexError & e)
	{
		// A fatal error is occurred
		cerr << e.what() << endl;
	}
	catch (...)
	{
		// A fatal error is occurred
		cerr << "Fatal error occured!" << endl;
	}
}

/////////////////////////////////////////////////////////////////////////
/// \brief Constructor: Leave and destroy the critical section
///
CriticalSection::~CriticalSection() throw()
{
	// Leave Mutex
	try
	{
		m_mutex.leave();
	}
	catch (const MutexError & e)
	{
		// A fatal error is occurred
		cerr << e.what() << endl;
	}
	catch (...)
	{
		// A fatal error is occurred
		cerr << "Fatal error occured!" << endl;
	}
}
