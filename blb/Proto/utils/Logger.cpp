//
// Created by avazula on 21/06/18.
//

#include "Logger.h"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <strings.h>
#include <chrono>
#include <iomanip>

namespace {
    std::ostream* checkLoggingOutput(void) {

        std::ostream* logout = &std::cout;
        std::stringstream logfilename;
        char* home = getenv("HOME");
        char* env = getenv("ITLOGFILE");

        if((home != NULL) && (env != NULL)) {
            logfilename << home << "/" << env;
            std::ofstream* ofs = new std::ofstream(logfilename.str().c_str(), std::ofstream::out | std::ofstream::app);

            if(ofs != NULL && ofs->is_open()) {
                logout = ofs;
            }
        }
        return logout;
    }

    std::ostream* outPtr = checkLoggingOutput();

    const Logger::level  checkLogginglevel(void) {
        Logger::level level = Logger::ERROR;
        char* env = getenv("ITLOGlevel");

        if(env != NULL) {
            if(strcasecmp(env, "INFO") == 0)
                level = Logger::level::INFO;
            else if(strcasecmp(env, "WARN") == 0)
                level = Logger::level::WARN;
            else if(strcasecmp(env, "ERROR") == 0)
                level = Logger::level::ERROR;
            else if(strcasecmp(env, "DEBUG") == 0)
                level = Logger::level::DEBUG;
        }
        return level;
    }

    Logger::level levelFilter = checkLogginglevel();

    std::ostream& setStream(std::ostream* ostr) {
        outPtr = ostr != NULL ? ostr : &std::cout;
        return *ostr;
    }

    const char* lname[] = {
            "DEBUG : ",
            "INFO  : ",
            "WARNING : ",
            "ERROR : "
    };

    const char* levelToString(const Logger::level level) {
        return (level >= 0 && level < sizeof(lname)) ? lname[level] : "UNKNOWN : ";
    }
} // End anonymous namespace

Logger::Logger(std::ostream &ostr) {
    setStream(&ostr);
}

std::ostream &Logger::setStream(std::ostream *ostr) {
    return setStream(ostr);
}

void Logger::setlevel(const Logger::level level) {
    ::levelFilter = level;
}

void Logger::log( const level level, const std::string& fileName, const unsigned int line, const std::string& message) {

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    switch(level) {
        case DEBUG:
            *outPtr << BOL << GRE << "DEBUG: " << RST << GRE;
            break;
        case INFO:
            *outPtr << BOL << BLU << "INFO: " << RST << BLU;
            break;
        case WARN:
            *outPtr << BOL << YEL << "WARNING: " << RST << YEL;
            break;
        case ERROR:
            *outPtr << BOL << RED << "ERROR: " << RST << RED;
            break;
        default:
            *outPtr << BOL << RST << "UNKNOWN: ";
            break;
    }

    auto gmt_time = gmtime(&time);
    auto timestamp = std::put_time(gmt_time, "%d %m %y %H:%M:%S");
    *outPtr << timestamp << " | " << fileName << " | Line " << line << " | " << message << RST << std::endl;
}
