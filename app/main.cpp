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


//TODO controllare esistenza file di calibrazione

//
////use this main for camera calibration
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
//    cc.calibrate(1);
//
//    return 0;
//}


int main() {


    Image img = ImageLoader("../../sample_imgs/rect12.png").getM_image();

//    std::cout<<"Press 's' to capture, 'Esc' to abort"<<std::endl;
//
//    cv::Mat mCapture = CameraCapture(1).capturing();
//    if(mCapture.empty())
//        return 0;
//
//    Image img("captured", mCapture);
    img.showImg();


//    //undistorting image
//    FileStorage fs;
//    fs.open("calibrationParams.xml", FileStorage::READ);
//
//    if(!fs.isOpened())
//        //TODO throw exeption?
//        ;
//    Mat intrinsic, distCoeffs;
//
//    fs["distortion_coefficients"] >> distCoeffs;
//    fs["intrinsic_matrix"] >> intrinsic;
//    (distCoeffs.empty() || intrinsic.empty() ? //TODO throw exeption?
//      std::cout<<"ciao": std::cout << " pippo");
//
//    Mat undistortMat;
//    undistort(imgDist.getM_mat(), undistortMat, intrinsic, distCoeffs);
//
//    Image img("img",undistortMat);


    //extracting working area
    Rect r = WorkingAreaExtractor(img).getM_workingArea();

    //cut original image
    Image imgCut = ImageCutter(img, r).getM_image();

    imgCut.showImg();

    //extracting workpiece
    WorkPiece wp = WorkPieceExtractor().workpiece(imgCut.getM_mat());

    //create a bounding rectangle of workpiece
    cv::RotatedRect rr = cv::RotatedRect(wp.getCenterPoint(),cv::Size(wp.getLongSide(), wp.getShortSide()), 90 +
            wp.getAngle());

    //draw workpiece bounds
    cv::Mat m = imgCut.getM_mat();
    cvtColor(m,m,COLOR_GRAY2BGR);
    const Point *pts = wp.getVertices();
//    rr.points(pts);
    for( int j = 0; j < 4; j++ )
        line( m, pts[j], pts[(j+1)%4], Scalar(0,0,255), 2, 8 );
    namedWindow("workpiece", WINDOW_NORMAL);
    imshow("workpiece", m);
    waitKey(0);


    //print workpiece coordinates and dimensions
    std::cout<< "x: " << wp.getCenterPoint().x << std::endl;
    std::cout<< "y: " << wp.getCenterPoint().y << std::endl;
    std::cout<< "angle: " << wp.getAngle() << std::endl;
    std::cout<< "size: " << wp.getLongSide()<<"x"<< wp.getShortSide() << std::endl;

    cv::Point2f verticesMm[4];
    float xmm;
    float ymm;
    float sizemmX;
    float sizemmY;
    float workingAreaHeight;
    try {
        //converting pixels in mm
        PixelsToMetric ptm(r.width);
        xmm = ptm.mMConversion(wp.getCenterPoint().x);
        ymm = ptm.mMConversion(wp.getCenterPoint().y);
        workingAreaHeight = ptm.mMConversion(r.height);
        for(int i = 0; i < 4; i++)
        {
            verticesMm[i] = cv::Point2f(ptm.mMConversion(wp.getVertices()[i].x), ptm.mMConversion(wp.getVertices()[i].y));
        }
        sizemmX = ptm.mMConversion(wp.getLongSide());
        sizemmY = ptm.mMConversion(wp.getShortSide());
        std::cout<< "xmm: " << xmm << std::endl;
        std::cout<< "ymm: " << ymm << std::endl;
        std::cout<< "sizemm: " << sizemmX <<"x"<< sizemmY;

    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }


//    std::ifstream gcode;
    auto output = std::ostringstream();

//    gcode.open("../../sample_gcode/output.ngc", std::ifstream::in );
    auto input = std::istringstream("Dummy\nG00 X10\nMore dummyStuffs\nG01 Z10 Y67\nfinal dummy stuff");

//
//    if(gcode.is_open())
//        std::cout << "ok" << std::endl;
//    else
//        std::cout << "no" << std::endl;

    auto gcodeUpdater = GcodeUpdater(input, output);

    //important! respect the order (x,y)
    cv::Size gcodeSize(100,150);

    GcodePointUpdater gcpu(gcodeSize, verticesMm, wp.getAngle(), workingAreaHeight);

    while (gcodeUpdater.hasNextPoint()) {
        GcodeUpdater::Point p = gcodeUpdater.nextPoint();


        GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
//        p[0] += 1;
//        p[1] += 1;
//        p[2] += 1;
//        p[3] += 1;

        p;
        gcodeUpdater.updatePoint(newP);
    }
    std::cout << output.str()<< std::endl;
//    gcode.close();
    return 0;
}
