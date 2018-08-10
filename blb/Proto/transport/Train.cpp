#include "Train.h"

using namespace std;

/// Default constructor
Train::Train() {}

/**
 * \brief Normal constructor (without default parameters), inherited from Vehicle's normal constructor
 *
 * \param vehId     The train identifier
 * \param linId     The line identifier (on which the train is currently travelling)
 * \param bTravel   The time at which the train is supposed to leave
 * \param eTravel   The time at which the train is supposed to arrive
 * \param maxCapa   The train maximum capacity
 * \param isH       Is the train humane- or machine-driven?
 * \param mod       The mode in which the train currently is.
 * \param coaches   The coaches compounding the train.
 */
Train::Train(uint vehId, uint linId, tm bTravel, tm eTravel, uint maxCapa, bool isH, uint mod, vector< Coach >& coach, vector< Camera >& cam) :
        Vehicle(vehId, linId, bTravel, eTravel, maxCapa, isH, mod, cam) {
    coachesCount = 0;
    for(int i = 0; i < coach.size(); i ++) {
        coaches.push_back(coach[i]);
        maxCapacity += coach[i].getMaxCapacity();
        coachesCount++;
    }
}

/**
 * \brief Destructor
 */
Train::~Train() {}

/**
 * \brief Gets and returns the train's maximum capacity.
 */
uint Train::getMaxCapacity(void) const {
    return maxCapacity;
}

/**
 * \brief Gets and returns the number of coaches compounding the Train.
 */
uint Train::getCoachesCount(void) const {
    return coachesCount;
}

/**
 * \brief Gets and returns the Coach found regarding the given location.
 * \param i    The location to look for in the vector of coaches.
 * \return      The corresponding Coach if found.
 */
Coach& Train::getCoachAt(uint i) const {
    return (Coach&)coaches[i-1];
}

/**
 * \brief Modifies the Coach found regarding the given location.
 * \param i    The location in the vector of the Coach to be modified.
 * \param coach
 */
void Train::setCoachAt(uint i, Coach& coach) {
    coaches[i-1] = coach;
}

/**
 * \brief Gets and return the vehicle name (hence a train)
 */
std::string Train::getVehicleName(void) const {
    return "Train";
}

