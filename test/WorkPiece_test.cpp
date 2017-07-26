//
// Created by riccardo on 25/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/WorkPiece.h"

TEST_CASE("WorkPiece"){

    SECTION("Creating empty workpiece") {
        WorkPiece wp;
        REQUIRE(wp.getM_angle() == 0);
        REQUIRE(wp.getM_height() == 0);
        REQUIRE(wp.getM_point().x == 0);
        REQUIRE(wp.getM_point().y == 0);
        REQUIRE(wp.getM_width() == 0);

        SECTION("Setting workpiece members")
        {
            float f = 45.5;
            wp.setM_angle(f);
            wp.setM_height(50);
            wp.setM_point(150,160);
            wp.setM_width(60);
            REQUIRE(wp.getM_angle() == 45.5);
            REQUIRE(wp.getM_height() == 50);
            REQUIRE(wp.getM_point().x == 150);
            REQUIRE(wp.getM_point().y == 160);
            REQUIRE(wp.getM_width() == 60);
        }

    }

    SECTION("Creating working piece"){
        float f = 56.3;
        WorkPiece wp = WorkPiece(cv::Point(10, 20), f, 400, 500);
        REQUIRE(wp.getM_angle() == f);
        REQUIRE(wp.getM_height() == 500);
        REQUIRE(wp.getM_point().x == 10);
        REQUIRE(wp.getM_point().y == 20);
        REQUIRE(wp.getM_width() == 400);
    }

}