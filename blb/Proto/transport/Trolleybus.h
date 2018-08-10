/*!
 * \class Trolleybus
 * \brief Specialization of the vehicle type. Describes the object Trolleybus and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_TROLLEYBUS_H
#define MOD_TROLLEYBUS_H

#include "Vehicle.h"

class Trolleybus: public Vehicle {
private:

public:
    Trolleybus();
    Trolleybus(uint, uint, tm, tm, uint, bool, uint, vector< Camera> &);
    ~Trolleybus();

    std::string getVehicleName(void) const override;
};


#endif //MOD_TROLLEYBUS_H
