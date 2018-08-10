/*!
 * \class Factory
 * \brief Handles all objects creation, i.e. Cameras, Coaches and Vehicles.
 *
 * This class implements the design pattern "Factory Method", and enables
 * the creation of any vehicle, even if its type is not known to the user.
 * All methods are static, so there is no need to create a Factory object
 * to use those methods.
 *
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 24, 2018
 */

#ifndef MOD_FACTORY_H
#define MOD_FACTORY_H

#include "Proto/transport/Bus.h"
#include "Trolleybus.h"
#include "Tramway.h"
#include "Tube.h"
#include "Proto/transport/Camera.h"
#include "Coach.h"
#include "Proto/utils/Tools.h"

class Factory {
public:

    static void                 createAllCameras(vector< Camera > &, vector< Camera >&);
    static vector< Coach >      createAllCoaches(vector< Camera > &);
    static vector< Vehicle* >   createAllVehicles(vector< Coach > &, vector< Camera> &, vector< Camera > &);
    static Vehicle*             create(const string &, uint, uint, tm, tm, uint,
                                       bool, uint, vector< Coach > &,
                                       vector< Camera> &, vector< Camera > & );
};

/**
 * Creates cameras from data file. One line equals one camera.
 * Each line is written considering the following pattern:
 * < coachID | cameraID | width | height >,
 * each field being separated by a blank space.
 * coachID identifies the coach in which the camera is,
 * and makes the connection between the 2 objects, helping
 * for the further creation of the coach.
 *
 * \return a map of Cameras, keyed with their associated Coach ID.
 */
inline void Factory::createAllCameras(vector< Camera >& camerasInCoaches, vector< Camera >& camerasNotInCoaches) {

    struct lineData {
        // priorID: = coachID if train or similar, = vehicleID if bus or trolleybus
        uint priorID = 0;
        uint cameraID = 0;
        uint width = 0;
        uint height = 0;
    };

    LOG(DEBUG, "/home/ubuntu/Stage-Marie/Proto/transport/camera_data.txt");
//    cameraData.open((string)getcwd(buff, FILENAME_MAX) + "/camera_data.txt");
//    char buff[FILENAME_MAX];

    ifstream cameraData;
    cameraData.open("/home/ubuntu/Stage-Marie/Proto/transport/camera_data.txt");

    if(cameraData) {
        LOG(DEBUG, "Opened camera file properly");

        lineData l;
        string lineToParse;

        while(getline(cameraData, lineToParse)) {
            // Acquire data
            stringstream lineStream(lineToParse);
            lineStream >> l.priorID >> l.cameraID >> l.width >> l.height;

            Camera c(l.priorID, l.cameraID, l.width, l.height);
            LOG(INFO, "Created Camera #" + std::to_string(l.cameraID));

            // Coaches are identified with a 2-digit ID, while vehicles are
            // identified with 4-digits IDs. Depending on the ID's length,
            // we determine whether the camera belongs to a singleton vehicle
            // or a coach-composed one.
            if(l.priorID >= 10) {
                // If belongs to a coach
                if(l.priorID < 1000) {
                    camerasInCoaches.push_back(c);
                // Else if belongs to a vehicle
                } else {
                    camerasNotInCoaches.push_back(c);
                }
            } else {
                LOG(ERROR, "Bad ID written, camera cannot be associated with a coach or a vehicle! ");
                return;
            }
        }
        // No need to file closing (RAII)

    } else {
        LOG(ERROR, "Cannot open file camera_data.txt! ");
        return;
    }
}

/**
 * Creates coaches from data file. One line equals one coach.
 * Each line is written considering the following pattern:
 * < trainID | coachID | camerasCount | maxCapacity >,
 * each field being separated by a blank space.
 * trainID identifies the train (or tramway, or tube) in which
 * the coach is, and makes the connection between the 2 objects,
 * helping for the further creation of the vehicle.
 * camerasCount indicates how many Cameras there is in the Coach.
 * \param allCameras    The map of Cameras that shall be associated with the Coaches
 * \return              A map of Coaches, keyed with their associated Train ID.
 */
