/*!
 * \class Bus
 * \brief Specialization of the vehicle type. Describes the object Bus and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_BUS_H
#define MOD_BUS_H

#include "Vehicle.h"

class Bus: public Vehicle {
private:

public:
    Bus();
    Bus(uint, uint, tm, tm, uint, bool, uint, vector<Camera>&);
    Bus(const Bus&);
    Bus& operator=(const Bus&);
    ~Bus();


    std::string getVehicleName(void) const override;
    //void        displayVehicle(void) const override;
};


#endif //MOD_BUS_H
