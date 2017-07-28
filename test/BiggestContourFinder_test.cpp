//
// Created by riccardo on 28/07/17.

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#endif

#include <cxcore.h>
#include "../include/catch.hpp"
#include "../wplib/BiggestContourFinder.h"

TEST_CASE("Finding biggest contour"){

    BiggestContourFinder bcf;
    std::vector<std::vector<cv::Point>> contours;

    SECTION("passing empty vector throw exception")
    {
        REQUIRE_THROWS_AS(bcf.biggestContour(contours), std::invalid_argument);
    }

    SECTION("vector with one contour return the contour"){

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Point> contour0 = {cv::Point(1,1), cv::Point(1,10), cv::Point(10,10), cv::Point(10,1)};
        contours.push_back(contour0);
        std::vector<cv::Point> bigCont = bcf.biggestContour(contours);
        REQUIRE(bigCont[0].x == 1);
        REQUIRE(bigCont[0].y == 1);
        REQUIRE(bigCont[2].x == 10);
        REQUIRE(bigCont[2].y == 10);

        // parent section fail prevent following sections from running

        SECTION("Adding a bigger contour"){
            std::vector<cv::Point> contour1 = {cv::Point(1,1), cv::Point(1,20), cv::Point(20,20), cv::Point(20,1)};
            contours.push_back(contour1);
            std::vector<cv::Point> bigCont = bcf.biggestContour(contours);
            REQUIRE(bigCont[0].x == 1);
            REQUIRE(bigCont[0].y == 1);
            REQUIRE(bigCont[2].x == 20);
            REQUIRE(bigCont[2].y == 20);

            SECTION("Adding a smaller contour"){
                std::vector<cv::Point> contour2 = {cv::Point(1,1), cv::Point(1,5), cv::Point(5,5), cv::Point(5,1)};
                contours.push_back(contour2);
                std::vector<cv::Point> bigCont = bcf.biggestContour(contours);
                REQUIRE(bigCont[0].x == 1);
                REQUIRE(bigCont[0].y == 1);
                REQUIRE(bigCont[2].x == 20);
                REQUIRE(bigCont[2].y == 20);

                SECTION("removing bigger contour"){
                    //erese second element
                    contours.erase(contours.begin() + 1);
                    std::vector<cv::Point> bigCont = bcf.biggestContour(contours);
                    REQUIRE(bigCont[0].x == 1);
                    REQUIRE(bigCont[0].y == 1);
                    REQUIRE(bigCont[2].x == 10);
                    REQUIRE(bigCont[2].y == 10);
                }
            }
        }
    }
}