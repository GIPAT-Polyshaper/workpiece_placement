#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"
#include "../wplib/WorkPieceExtractor.h"
#include "../wplib/CameraCapture.h"
#include "../wplib/BiggestContourFinder.h"
#include "../wplib/ContourDetector.h"
#include "../wplib/CameraCalibrator.h"
#include "../wplib/PixelsToMetric.h"
#include "../wplib/GcodeUpdater.h"
#include "../wplib/GcodePointUpdater.h"
#include "../wplib/WorkingAreaLoader.h"
#include "../wplib/WorkingAreaSaver.h"
#include <opencv2/aruco.hpp>


//TODO controllare esistenza file di calibrazione


//use this main for camera calibration and working area search
//int main(){
//
//    int numBoards = 0;
//    int numCornersHor;
//    int numCornersVer;
//    printf("Enter number of corners along width: ");
//    scanf("%d", &numCornersHor);
//
//    printf("Enter number of corners along height: ");
//    scanf("%d", &numCornersVer);//todo change to cin
//
//    printf("Enter number of boards: ");
//    scanf("%d", &numBoards);
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
//    Image img("captured", mCapture);
//
//    img.show();
//
//    cv::Mat copyMat;
//    img.getMat().copyTo(copyMat);
//    //extracting working area from copy
//    cv::Rect r = WorkingAreaExtractor().elaborate(Image("imgCopy", copyMat));
//
//    //deleting
//    delete copyMat;
//
//    //saving working area in a file
//    WorkingAreaSaver().elaborate(r);
//
//    return 0;
//}


int main() {


    Image img = ImageLoader("../../sample_imgs/prova.png").getImage();

//    std::cout<<"Press 's' to capture, 'Esc' to abort"<<std::endl;
//
//    cv::Mat mCapture = CameraCapture(1).capturing();
//    if(mCapture.empty())
//        return 0;
//
//
//
//    Image img("captured", mCapture);
//    time_t timer;
//    time(&timer);
//    std::string name = "../../shots/shot" + std::to_string( timer) +".bmp";
//    imwrite(name , img.getMat());

//
//    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
//    std::vector<int> ids;
//    std::vector<std::vector<cv::Point2f> > corners;
//    cv::aruco::detectMarkers(copyMat, dictionary, corners, ids);
//
//    cv::aruco::drawDetectedMarkers(copyMat, corners, ids);
//    imshow("copm", copyMat);
//    waitKey(0);
//
//    if(corners.size() != 4)
//    {return 0;}
//
//    int index0;
//    int index2;
//    for(int i = 0; i < 4; i++){
//
//        if(ids[i] == 0)
//            index0 = i;
//        if(ids[i]==2)
//            index2 = i;
//    }
//    cv::Rect arucoRect(corners[index0][2], corners[index2][1]);

//    cv::Mat copyMat;
//    img.getMat().copyTo(copyMat);
//    cv::rectangle(copyMat, arucoRect, cv::Scalar(255,255,255), 2);
//
//    imshow("image",copyMat);
//    waitKey(0);

    //loading working area from file
    cv::Rect re = WorkingAreaLoader().elaborate();

//    //cut original image
    Image imgCut = ImageCutter().elaborate(img, re);

    imgCut.show();

    //extracting workpiece
    WorkPiece wp = WorkPieceExtractor().elaborate(imgCut.getMat());

//    //create a bounding rectangle of workpiece
//    cv::RotatedRect rr = cv::RotatedRect(wp.getCenterPoint(),cv::Size(wp.getLongSide(), wp.getShortSide()),
//                                         90 + wp.getAngle());

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
    float workingAreaHeightMm;
    try {
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

    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }


    std::ifstream gcode;
    auto output = std::ostringstream();

    gcode.open("../../sample_gcode/prova-003.gcode", std::ifstream::in );
//    auto input = std::istringstream("Dummy\nG00 X10\nMore dummyStuffs\nG01 Z10 Y67\nfinal dummy stuff");

//
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
    gcode.close();
    return 0;
}
