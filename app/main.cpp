#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"


//TODO marker opencv e rettificazione d'immagine

int main() {

    Image img = ImageLoader("IMG_2215_shapes.png").getM_image();
    img.showImg();
    Rect r = WorkingAreaExtractor(img).getM_workingArea();

    Image imgCut = ImageCutter(img, r).getM_image();
    imgCut.showImg();
    return 0;
}