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
//    scanf("%d", &numCornersVer);
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


//    Image img = ImageLoader("../../sample_imgs/prova.png").getM_image();

    std::cout<<"Press 's' to capture, 'Esc' to abort"<<std::endl;

    cv::Mat mCapture = CameraCapture(1).capturing();
    if(mCapture.empty())
        return 0;

    Image img("captured", mCapture);
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
    cv::RotatedRect rr = cv::RotatedRect(wp.getM_point(),cv::Size(wp.getM_longSide(),wp.getM_shortSide()), 90 + wp.getM_angle());

    //draw workpiece bounds
    cv::Mat m = imgCut.getM_mat();
    cvtColor(m,m,COLOR_GRAY2BGR);
    Point2f pts[4];
    rr.points(pts);
    for( int j = 0; j < 4; j++ )
        line( m, pts[j], pts[(j+1)%4], Scalar(0,0,255), 2, 8 );
    namedWindow("workpiece", WINDOW_NORMAL);
    imshow("workpiece", m);
    waitKey(0);

    //print workpiece coordinates and dimensions
    std::cout<< "x: " << wp.getM_point().x << std::endl;
    std::cout<< "y: " << wp.getM_point().y << std::endl;
    std::cout<< "angle: " << wp.getM_angle() << std::endl;
    std::cout<< "size: " << wp.getM_longSide()<<"x"<<wp.getM_shortSide() << std::endl;

    try {
        //converting pixels in mm
        PixelsToMetric ptm(r.width);
        float xmm =ptm.MMConversion( wp.getM_point().x);
        float ymm =ptm.MMConversion( wp.getM_point().y);
        float sizemmX = ptm.MMConversion( wp.getM_longSide());
        float sizemmY = ptm.MMConversion( wp.getM_shortSide());
        std::cout<< "xmm: " << xmm << std::endl;
        std::cout<< "ymm: " << ymm << std::endl;
        std::cout<< "sizemm: " << sizemmX <<"x"<< sizemmY;

    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }


    std::ifstream gcode;
    auto output = std::ostringstream();

    gcode.open("../../sample_gcode/output.ngc", std::ifstream::in );

    if(gcode.is_open())
        std::cout << "ok" << std::endl;
    else
        std::cout << "no" << std::endl;

    auto gcodeUpdater = GcodeUpdater(gcode, output);

    while (gcodeUpdater.hasNextPoint()) {
        GcodeUpdater::Point p = gcodeUpdater.nextPoint();

        p[0] += 1;
        p[1] += 1;
        p[2] += 1;
        p[3] += 1;

        gcodeUpdater.updatePoint(p);
    }
    std::cout << output.str()<< std::endl;
    gcode.close();
    return 0;
}
