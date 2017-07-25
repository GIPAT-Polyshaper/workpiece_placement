//
// Created by riccardo on 19/07/17.
//
#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../wplib/Image.h"

TEST_CASE("WorkingArea") {

    SECTION("Empty_working_area") {
        Mat mat = Mat::ones(500, 500, CV_8UC1) * 255;//white matrix
        REQUIRE_THROWS_AS(new WorkingArea(mat), std::invalid_argument);
    }

    SECTION("Whole_working_area") {
        Mat mat = Mat::zeros(500, 500, CV_8UC1); //black matrix
        WorkingArea *wa = new WorkingArea(mat);
        REQUIRE(wa->workingAreaWidth() == 498);//498 internal area width
        REQUIRE(wa->workingAreaHeight() == 498);

    }

    SECTION("Working_area_from_image") {
        Image *img = new Image("workingArea300x400.png");// 400x300 black rect
        WorkingArea wa = img->getWorkingArea();
        const cv::Rect rect = wa.getRect();
        REQUIRE(rect.tl().x == 1);
        REQUIRE(rect.tl().y == 1);
        REQUIRE(rect.br().x == 300);
        REQUIRE(rect.br().y == 400);
    }

    SECTION("Corners")
    {
        Mat mat = Mat::zeros(500, 500, CV_8UC1);
        WorkingArea *wa = new WorkingArea(mat);
        SECTION("Top left corner")
        {
            REQUIRE(wa->getTopLeft().x == 1);
            REQUIRE(wa->getTopLeft().y == 1);
        }
        SECTION("Bottom right corner")
        {
            REQUIRE(wa->getBottomRight().x == 499);
            REQUIRE(wa->getBottomRight().y == 499);
        }
    }

}
