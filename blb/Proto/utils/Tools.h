/*!\class Tools
 * \brief Defines useful methods and stuff for the project.
 * \author Marie BRUNET CARTEAUX | < marie.brunet@orange.com >
 * \date June 5, 2018
 */

#ifndef MOD_TOOLS_H
#define MOD_TOOLS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <unistd.h>

#define GetCurrentDir getcwd

using std::string;

/**\brief Returns the current working directory.
 *
 * This code has been written by Programming Knowledge for CodeBind
 * and can be found at https://goo.gl/wRbRYw.
 *
 * \return A string containing the path to the current working directory.
 */
inline string getCurrentWorkingDir() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    string current_working_dir(buff);
    current_working_dir += "/..";
    return current_working_dir;
}

#endif //MOD_TOOLS_H
