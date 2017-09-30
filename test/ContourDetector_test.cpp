//
// Created by riccardo on 27/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "test_config.h"
#include "../wplib/wp.h"


TEST_CASE("Detecting contours inside image"){

    SECTION("Detecting contours of black matrix")
    {
        cv::Mat bMat = Mat::zeros(400,500,CV_8UC1);
        std::vector<std::vector<cv::Point>> vec = wp::contourDetector(bMat, true);
        Approx X_target = Approx(500).epsilon(0.01);
        Approx Y_target = Approx(400).epsilon(0.01);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 0 );
        REQUIRE(vec[0][0].y == 0 );
        REQUIRE(vec[0][2].x == X_target );
        REQUIRE(vec[0][2].y == Y_target );
    }

    SECTION("Detecting contours of white matrix")
    {
        cv::Mat wMat = Mat::ones(400,500,CV_8UC1)*255;
        std::vector<std::vector<cv::Point>> vec = wp::contourDetector(wMat, false);
        Approx X_target = Approx(500).epsilon(0.01);
        Approx Y_target = Approx(400).epsilon(0.01);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 0 );
        REQUIRE(vec[0][0].y == 0 );
        REQUIRE(vec[0][2].x == X_target );
        REQUIRE(vec[0][2].y == Y_target );
    }

    SECTION("Detecting contours of external black areas"){

        Image img = ImageLoader(img_path + "prova.png").getImage();
        std::vector<std::vector<cv::Point>> vec = wp::contourDetector(img.getMat(), true);
        Approx X_target = Approx(650).epsilon(0.01);
        Approx Y_target = Approx(600).epsilon(0.01);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 50 );
        REQUIRE(vec[0][0].y == 100 );
        REQUIRE(vec[0][2].x == X_target );
        REQUIRE(vec[0][2].y == Y_target );
    }

    SECTION("Detecting contours of external white areas"){

        Image img = ImageLoader(img_path + "prova.png").getImage();
        std::vector<std::vector<cv::Point>> vec = wp::contourDetector(img.getMat(), false);
        Approx X_target = Approx(700).epsilon(0.01);
        Approx Y_target = Approx(1100).epsilon(0.01);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0][0].x == 0 );
        REQUIRE(vec[0][0].y == 0 );
        REQUIRE(vec[0][2].x == X_target );
        REQUIRE(vec[0][2].y == Y_target );
    }

}