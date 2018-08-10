#include "MainWindow.h"
#include <cstdlib>
#include <sstream>
#include <exception>
#include <pthread.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using std::to_string;
using namespace cv;

/**
 * \brief Inits the main window.
 * \param parent The parent widget
 */
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // DEBUG
    cout << "Creating a new MainWindow object!" << endl;

    ui.setupUi(this);

    // Display a generic message until a vehicle is selected by user
    ui.label_trainID->setText("No vehicle selected yet");
    ui.label_trainID->setFont(QFont("Ubuntu", 24, QFont::Bold));
    ui.label_lineID->clear();
    ui.label_isHumaneDriven->clear();

//    map< uint, Camera > cameras;
    vector< Coach > coaches;

    Factory::createAllCameras(camerasInCoaches, camerasNotInCoaches);
    coaches = Factory::createAllCoaches(camerasInCoaches);
    allVehicles = Factory::createAllVehicles(coaches, camerasInCoaches, camerasNotInCoaches);

    inMission = Vehicle::selectAllInMission(allVehicles);

    fillComboBoxList(inMission);

    // Wipes out the label about objects being detected in whatever coach for initialization
    ui.label_luggageDetected->clear();

    ui.dateTimeEdit->setDate(QDate::currentDate());
    ui.dateTimeEdit->setTime(QTime::currentTime());

    // Create a timer that is triggered every second to refresh the GUI clock
    update = new QTimer;
    connect(update, SIGNAL(timeout()), this, SLOT(updateTime()));
    update->start(1000);

    connect(ui.comboBox_chooseAnotherVehicle, SIGNAL(activated(QString)), this, SLOT(editWindowHeader(QString)));
    connect(ui.comboBox_chooseAnotherVehicle, SIGNAL(activated(QString)), this, SLOT(disableIfNotTrain(QString)));
//    connect(ui.comboBox, SIGNAL(activated(QString)), this, SLOT(affectVehicleDisplayed(QString)));

//    connect(this, SIGNAL(newVehicleSelected()), this, SLOT(displayCameras()));
    connect(ui.comboBox_chooseAnotherVehicle, SIGNAL(activated(QString)), this, SLOT(displayCameras(QString)));
}

/**
 * \brief Update the time every time the timer is triggered
 */
void MainWindow::updateTime() {
    ui.dateTimeEdit->setTime(QTime::currentTime());
}

/**
 * \brief Creates all list entries from the vehicles currently in mission.
 *
 * This function takes all vehicles that are currently in mission and creates a list entry
 * for each of them according to the following syntax:
 *
 * < vehicleType vehicleID - Line lineID - Dep. HHhmm - Arr. HHhmm >
 *
 *
 * \param v A vector of all vehicles in mission.
 */
void MainWindow::fillComboBoxList(vector< Vehicle* > v) {
    for(auto const& i : v) {
        string verbose = i->getVehicleName() + " " + to_string(i->getVehicleId()) +
                         " - Line " + to_string(i->getLineId()) +
                         " - Dep. " + to_string(i->getBeginTime().tm_hour) + "h" + to_string(i->getBeginTime().tm_min)
                         + " - Arr. " + to_string(i->getEndTime().tm_hour) + "h" + to_string(i->getEndTime().tm_min) ;
        ui.comboBox_chooseAnotherVehicle->addItem(QString::fromStdString(verbose));
    }
}

/**
 * \brief Edit the basic info every time a new vehicle is selected.
 *
 * This function refreshes the vehicle name, ID, the line ID,
 * and indicates whether it is humanly driven or not.
 *
 * \param s A QString that is actually what is displayed by the combo box containing
 * all vehicles in mission. It is parsed to get the vehicle and line information needed.
 */
