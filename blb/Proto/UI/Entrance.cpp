//#include "Entrance.h"
//
//Entrance::Entrance(QWidget *parent) : QDialog(parent) {
//
//    ui.setupUi(this);
//
//    setAttribute(Qt::WA_DeleteOnClose);
//    for(int i = 0; i < ui.comboBox->count(); i++) {
//        ui.comboBox->removeItem(i);
//    }
//
//    map< uint, Camera > camerasInCoaches, camerasNotInCoaches;
//    map< uint, Coach > coaches;
//    vector< Vehicle* > vehicles;
//
//    Factory::createAllCameras(camerasInCoaches, camerasNotInCoaches);
//    coaches = Factory::createAllCoaches(camerasInCoaches);
//    vehicles = Factory::createAllVehicles(coaches, camerasInCoaches, camerasNotInCoaches);
//
//    vector<Vehicle* > testSelect = Vehicle::selectAllInMission(vehicles);
//
//    fillComboBoxList(testSelect);
//
////    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(createMain()));
//    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
//
//    // Makes the dialog modal: main window won't be usable until dialog is closed
//    exec();
//
//}
//
//using std::to_string;
//
//void Entrance::fillComboBoxList(vector< Vehicle* > v) {
//    for(auto const& i : v) {
//        string verbose = i->getVehicleName() + " - " + std::to_string(i->getVehicleId()) + " - Departure " + std::to_string(i->getBeginTime().tm_hour) + "h" + std::to_string(i->getBeginTime().tm_min)
//                + " - Arrival " + std::to_string(i->getEndTime().tm_hour) + "h" + to_string(i->getEndTime().tm_min) ;
//        ui.comboBox->addItem(QString::fromStdString(verbose));
//        cout << "Added an element to comboBox!" << endl;
//    }
//}
//
//void Entrance::closeWindow() {
//    close();
//}
