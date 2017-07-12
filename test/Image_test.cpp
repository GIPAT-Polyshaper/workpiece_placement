//
// Created by riccardo on 10/07/17.
//

#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../wplib/Image.h"


TEST_CASE( "Image_test", "[compare]" ) {

    Image *img1 = new Image("IMG_2215.JPG");
    Image *img2 = new Image("IMG_2215.JPG");
    REQUIRE(img1->isEqualTo(img2));         //test: is an image  equal to itself?
    Image *img3 = new Image("IMG_2216.JPG");
    REQUIRE(!img1->isEqualTo(img3));        //test: are two different images  equal?

}



