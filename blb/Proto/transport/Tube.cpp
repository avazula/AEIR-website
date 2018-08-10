#include "Tube.h"

///Default constructor
Tube::Tube() = default;

/**
 * Normal constructor
 * \param vehId     The tube identifier
 * \param linId     The line identifier (on which the tube is currently travelling)
 * \param bTravel   The time at which the tube is supposed to leave
 * \param eTravel   The time at which the tube is supposed to arrive
 * \param maxCapa   The tube maximum capacity
 * \param isH       Is the tube humane- or machine-driven?
 * \param mod       The mode in which the tube currently is.
 * \param coaches   The coaches compounding the tube.
 */
Tube::Tube(uint v, uint l, tm b, tm e, uint m, bool i, uint md, vector< Coach >& c, vector< Camera >& cam) :
        Train(v,l,b,e,m,i,md,c, cam) {}

/// Destructor
Tube::~Tube() = default;

/**
 * \brief Gets and returns the vehicle name (hence a tube).
 */
std::string Tube::getVehicleName(void) const {
    return "Tube";
}