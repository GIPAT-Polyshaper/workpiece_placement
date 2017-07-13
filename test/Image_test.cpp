//
// Created by riccardo on 10/07/17.
//

#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../wplib/Image.h"


TEST_CASE( "Image_comparing_test", "[compare]" ) {

    Image *img1 = new Image("IMG_2215.JPG");
    Image *img2 = new Image("IMG_2215.JPG");
    // is an image  equal to itself?
    REQUIRE(img1->isEqualTo(img2));
    Image *img3 = new Image("IMG_2216.JPG");
    // are two different images  equal?
    REQUIRE(!img1->isEqualTo(img3));

}

TEST_CASE( "Image_cleaning_test", "[clean]" ) {

    Image *img16 = new Image("IMG_2216.JPG");
    Image cleanedImg16 = img16->clean();
    // manual cropped image
    Image *img16c = new Image("IMG_2216_cut.JPG");
    //  check if the image result of clean method is equal to a manual cropped image
    REQUIRE(cleanedImg16.isEqualTo(img16c));
    Image *img17 = new Image("IMG_2217.JPG");
    Image cleanedImg17 = img17->clean();
    Image *img17c = new Image("IMG_2217_cut.JPG");
    REQUIRE(cleanedImg17.isEqualTo(img17c));

}


