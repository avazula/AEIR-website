/*!
 * \class CriticalSection
 * \date April 2014
 * \author IT&Labs - Orange Business Services
 */

#ifndef MOD_CRITICALSECTION_H
#define MOD_CRITICALSECTION_H

class Mutex;

/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a Critical section.
///	It allows to create a critical section within a block statement by declaring
/// an instance at the beginning of the block.
///
class CriticalSection
{
public:
    /////////////////////////////////////////////////////////////////////////
    /// @brief Constructor: Create and enter in critical section
    ///
    CriticalSection(Mutex & mutex) throw();

    /////////////////////////////////////////////////////////////////////////
    /// @brief Constructor: Leave and destroy the critical section
    ///
    ~CriticalSection() throw();

private:
    Mutex & m_mutex;
};

#endif //MOD_CRITICALSECTION_H
