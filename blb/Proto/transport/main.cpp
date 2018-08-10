#include <iostream>

#include "Proto/transport/Bus.h"
#include "Proto/transport/Coach.h"
#include "Proto/transport/Camera.h"
#include "Proto/transport/Factory.h"
#include "Proto/transport/Trolleybus.h"
#include "Proto/transport/Tube.h"
#include "Proto/transport/Tramway.h"
#include "Proto/transport/Vehicle.h"
// OpenCV includes
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// Qt includes
#include <QApplication>
#include <QDebug>
#include "UI/MainWindow.h"
#include "UI/Entrance.h"

#include "utils/Logger.h"

using namespace cv;

int main(int argc, char** argv) {

//    // OPENCV TEST BABY!
//    cv::Mat image;
//    image = cv::imread("/home/avazula/Downloads/random.png");
//    namedWindow("Display window", WINDOW_AUTOSIZE);
//    imshow("Display window", image);

//    waitKey(0);

    QApplication app(argc, argv);

//    Entrance ui;
//    ui.show();

    MainWindow ui2;
    ui2.showMaximized();

    return app.exec();
//    return 0;
}