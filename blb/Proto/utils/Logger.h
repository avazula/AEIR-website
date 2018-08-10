/*!
 * \class Logger
 * \brief Defines logs for easier troubleshooting
 * \author Marie Brunet Carteaux | <marie.brunet@orange.com>
 * \date June 21, 2018
 */

#ifndef MOD_LOGGER_H
#define MOD_LOGGER_H

#include <iostream>

#define BOL     "\e[1m"
#define RED     "\e[31m"
#define BLU     "\e[34m"
#define GRE     "\e[37m"
#define YEL     "\e[33m"
#define RST     "\e[0m"

class Logger {
public:
    enum level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    explicit Logger(std::ostream& os);
    static void setlevel(const level = DEBUG);
    static std::ostream& setStream(std::ostream* os = 0);
    static void log(const level, const std::string& fileName, const unsigned int line, const std::string& msg);

};

#define LOG(level, string) Logger::log((Logger::level), __FILE__, __LINE__, (string));

#endif //MOD_LOGGER_H