inline vector< Coach > Factory::createAllCoaches(vector< Camera >& allCameras) {
    struct lineData  {
        uint trainID;
        uint coachID;
        uint camerasCount;
        uint maxCapacity;
    };

    vector< Coach > allCoaches;

    ifstream coachData;
    LOG(DEBUG, "/home/ubuntu/Stage-Marie/Proto/transport/coach_data.txt");

//    coachData.open(getCurrentWorkingDir() + "/coach_data.txt");
    coachData.open("/home/ubuntu/Stage-Marie/Proto/transport/coach_data.txt");

    if(coachData) {
        LOG(DEBUG, "Opened coach file properly");
        lineData l;
        string lineToParse;

        while(getline(coachData, lineToParse)) {
            stringstream lineStream(lineToParse);

            /**
             * Warning: No conversion from string to int is done below.
             * This is due to the nature of stringstream,
             * which converts automatically if it's possible.
             */
            lineStream >> l.trainID >> l.coachID >> l.camerasCount >> l.maxCapacity;

            vector< Camera > camerasInCoach;
//            map< uint, Camera >::iterator it;
            // Getting all cameras in the coach
            for(auto const& it : allCameras) {
//            for(it = allCameras.begin(); it != allCameras.end(); ++it) {
                if(it.getPriorID() == l.coachID) {
                    camerasInCoach.push_back(it);
                }
            }
            Coach c(l.coachID, l.maxCapacity, std::move(camerasInCoach), l.trainID);
            allCoaches.push_back(c);
            LOG(INFO, "Created Coach #" + std::to_string(c.getCoachID()) + ". Key value is: " + std::to_string(c.getVehicleID()));
        }
        // No need to file closing (RAII)
    }
    else {
        LOG(ERROR, "Cannot open file coach_data.txt !");
        return allCoaches;
    }
}

/**
 * Factory method for creating all vehicles.
 * Sweeps all possible vehicle types and creates the proper one.
 * \param vehicleName       e.g., "train" or "trolleybus" (lower case)
 * \param vehicleID         the vehicle ID
 * \param lineID            the line ID
 * \param beginTravel       the date and time at which the vehicle shall leave
 * \param endTravel         the date and time at which the vehicle shall arrive
 * \param maxCapacity       the vehicle maximum capacity
 * \param isHuman           is the vehicle humane-driven?
 * \param mode              the vehicle mode (i.e. 0- offline, 1- in mission or 2- waiting)
 * \param allCoaches        all the coaches created, to connect them to their respective vehicle
 * \return                  a pointer to the created Vehicle
 */
inline Vehicle* Factory::create(const string& vehicleName, uint vehicleID, uint lineID, tm beginTravel, tm endTravel,
                                uint maxCapacity, bool isHuman, uint mode, vector< Coach >& coaches,
                                vector< Camera>& camerasInCoaches, vector< Camera >& camerasNotInCoaches ) {
    if( vehicleName == "bus") {
        vector< Camera > cam;
        for(const auto& i : camerasNotInCoaches) {
            cam.push_back(i);
        }
        return new Bus(vehicleID, lineID, beginTravel, endTravel, maxCapacity, isHuman, mode, cam);

    } else if (vehicleName == "trolleybus") {
        vector< Camera > cam;
        for(const auto& i : camerasNotInCoaches) {
            cam.push_back(i);
        }
        return new Trolleybus(vehicleID, lineID, beginTravel, endTravel, maxCapacity, isHuman, mode, cam);

    } else if (vehicleName == "train") {
        vector< Camera > cam;
        for(const auto& i : camerasInCoaches) {
            cam.push_back(i);
        }
        return new Train(vehicleID, lineID, beginTravel, endTravel, maxCapacity, isHuman, mode, coaches, cam);

    } else if (vehicleName == "tramway") {
        vector< Camera > cam;
        for(const auto& i : camerasInCoaches) {
            cam.push_back(i);
        }
        return new Tramway(vehicleID, lineID, beginTravel, endTravel, maxCapacity, isHuman, mode, coaches, cam);

    } else if (vehicleName == "tube") {
        vector< Camera > cam;
        for(const auto& i : camerasInCoaches) {
            cam.push_back(i);
        }
        return new Tube(vehicleID, lineID, beginTravel, endTravel, maxCapacity, isHuman, mode, coaches, cam);
    }
    LOG(WARN, "Could not create vehicle #" + std::to_string(vehicleID) + ": something went wrong!");
    return nullptr;
}

