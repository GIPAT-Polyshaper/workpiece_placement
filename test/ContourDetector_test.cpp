//
// Created by riccardo on 27/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/ContourDetector.h"

TEST_CASE("Detecting contours inside image"){

    SECTION("Detecting contours of external black areas"){

        Image img = ImageLoader("prova.png").getM_image();
        std::vector<std::vector<cv::Point>> vec = ContourDetector(img, true).getM_contours();
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 50 );
        REQUIRE(vec[0][0].y == 100 );
    }

    SECTION("Detecting contours of external white areas"){

        Image img = ImageLoader("prova.png").getM_image();
        std::vector<std::vector<cv::Point>> vec = ContourDetector(img, false).getM_contours();
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 1 );
        REQUIRE(vec[0][0].y == 1 );
    }

}