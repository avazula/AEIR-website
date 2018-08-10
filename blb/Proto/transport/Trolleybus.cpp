//
// Created by Marie Brunet Carteaux on 07/05/18.
//

#include "Trolleybus.h"

/// Default constructor
Trolleybus::Trolleybus() = default;

/**
 * Normal constructor
 * \param v         The trolleybus ID
 * \param l         The line ID
 * \param b         The time at which the trolleybus is supposed to leave
 * \param e         The time at which the trolleybus is supposed to arrive
 * \param m         The trolleybus maximum capacity
 * \param i         Is the trolleybus humane- or machine-driven?
 * \param md        The mode in which the trolleybus currently is
 */
Trolleybus::Trolleybus(uint v, uint l, tm b, tm e, uint m, bool i, uint md, vector< Camera >& cam) :
        Vehicle(v, l, b, e, m, i, md, cam) {}

/// Destructor
Trolleybus::~Trolleybus() {}

/**
 * \brief Gets and return the vehicle name (hence a trolleybus)
 */
std::string Trolleybus::getVehicleName(void) const {
    return "Trolleybus";
}