/*!
 * \class Camera
 * \brief Describes the object Camera and all its associated methods.
 *
 * This is the class dealing with all Camera attributes and associated
 * methods.
 *
 * \author Marie Brunet Carteaux | <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_CAMERA_H
#define MOD_CAMERA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "utils/Logger.h"

// Include stream prefixes here to avoid writing std:: in the whole project
// (because this header is included at the top of the project so it's
// applicable everywhere from here)
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::ifstream;

using std::vector;
using std::map;
using std::pair;

class Camera {
private:
    // ID of prior vehicle / coach
    uint priorID;
    uint cameraID;
    uint width;
    uint height;

public:
    Camera();
    Camera(uint, uint, uint, uint);
    ~Camera() {}

    uint getCameraID() const;
    void setCameraID(uint);
    uint getWidth() const;
    void setWidth(uint);
    uint getHeight() const;
    void setHeight(uint);
    uint getPriorID(void) const;
    void setPriorID(uint);
};


#endif //MOD_CAMERA_H