/**
 * Creates vehicles from data line. One line equals one vehicle.
 * Each line is written considering the following pattern:
 * < vehicleType | vehicleID | lineID | beginDate | beginTime | endDate | endTime | maxCapacity | isHuman | mode >,
 * each field being separated by a blank space.
 * \param allCoaches        The map of coaches constituting the different vehicles.
 * \return                  A vector containing all created Vehicles.
 */
inline vector< Vehicle* > Factory::createAllVehicles(vector< Coach >& allCoaches, vector< Camera >& camerasInCoaches, vector< Camera >& camerasNotInCoaches) {

    /**
     * Structure declaring all parameters
     * needed to parse each file line and construct
     * a vehicle from this information.
     * CAUTION! For now, it only supports Bus and Trolleybus
     * object construction!
     */
    struct lineData {
        string      vehicleName;
        uint        vehicleID;
        uint        lineID;
        string      beginDate;
        string      beginTime;
        string      endDate;
        string      endTime;
        uint        maxCapacity;
        bool        isHuman;
        uint        mode;
    };

    // Initialize the vector to return
    std::vector< Vehicle* > allVehicles;

    ifstream vehicleData;
    // @TODO: Replace by relative path
    vehicleData.open("home/ubuntu/Stage-Marie/Proto/transport/vehicle_data.txt");

    if(vehicleData) {
        LOG(DEBUG, "Opened vehicle file properly");
        lineData l;
        string lineToParse;

        while(getline(vehicleData, lineToParse)) {

            stringstream lineStream(lineToParse);
            lineStream >> l.vehicleName >> l.vehicleID >> l.lineID >> l.beginDate >> l.beginTime >> l.endDate >> l.endTime >> l.maxCapacity >> l.isHuman >> l.mode;

            // Parsing the date and time
            tm beginTravel, endTravel;
            string dateDelimiter = "/";
            string timeDelimiter = "h";

            beginTravel.tm_mday = stoi(l.beginDate.substr(0, l.beginDate.find(dateDelimiter)));
            beginTravel.tm_mon = stoi(l.beginDate.substr(l.beginDate.find(dateDelimiter)+1, l.beginDate.length()));

            beginTravel.tm_hour = stoi(l.beginTime.substr(0, l.beginTime.find(timeDelimiter)));
            beginTravel.tm_min = stoi(l.beginTime.substr(l.beginTime.find(timeDelimiter)+1, l.beginTime.length()));

            endTravel.tm_mday = stoi(l.endDate.substr(0, l.endDate.find(dateDelimiter)));
            endTravel.tm_mon = stoi(l.endDate.substr(l.endDate.find(dateDelimiter)+1, l.endDate.length()));

            endTravel.tm_hour = stoi(l.endTime.substr(0, l.endTime.find(timeDelimiter)));
            endTravel.tm_min = stoi(l.endTime.substr(l.endTime.find(timeDelimiter)+1, l.endTime.length()));

            vector< Coach > coachesInTrain;

            // If the vehicle is a train or assimilated,
            // get all the coaches associated to it
            if(l.vehicleName == "train" || l.vehicleName == "tramway" || l.vehicleName == "tube") {
//                map< uint, Coach >::iterator it;
                for(auto const& it: allCoaches) {
//                for(it = allCoaches.begin(); it != allCoaches.end(); ++ it) {
                    if(it.getVehicleID() == l.vehicleID) {
                        coachesInTrain.push_back(it);
                    }
                }
            }
            // Create the vehicle given all the data previously extracted
            Vehicle* v = create(l.vehicleName, l.vehicleID, l.lineID, beginTravel, endTravel, l.maxCapacity, l.isHuman,
                    l.mode, coachesInTrain, camerasInCoaches, camerasNotInCoaches);
            allVehicles.push_back(v);
            LOG(INFO, "Created Vehicle #" + std::to_string(l.vehicleID) + " of type " + l.vehicleName);
        }
    } else {
        LOG(ERROR, "Cannot open file vehicle_data.txt!");
        LOG(ERROR, std::to_string(errno));
        // Return empty vector
        return allVehicles;
    }
    return allVehicles;
}

#endif //MOD_FACTORY_H
