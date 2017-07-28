#include <iostream>
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/ImageCutter.h"

int main() {

    Image img = ImageLoader("IMG_2216.JPG").getM_image();
    img.showImg();
    Rect r = WorkingAreaExtractor(img).getM_workingArea();

    Image imgCut = ImageCutter(img, r).getM_image();
    imgCut.showImg();
    return 0;
}