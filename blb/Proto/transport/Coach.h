/*!
 * \class Coach
 * \brief Describes the object Coach and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_COACH_H
#define MOD_COACH_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>
#include "Proto/transport/Camera.h"

class Coach {
private:
    uint coachID;
    uint maxCapacity;
    // Cameras in coach
    vector< Camera > cameras;

    // Bond with vehicles
    uint trainID;

public:
    Coach(uint, uint, vector< Camera >, uint);
    uint getCoachID(void) const;
    void setCoachID(uint);
    uint getMaxCapacity(void) const;
    void setMaxCapacity(uint);
    uint getVehicleID(void) const;
    void setVehicleID(uint);

};


#endif //MOD_COACH_H
