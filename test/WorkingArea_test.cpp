//
// Created by riccardo on 19/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/WorkPiece.h"

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
        const cv::Rect rect = wa.getM_rect();
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

    SECTION("Creating working area having workpiece inside"){

        Mat mat = Mat::zeros(500, 600, CV_8UC1);
        WorkPiece wpParam = WorkPiece(cv::Point(100, 120), 0.0, 200, 300);
        WorkingArea wa = WorkingArea(mat, wpParam);
        REQUIRE(wa.workingAreaWidth() == 600);//498 internal area width
        REQUIRE(wa.workingAreaHeight() == 500);
        const WorkPiece wp = wa.getM_workPiece();
        REQUIRE(wp.getM_point().x == 100);
        REQUIRE(wp.getM_point().y == 120);
        REQUIRE(wp.getM_width() == 200);
        REQUIRE(wp.getM_height() == 300);
        REQUIRE(wp.getM_angle() == 0);

    }

}
