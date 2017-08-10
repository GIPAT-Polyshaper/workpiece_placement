#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"
#include "../wplib/WorkPieceExtractor.h"
#include "../wplib/CameraCapture.h"


//TODO marker opencv e rettificazione d'immagine, http://docs.opencv.org/trunk/da/d6e/tutorial_py_geometric_transformations.html


int main() {

//    Image img = ImageLoader("../../sample_imgs/IMG_2218.JPG").getM_image();

    std::cout<<"Press 's' to capture, 'Esc' to abort"<<std::endl;

    cv::Mat mCapture = CameraCapture(0).capturing();
    if(mCapture.empty())
        return 0;

    Image img("captured", mCapture);
    img.showImg();

    //extracting working area
    Rect r = WorkingAreaExtractor(img).getM_workingArea();

    //cut original image
    Image imgCut = ImageCutter(img, r).getM_image();

    imgCut.showImg();
    cv::Mat matr = imgCut.getM_mat();

    //extracting workpiece
    WorkPiece wp = WorkPieceExtractor().workpiece(imgCut.getM_mat());

    //create a bounding rectangle of workpiece
    cv::RotatedRect rr = cv::RotatedRect(wp.getM_point(),cv::Size(wp.getM_longSide(),wp.getM_shortSide()), 90 + wp.getM_angle());

    cv::Mat m = imgCut.getM_mat();
    cvtColor(m,m,COLOR_GRAY2BGR);
    Point2f pts[4];
    rr.points(pts);
    for( int j = 0; j < 4; j++ )
        line( m, pts[j], pts[(j+1)%4], Scalar(0,0,255), 2, 8 );
    namedWindow("workpiece", WINDOW_NORMAL);
    imshow("workpiece", m);
    waitKey(0);

    std::cout<< "x: " << wp.getM_point().x << std::endl;
    std::cout<< "y: " << wp.getM_point().y << std::endl;
    std::cout<< "angle: " << wp.getM_angle() << std::endl;
    std::cout<< "size: " << wp.getM_longSide()<<"x"<<wp.getM_shortSide();

    return 0;
}

