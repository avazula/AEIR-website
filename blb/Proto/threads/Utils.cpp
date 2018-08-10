//
// Created by avazula on 14/06/18.
//

#include "Utils.h"
#include <sstream>

std::string getErrorMessage(int errCode)
{
    std::ostringstream os;
#ifndef WIN32_THREADS
    os << " - Error " << errCode << " : " << strerror(errCode);
#else
    os << " - Error " << errCode;
#endif
    return os.str();
}