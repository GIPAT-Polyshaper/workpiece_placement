#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"
#include "../wplib/WorkPieceExtractor.h"


//TODO marker opencv e rettificazione d'immagine

int main() {
    Image img = ImageLoader("IMG_2216.JPG").getM_image();
    img.showImg();
    Rect r = WorkingAreaExtractor(img).getM_workingArea();

    Image imgCut = ImageCutter(img, r).getM_image();
    imgCut.showImg();
//    WorkPiece wp = WorkPieceExtractor().workpiece(imgCut.getM_mat());
//    Rect r1 = cv::Rect(wp.getM_point().x, wp.getM_point().y, wp.getM_width(),wp.getM_height());
//    Image imgCutCut = ImageCutter(imgCut, r1).getM_image();
//    imgCutCut.showImg();
    return 0;
}