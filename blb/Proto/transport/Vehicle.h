/**
 * \class Vehicle
 * \brief Interface for all vehicles and subtypes. Describes the object Vehicle and all its associated methods.
 *
 * This class is the base class for implementing specialized vehicles
 * as trains and (trolley-)buses. This class is therefore polymorphic
 * and comprises pure virtual methods to be implemented in derived
 * classes (for instance, maximum capacity is not computed the same way
 * whether the vehicle is composed of coaches or is one single entity).
 *
 * \author Marie Brunet Carteaux | <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_VEHICLE_H
#define MOD_VEHICLE_H

#include <ctime>
#include "Proto/transport/Camera.h"
#include "Proto/transport/Coach.h"
#include <vector>

class Vehicle {

protected:
    uint                vehicleID;
    uint                lineID;
    tm                  beginTravel;
    tm                  endTravel;
    uint                maxCapacity;
    bool                isHuman;
    uint                mode;
    uint                camerasCount;
    vector< Camera >    cameras;

public:
    // Constructors
    Vehicle();
    Vehicle(uint, uint, tm&, tm&, uint, bool, uint, vector< Camera >&);
    // Destructor
    virtual ~Vehicle() {}

    virtual uint                getMaxCapacity(void) const;
    virtual void                setMaxCapacity(uint);
    virtual std::string         getVehicleName(void) const = 0;
    //virtual void              displayVehicle(void) const = 0;

    // Getters and setters
    uint        getVehicleId(void) const;
    void        setVehicleId(uint);
    uint        getLineId(void) const;
    void        setLineId(uint);
    tm          getBeginTime(void) const;
    void        setBeginTime(tm);
    tm          getEndTime(void) const;
    void        setEndTime(tm);
    uint        getVehicleMode();
    void        setVehicleMode(uint);
    bool        getIsHuman();
    void        setIsHuman(bool);
    uint        getCamerasCount(void);
    void        setCamerasCount(uint);
    Camera&     getCameraAt(uint);
    void        setCameraAt(uint, Camera &);
    vector< Camera >& getCameras(void);

    static vector< Vehicle* >   selectAllInMission(vector< Vehicle* >&);

};


#endif //MOD_VEHICLE_H
