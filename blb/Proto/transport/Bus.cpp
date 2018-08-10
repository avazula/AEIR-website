/*!
 * \class Bus
 * \brief Specialization of the vehicle type. Describes the object Bus and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#include "Bus.h"

/// Default constructor
Bus::Bus() = default;

/**
 * Normal constructor
 * \param n         The vehicle name (bus)
 * \param v         The vehicle ID
 * \param l         The line ID
 * \param b         The time at which the bus is supposed to leave
 * \param e         The time at which the bus is supposed to arrive
 * \param m         The bus maximum capacity
 * \param i         Is the bus humane- or machine-driven?
 * \param md        The mode in which the bus currently is.
 */
Bus::Bus(uint v, uint l, tm b, tm e, uint m, bool i, uint md, vector< Camera >& cam) :
        Vehicle(v, l, b, e, m, i, md, cam) {
    LOG(DEBUG, "Created a bus with normal constructor.");
}

///*!
// * Copy constructor
// * \param b The bus to copy
// */
//Bus::Bus(const Bus& b) : Vehicle(b.vehicleID, b.lineID, b.beginTravel, b.endTravel, b.maxCapacity, b.isHuman, b.mode, b.cameras) {
//    LOG(DEBUG, "Created a bus with copy constructor.");
//}

/// Destructor
Bus::~Bus() {
    LOG(DEBUG, "Destroyed a bus.");
}

/**
 * \brief Gets and return the vehicle name (hence a bus)
 */
std::string Bus::getVehicleName(void) const {
    return "Bus";
}

//Bus& Bus::operator=(const Bus& b) {
//    if(this != &b) {
//
//    }
//}