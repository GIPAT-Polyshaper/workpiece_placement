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

    SECTION("Detecting contours of black matrix")
    {
        cv::Mat bMat = Mat::zeros(400,500,CV_8UC1);
        std::vector<std::vector<cv::Point>> vec = ContourDetector().contours(bMat, true);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 1 );
        REQUIRE(vec[0][0].y == 1 );
        REQUIRE(vec[0][2].x == 498 );
        REQUIRE(vec[0][2].y == 398 );
    }

    SECTION("Detecting contours of white matrix")
    {
        cv::Mat wMat = Mat::ones(400,500,CV_8UC1)*255;
        std::vector<std::vector<cv::Point>> vec = ContourDetector().contours(wMat, false);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 1 );
        REQUIRE(vec[0][0].y == 1 );
        REQUIRE(vec[0][2].x == 498 );
        REQUIRE(vec[0][2].y == 398 );
    }

    SECTION("Detecting contours of external black areas"){

        Image img = ImageLoader("prova.png").getM_image();
        std::vector<std::vector<cv::Point>> vec = ContourDetector().contours(img.getM_mat(), true);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 50 );
        REQUIRE(vec[0][0].y == 100 );
        REQUIRE(vec[0][2].x == 649 );
        REQUIRE(vec[0][2].y == 599 );
    }

    SECTION("Detecting contours of external white areas"){

        Image img = ImageLoader("prova.png").getM_image();
        std::vector<std::vector<cv::Point>> vec = ContourDetector().contours(img.getM_mat(), false);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 1 );
        REQUIRE(vec[0][0].y == 1 );
        REQUIRE(vec[0][2].x == 698 );
        REQUIRE(vec[0][2].y == 1098 );
    }

}