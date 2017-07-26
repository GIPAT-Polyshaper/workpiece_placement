//
// Created by riccardo on 10/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"

TEST_CASE("Image"){

    SECTION("creating new image from not existing file throw invalid argument exception")
    {
        REQUIRE_THROWS_AS( new Image("ciao"), std::invalid_argument );
    }

    SECTION("opening image from file sistem and initializing Image object")
    {
        Image *img1 = new Image("IMG_2215.JPG");
        REQUIRE(img1->getImgMat().size);
    }

    SECTION("is an image  equal to itself?")
    {
        Image *img1 = new Image("IMG_2215.JPG");
        Image *img2 = new Image("IMG_2215.JPG");
        REQUIRE(img1->isEqualTo(*img2));

        SECTION("is an image equal to a different one?")
        {
            Image *img3 = new Image("IMG_2216.JPG");
            REQUIRE_FALSE(img1->isEqualTo(*img3));
        }
    }
    
    SECTION("working area extraction")
    {
        Image *img = new Image("workingArea300x400.png");
        Image waImg = img->extractWorkingArea();
        REQUIRE(waImg.getImgMat().rows == 399);
        REQUIRE(waImg.getImgMat().cols == 299);
    }
    
}

