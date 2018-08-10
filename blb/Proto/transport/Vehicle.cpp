#include "Vehicle.h"

/// Default constructor.
Vehicle::Vehicle() {}

/**
* \brief Normal constructor.
* \param v the vehicle ID.
* \param l the line ID.
* \param b the beginning time of travelling.
* \param e the ending time of travelling.
* \param m the maximum capacity.
* \param i boolean ruling the nature of driver (human or machine?)
* \param mod the vehicle mode (offline, in_mission, waiting).
*/
Vehicle::Vehicle(uint v, uint l, tm& b, tm& e, uint m, bool i, uint mod, vector< Camera >& cam) :
        vehicleID(v),
        lineID(l),
        beginTravel(b),
        endTravel(e),
        maxCapacity(m),
        isHuman(i),
        mode(mod) {

    camerasCount = 0;
    for(const auto& item : cam) {
        cam.push_back(item);
        camerasCount++;
    }
}

/**
 * \brief Gets and returns the vehicle maximum capacity.
 */
uint Vehicle::getMaxCapacity(void) const {
    return maxCapacity;
}

/**
 * \brief Sets the new vehicle maximum capacity.
 * \param m: the new maximum capacity to set.
 */
void Vehicle::setMaxCapacity(uint m) {
    maxCapacity = m;
}

/**
 * \brief Getter for the vehicle's ID.
 * \return the vehicle ID.
 */
uint Vehicle::getVehicleId() const {
    return vehicleID;
}

/*!
 * \brief Setter for the vehicle's ID.
 * \param vehId: the new ID to set.
 */
void Vehicle::setVehicleId(uint vehId) {
    vehicleID = vehId;
}

/**
 * \brief Getter for the line's ID.
 * \return the line ID.
 */
uint Vehicle::getLineId() const {
    return lineID;
}

/**
 * \brief Setter for the line's ID.
 * \param linId: the new ID to set.
 */
void Vehicle::setLineId(uint linId) {
    lineID = linId;
}

/**
 * \brief Getter for the beginning time of travel.
 * \return the date at which the travel begins.
 */
tm Vehicle::getBeginTime() const {
    return beginTravel;
}

/**
 * \brief Setter for the beginning time of travel.
 * \param beginT: the new date to set.
 */
void Vehicle::setBeginTime(tm beginT) {
    beginTravel = beginT;
}

/**
 * \brief Getter for the ending time of travel.
 * \return the date at which the travel ends.
 */
tm Vehicle::getEndTime() const {
    return endTravel;
}

/**
 * \brief Setter for the ending time of travel.
 * \param endT: the new date to set.
 */
void Vehicle::setEndTime(tm endT) {
    endTravel = endT;
}

vector< Vehicle * > Vehicle::selectAllInMission(vector<Vehicle *>& v) {
    vector< Vehicle * > tmp;
    for(auto const& i: v) {
        if(i->mode == 1) { // Corresponds to vehicles in mission
            tmp.push_back(i);
            cout << "Vehicle " << i->vehicleID << " is considered in mission." << endl;
            cout << "Its mode is " << i->mode << endl;
        }
    }
    return tmp;
}

/**
 * \brief Gets and returns the vehicle mode.
 */
uint Vehicle::getVehicleMode() {
    return mode;
}

/**
 * Sets the new vehicle mode.
 * \param m The new mode to set.
 */
void Vehicle::setVehicleMode(uint m) {
    mode = m;
}

/**
 * \brief Gets and returns the boolean ruling if the vehicle is automatically driven.
 */
bool Vehicle::getIsHuman() {
    return isHuman;
}

/**
 * Sets a new state of automatic driving. If boolean is true,
 * the vehicle is humane-driven, and it's automatically driven
 * if boolean is false.
 * \param i The new boolean value to be applied.
 */
void Vehicle::setIsHuman(bool i) {
    isHuman = i;
}

uint Vehicle::getCamerasCount() {
    return camerasCount;
}

void Vehicle::setCamerasCount(uint count) {
    camerasCount = count;
}

Camera& Vehicle::getCameraAt(uint id) {
    return cameras[id];
}

void Vehicle::setCameraAt(uint id, Camera & cam) {
    cameras[id] = cam;
}

vector< Camera >& Vehicle::getCameras() {
    return cameras;
}