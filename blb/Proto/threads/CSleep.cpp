/////////////////////////////////////////////////////////////////////////
/// @file CSleep.cc
///
/// Created on: April 2014
/// Author: IT&Labs - Orange Business Services
///

#include "CSleep.h"

/////////////////////////////////////////////////////////////////////////
/// @brief This class defines a sleep.
///


/////////////////////////////////////////////////////////////////////////
/// @brief Sleep the current thread for specified milliseconds
///
/// @param millisec : time for slepp
///
void CSleep::sleep(unsigned long millisec)
{
#ifdef WIN32_THREADS
   Sleep(millisec);
#else

#ifdef _CYGWIN
   sleep(millisec/1000);
#else

#ifdef __MINGW32__
   Sleep(millisec);
#else
   struct timespec rqtp;
   rqtp.tv_sec = (int)(millisec/1000);
   rqtp.tv_nsec = (int)(millisec%1000)*1000000;

   nanosleep(&rqtp, NULL);
#endif
#endif
#endif
}
