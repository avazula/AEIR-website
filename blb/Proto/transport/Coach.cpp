#include "Coach.h"

/// Normal constructor
Coach::Coach(uint id, uint max, vector<Camera> cam, uint t) :
        coachID(id),
        maxCapacity(max),
        cameras(std::move(cam)),
        trainID(t) {}

/**
 * Gets and returns the coach identifier.
 * \return the coach identifier
 */
uint Coach::getCoachID(void) const {
    return coachID;
}

/**
 * Sets a new coach identifier
 * \param id       The new identifier to set
 */
void Coach::setCoachID(uint id) {
    coachID = id;
}


/** Gets and returns the Coach maximum capacity
 * \return the coach maximum capacity
 */
uint Coach::getMaxCapacity(void) const {
    return maxCapacity;
}

/**
 * Sets a new maximum capacity.
 * @param maxCapa the new capacity to set
 */
void Coach::setMaxCapacity(uint maxCapa) {
    maxCapacity = maxCapa;
}

uint Coach::getVehicleID() const {
    return trainID;
}

void Coach::setVehicleID(uint t) {
    trainID = t;
}