//
// Created by riccardo on 27/07/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "test_config.h"

TEST_CASE("Extracting working area"){

    SECTION("extracting working area from image having white frame"){
        Image img = ImageLoader(img_path+"prova.png").getM_image();
        cv::Rect wa = WorkingAreaExtractor(img).getM_workingArea();
        REQUIRE(wa.x == 50);
        REQUIRE(wa.y == 100);
        REQUIRE(wa.width == 600);
        REQUIRE(wa.height == 500);
    }

    SECTION("extracting working area from image not having frame"){
        Image img = ImageLoader(img_path+"prova2.png").getM_image();
        cv::Rect wa = WorkingAreaExtractor(img).getM_workingArea();
        REQUIRE(wa.x == 1);
        REQUIRE(wa.y == 1);
        REQUIRE(wa.width == 598);
        REQUIRE(wa.height == 498);
    }

    SECTION("extracting working area from image having half frame"){
        Image img = ImageLoader(img_path+"workingArea300x400.png").getM_image();
        cv::Rect wa = WorkingAreaExtractor(img).getM_workingArea();
        REQUIRE(wa.x == 1);
        REQUIRE(wa.y == 1);
        REQUIRE(wa.width == 299);
        REQUIRE(wa.height == 399);
    }

}