//
// Created by riccardo on 25/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include "../include/catch.hpp"
#include "../wplib/WorkPiece.h"

TEST_CASE("WorkPiece"){

    SECTION("Creating empty elaborate") {
        WorkPiece wp;
        REQUIRE(wp.getAngle() == 0);
        REQUIRE(wp.getShortSide() == 0);
        REQUIRE(wp.getCenterPoint().x == 0);
        REQUIRE(wp.getCenterPoint().y == 0);
        REQUIRE(wp.getLongSide() == 0);
        int i;
        for(i==0; i < 4; i++){
            REQUIRE(wp.getVertices()[0] == cv::Point(0,0));
        }


        SECTION("Setting elaborate members")
        {
            float f = 45.5;
            wp.setAngle(f);
            wp.setShortSide(50);
            wp.setCenterPoint(150, 160);
            wp.setLongSide(60);
            REQUIRE(wp.getAngle() == 45.5);
            REQUIRE(wp.getShortSide() == 50);
            REQUIRE(wp.getCenterPoint().x == 150);
            REQUIRE(wp.getCenterPoint().y == 160);
            REQUIRE(wp.getLongSide() == 60);
        }

    }

    SECTION("Worpiece from rotated rectangle")
    {
        cv::Mat m = cv::Mat::zeros(500,500, CV_8UC3);
        cv::RotatedRect rr(cv::Point2f(105.5, 210.6), cv::Size(100,50), float(36.3));
        WorkPiece wp = WorkPiece(rr);

        const cv::Point* vertices = wp.getVertices();

        Approx point0X = Approx(50).epsilon(0.01);
        Approx point0Y = Approx(201).epsilon(0.01);
        Approx point1X = Approx(80).epsilon(0.01);
        Approx point1Y = Approx(160).epsilon(0.01);
        Approx point2X = Approx(160).epsilon(0.01);
        Approx point2Y = Approx(220).epsilon(0.01);
        Approx point3X = Approx(130).epsilon(0.01);
        Approx point3Y = Approx(260).epsilon(0.01);

        REQUIRE(wp.getAngle() == float(126.3));
        CHECK(vertices[0].x == point0X);
        CHECK(vertices[0].y == point0Y);
        CHECK(vertices[1].x == point1X);
        CHECK(vertices[1].y == point1Y);
        CHECK(vertices[2].x == point2X);
        CHECK(vertices[2].y == point2Y);
        CHECK(vertices[3].x == point3X);
        CHECK(vertices[3].y == point3Y);
    }

//    SECTION("Creating working piece"){
//        float f = 56.3;
//        WorkPiece wp = WorkPiece(cv::Point(380, 350), f, 400, 500);
//        REQUIRE(wp.getAngle() == f);
//        REQUIRE(wp.getShortSide() == 400);
//        REQUIRE(wp.getCenterPoint().x == 380);
//        REQUIRE(wp.getCenterPoint().y == 350);
//        REQUIRE(wp.getLongSide() == 500);
//    }

}