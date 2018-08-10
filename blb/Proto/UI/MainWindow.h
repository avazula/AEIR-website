/*!
 * \class Detection
 * \brief Defines behavior of the detection window.
 * \author Marie Brunet Carteaux | < marie.brunet@orange.com >
 * \date May 31, 2018
 */

#ifndef MOD_DETECTION_H
#define MOD_DETECTION_H


#include "../cmake-build-debug/ui_mainwindow.h"

#include <QtGui>
#include <QDialog>
#include "Entrance.h"
#include "Proto/transport/Vehicle.h"
#include "Proto/transport/Factory.h"

class MainWindow : public QMainWindow {
Q_OBJECT

signals:
    void newVehicleSelected(void);

private:
    Ui::MainWindow          ui;
    Vehicle*                vehicleDisplayed;
    vector< Camera >        camerasInCoaches, camerasNotInCoaches;
    vector < Vehicle* >     allVehicles;
    vector< Vehicle* >      inMission;
    QTimer*                 update;

//    QPixmap randomPixmap;
//    QImage* randomImage;
//    QGraphicsScene* randomScene;

public:
    explicit MainWindow(QWidget* parent = 0);
    void fillComboBoxList(vector< Vehicle* >);


private slots:
    void editWindowHeader(QString);
    void disableIfNotTrain(QString);
    void displayCameras(QString s);
    void updateTime(void);
    void affectVehicleDisplayed(QString);

};

#endif //MOD_DETECTION_H
