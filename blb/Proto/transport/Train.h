/*!
 * \class Train
 * \brief Specialization of the vehicle type. Describes the object Train and all its associated methods.
 *
 * Train inherits from the Vehicle class and is inherited itself by the Tramway
 * and Tube classes. A train is composed of at least one Coach and its maximum capacity
 * is the sum of all its coaches' maximum capacity.
 *
 * \author Marie Brunet Carteaux | <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_TRAIN_H
#define MOD_TRAIN_H

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Proto/transport/Coach.h"

class Train: public Vehicle {

protected:
    vector< Coach > coaches;
    uint coachesCount = 0;

public:
    Train();
    Train(uint, uint, tm, tm, uint, bool, uint, vector< Coach >&, vector< Camera >&);
    ~Train();

    uint getMaxCapacity(void) const override;
    uint getCoachesCount(void) const ;
    Coach& getCoachAt(uint) const;
    void setCoachAt(uint, Coach&);
    std::string getVehicleName(void) const override;

};

#endif //MOD_TRAIN_H
