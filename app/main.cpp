#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"
#include "../wplib/WorkPieceExtractor.h"


//TODO marker opencv e rettificazione d'immagine, http://docs.opencv.org/trunk/da/d6e/tutorial_py_geometric_transformations.html

int main() {

    Image img = ImageLoader("../../sample_imgs/IMG_2216.JPG").getM_image();
    img.showImg();
    //extracting working area
    Rect r = WorkingAreaExtractor(img).getM_workingArea();
    //cut original image
    Image imgCut = ImageCutter(img, r).getM_image();
    imgCut.showImg();
    cv::Mat matr = imgCut.getM_mat();

//    cv::Mat colmat;
//    cvtColor(matr, matr,COLOR_GRAY2BGR);
//    imshow("mat1", matr);
//    waitKey(0);

    //extracting workpiece
    WorkPiece wp = WorkPieceExtractor().workpiece(imgCut.getM_mat());
    //create a bounding rectangle of workpiece
    Rect r1 = cv::Rect(wp.getM_point().x, wp.getM_point().y-wp.getM_height(), wp.getM_width(),wp.getM_height());
    Image imgCutCut = ImageCutter(imgCut, r1).getM_image();
    imgCutCut.showImg();
    std::cout<< "x: " << wp.getM_point().x << std::endl;
    std::cout<< "y: " << wp.getM_point().y << std::endl;

    return 0;
}