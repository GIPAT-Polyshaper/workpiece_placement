#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"
#include "../wplib/WorkPieceExtractor.h"
#include "../wplib/CameraCapture.h"
#include "../wplib/CameraCalibrator.h"
#include "../wplib/PixelsToMetric.h"
#include "../wplib/GcodeUpdater.h"
#include "../wplib/GcodePointUpdater.h"
#include "../wplib/WorkingAreaLoader.h"
#include "../wplib/WorkingAreaSaver.h"
#include "../wplib/ImageCorrector.h"
#include <opencv2/aruco.hpp>


//TODO controllare esistenza file di calibrazione


//use this main for camera calibration and working area search
//int main(){
//
//    int numBoards = 0;
//    int numCornersHor;
//    int numCornersVer;
//
//    std::cout<<("Enter number of corners along width: ");
//    std::cin>>numCornersHor;
//
//    std::cout<<("Enter number of corners along height: ");
//    std::cin>>numCornersVer;
//
//    std::cout<<("Enter number of boards: ");
//    std::cin>>numBoards;
//
//    CameraCalibrator cc( numCornersHor, numCornersVer, numBoards);
//    cc.elaborate(1);
//
//    std::cout<<"Press 's' to capture and start working area detection, 'Esc' to abort"<<std::endl;
//
//    cv::Mat mCapture = CameraCapture(1).capturing();
//    if(mCapture.empty())
//        return 0;
//
////    Image img = ImageLoader("../../sample_imgs/provaSenzaWorkpiece.png").getImage();
//
//    Image img("captured", mCapture);
//
//    img.show();
//
//    cv::Mat copyMat;
//    img.getMat().copyTo(copyMat);
//
////    extracting working area from copy
//    cv::Rect r = WorkingAreaExtractor().elaborate(Image("imgCopy", copyMat));
//
////    saving working area in a file
//    try {
//        WorkingAreaSaver().elaborate(r);
//    }catch (std::exception &ex) {
//        std::cout << "An error occurred: "
//                  << ex.what() << "!\n";
//    }
//
//    return 0;
//}


int main() {

    //Image capturing
    Image img = ImageLoader("../../sample_imgs/prova.png").getImage();

//    std::cout<<"Press 's' to capture, 'Esc' to abort"<<std::endl;
//
//    cv::Mat mCapture = CameraCapture(1).capturing();
//    if(mCapture.empty())
//        return 0;
//
//    Image img("captured", mCapture);
//    time_t timer;
//    time(&timer);
//    std::string name = "../../shots/shot" + std::to_string( timer) +".bmp";
//    imwrite(name , img.getMat());

//    //correcting camera distortion
//    try
//    {
//        img = ImageCorrector().elaborate(img);
//    }
//    catch (std::exception &ex) {
//        std::cerr << "An error occurred: "
//                  << ex.what() << "!\n";
//    }

    img.show();


    //loading working area from file
    cv::Rect re;
    try
    {
         re = WorkingAreaLoader().elaborate();
    }
    catch (std::exception &ex) {
        std::cerr << "An error occurred: "
                  << ex.what() << "!\n";
    }

    //cut original image
    Image imgCut = ImageCutter().elaborate(img, re);

    imgCut.show();

    //extracting workpiece
    WorkPiece wp;
    try
    {
        wp = WorkPieceExtractor().elaborate(imgCut.getMat());
    }
    catch (std::exception &ex)
    {
        std::cerr << "An error occurred: "
                  << ex.what() << "!\n";
    }

    //draw workpiece bounds
    cv::Mat m = imgCut.getMat();
    cvtColor(m,m,COLOR_GRAY2BGR);
    const Point *pts = wp.getVertices();
    for( int j = 0; j < 4; j++ )
        line( m, pts[j], pts[(j+1)%4], Scalar(0,0,255),2);
    namedWindow("elaborate", WINDOW_NORMAL);
    imshow("elaborate", m);
    waitKey(0);

    //print elaborate coordinates and dimensions
    std::cout<< "x: " << wp.getCenterPoint().x << std::endl;
    std::cout<< "y: " << wp.getCenterPoint().y << std::endl;
    std::cout<< "angle: " << wp.getAngle() << std::endl;
    std::cout<< "size: " << wp.getLongSide()<<"x"<< wp.getShortSide() << std::endl;

    cv::Point2f verticesMm[4];
    float xmm;
    float ymm;
    float sizemmX;
    float sizemmY;
    float workingAreaHeightMm = 0;
    try
    {
        //converting pixels in mm
        PixelsToMetric ptm(re.width);
        xmm = ptm.elaborate(wp.getVertices()[0].x);
        ymm = ptm.elaborate(wp.getVertices()[0].y);
        workingAreaHeightMm = ptm.elaborate(re.height);
        for(int i = 0; i < 4; i++)
        {
            verticesMm[i] = cv::Point2f(ptm.elaborate(wp.getVertices()[i].x), ptm.elaborate(wp.getVertices()[i].y));
        }
        sizemmX = ptm.elaborate(wp.getLongSide());
        sizemmY = ptm.elaborate(wp.getShortSide());
        std::cout<< "xmm: " << xmm << std::endl;
        std::cout<< "ymm: " << ymm << std::endl;
        std::cout<< "sizemm: " << sizemmX <<"x"<< sizemmY;

    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }


    std::ifstream gcode;
    auto output = std::ostringstream();

    gcode.open("../../sample_gcode/prova-003.gcode", std::ifstream::in );

//    if(gcode.is_open())
//        std::cout << "ok" << std::endl;
//    else
//        std::cout << "no" << std::endl;

    auto gcodeUpdater = GcodeUpdater(gcode, output);

    //important! respect the order (x,y)
    cv::Size gcodeSize(10,5);

    GcodePointUpdater gcpu(gcodeSize, verticesMm, wp.getAngle(), workingAreaHeightMm);

    // G01 Y-237
    // G92 Y0

    while (gcodeUpdater.hasNextPoint())
    {

        GcodeUpdater::Point p = gcodeUpdater.nextPoint();
        GcodeUpdater::Point newP = gcpu.elaborate(p, 0);
        gcodeUpdater.updatePoint(newP);

    }
    std::cout << output.str()<< std::endl;
    std::ofstream outFile("out.gcode",std::ofstream::out);
    outFile << output.str();
    outFile.close();
    gcode.close();
    return 0;
}