void MainWindow::editWindowHeader(QString s) {

    stringstream lineStream(s.toStdString());
    string vehicleName, vehicleID, junk, lineID;
    /** Structure of items in the list is like:
     *  vehicleName vehicleID - Line lineID
     *  Consequently, when parsing, there are 2
     *  words we do not want to consider: hyphen and 'Line'.
     *  These go in the 'junk' variable.
     */
    lineStream >> vehicleName >> vehicleID >> junk >> junk >> lineID;

    /// Get all information about the vehicle by retrieving it thanks to its ID and its line ID.
    /// This will be helpful later, for example to determine whether the vehicle is humanly driven,
    /// because this is no information displayed in the combo box.
    Vehicle* v;

    for(auto const& i : inMission)  {
        if(i->getVehicleId() == stoi(vehicleID) && i->getLineId() == stoi(lineID)) {
            v = i;
        }
    }

    /// Display the vehicle name & ID s.a.: Train #2241
    QString title = QString::fromStdString(v->getVehicleName() + " #" + to_string(v->getVehicleId()));
    ui.label_trainID->setText(title);
    ui.label_trainID->setFont(QFont("Ubuntu", 24, QFont::Bold));

    /// Display the line ID s.a.: Line #12
    QString line = QString::fromStdString("Line #" + to_string(v->getLineId()));
    ui.label_lineID->setText(line);

    QString autoDriven;
    if(v->getIsHuman()) {
        autoDriven = "This vehicle is humanly driven.";
    } else {
        autoDriven = "This vehicle is automatically driven.";
    }
    ui.label_isHumaneDriven->setText(autoDriven);

    emit newVehicleSelected();
}


/**
 * \brief Disable other tabs if the vehicle is not a train.
 *
 * If the vehicle selected is either a bus or trolleybus, it is not composed
 * of coaches, and therefore needs only one tab to display all cameras. This function
 * disables all other tabs when it detects that the selected vehicle is a (trolley-)bus.
 *
 * \param s A QString that is actually what is displayed by the combo box containing
 * all vehicles in mission. It is parsed to get the vehicle type and react accordingly.
 */
void MainWindow::disableIfNotTrain(QString s) {
    stringstream lineStream(s.toStdString());
    string vehicleName;
    lineStream >> vehicleName;

    if(vehicleName == "Bus" || vehicleName == "Trolleybus") {
        ui.tabWidget->setTabEnabled(1, false);
        ui.tabWidget->setTabEnabled(2, false);
        ui.tabWidget->setTabEnabled(3, false);
    } else if(vehicleName == "Train" || vehicleName == "Tramway" || vehicleName == "Tube") {
        ui.tabWidget->setTabEnabled(1, true);
        ui.tabWidget->setTabEnabled(2, true);
        ui.tabWidget->setTabEnabled(3, true);
    }
}

/**
 * \brief display all cameras present in the vehicle.
 *
 * Those images are stored in the 'data' folder and are named after their respective
 * camera ID.
 * This method is not finished yet and its behavior still needs to be described.
 * PLEASE REMEMBER: One nice functionality would be to maximize the image when clicked.
 */

using namespace cv;

void MainWindow::displayCameras(QString s) {
    stringstream lineStream(s.toStdString());
    string vehicleName, junk;
    uint vehicleID, lineID;

    lineStream >> vehicleName >> vehicleID >> junk >> junk >> lineID;
    Vehicle* v = nullptr;
    // We consider PK on vehicles can be the duet of vehicle ID and line ID
    // So if there's a vehicle with the same ID and line ID, we know it's our match
    for(const auto& i : inMission) {
        if(i->getVehicleId() == vehicleID) {
            if(i->getLineId() == lineID) {
                v = i;
            }
        }
    }
    // If none match found
    if(v == nullptr) {
        cerr << "Error while trying to display cameras: none vehicle found!" << endl;
        return;
    }

    uint camerasCount = v->getCamerasCount();
//    vector< Mat* > vehicleSnapshots;
    map< uint, Mat* > vehicleSnapshots;
    for(const auto& i : v->getCameras()) {
        vehicleSnapshots.insert(pair< uint, Mat* >(i.getCameraID(), new Mat));
    }

    for(auto&& [first,second] : vehicleSnapshots) {
        cout << "Je parcours ma map!" << endl;
        cout << first << endl;
    }




}

void MainWindow::affectVehicleDisplayed(QString s) {
//
//    stringstream lineStream(s.toStdString());
//    string vehicleName, vehicleID, junk, lineID;
//
//    lineStream >> vehicleName >> vehicleID >> junk >> junk >> lineID;
//    for(const auto& i : inMission) {
//        if(stoi(vehicleID) == i->getVehicleId() && stoi(lineID) == i->getLineId()) {
//            vehicleDisplayed = i;
//        }
//    }
//    // DEBUG
//    cout << "Vehicle displayed: " << vehicleDisplayed->getVehicleId() << " from line " << vehicleDisplayed->getLineId() << endl;
}