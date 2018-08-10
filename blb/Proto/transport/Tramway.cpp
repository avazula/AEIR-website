#include "Tramway.h"

/// Default constructor
Tramway::Tramway() = default;

/**
 * Normal constructor
 * \param vehId     The tramway identifier
 * \param linId     The line identifier (on which the tramway is currently travelling)
 * \param bTravel   The time at which the tramway is supposed to leave
 * \param eTravel   The time at which the tramway is supposed to arrive
 * \param maxCapa   The tramway maximum capacity
 * \param isH       Is the tramway humane- or machine-driven?
 * \param mod       The mode in which the tramway currently is.
 * \param coaches   The coaches compounding the tramway.
 */
Tramway::Tramway(uint vehId, uint linId, tm bT, tm eT, uint mC, bool isH,
                 uint md, vector< Coach >& c, vector< Camera >& cam) :
Train(vehId, linId, bT, eT, mC, isH, md, c, cam) {}

/// Destructor
Tramway::~Tramway() = default;

/**
 * \brief Gets and return the vehicle name (hence a tramway)
 */
std::string Tramway::getVehicleName(void) const {
    return "Tramway";
}