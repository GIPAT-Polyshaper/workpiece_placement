//
// Created by riccardo on 03/09/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include <opencv2/core/types.hpp>
#include "../include/catch.hpp"
#include "../wplib/WorkPiece.h"
#include "../wplib/GcodeUpdater.h"
#include "../wplib/GcodePointUpdater.h"

TEST_CASE("Updating a gcode point")
{
    SECTION("worpiece angle > 90, gcode x-side < y-side")
    {
        cv::Size gcodeSize = cv::Size(100,150);
        float worpieceAngle = 135;cv::RotatedRect wp(cv::Point(150, 200), cv::Size(150,100), 180 - worpieceAngle);
        cv::Point2f vertices[4];
        wp.points(vertices);
        auto gcpu = GcodePointUpdater(gcodeSize, vertices, worpieceAngle, 400);

        SECTION("Origin point")
        {
            auto o = GcodeUpdater::Point{0, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(o, 80);
            Approx x_Target = Approx(132).epsilon(0.01);
            Approx y_Target = Approx(288).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 155.5);
        }

        SECTION("Bottom right corner")
        {
            auto p = GcodeUpdater::Point{100, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(61).epsilon(0.01);
            Approx y_Target = Approx(217).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 155.5);
        }

        SECTION("Top right corner")
        {
            auto p = GcodeUpdater::Point{100, 150, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(167).epsilon(0.01);
            Approx y_Target = Approx(111).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 155.5);
        }

        SECTION("Point inside bound")
        {
            auto p = GcodeUpdater::Point{10, 20, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(140).epsilon(0.01);
            Approx y_Target = Approx(267).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 155.5);
        }

    }

    SECTION("worpiece angle > 90, gcode x-side > y-side")
    {
        cv::Size gcodeSize = cv::Size(150,100);
        float worpieceAngle = 135;
        cv::RotatedRect wp(cv::Point(150, 200), cv::Size(150,100), 180 - worpieceAngle);
        cv::Point2f vertices[4];
        wp.points(vertices);
        auto gcpu = GcodePointUpdater(gcodeSize, vertices, worpieceAngle, 400);

        SECTION("Origin point")
        {
            auto o = GcodeUpdater::Point{0, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(o, 80);
            Approx x_Target = Approx(61).epsilon(0.01);
            Approx y_Target = Approx(217).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Bottom right corner")
        {
            auto p = GcodeUpdater::Point{150, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(167).epsilon(0.01);
            Approx y_Target = Approx(111).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Top right corner")
        {
            auto p = GcodeUpdater::Point{150, 100, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(238).epsilon(0.01);
            Approx y_Target = Approx(182).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Point inside bound")
        {
            auto p = GcodeUpdater::Point{10, 20, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(83).epsilon(0.01);
            Approx y_Target = Approx(225).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

    }

    SECTION("worpiece angle < 90, gcode x-side < y-side")
    {
        cv::Size gcodeSize = cv::Size(100,150);
        float worpieceAngle = 45;
        cv::RotatedRect wp(cv::Point(150, 200), cv::Size(150,100), -worpieceAngle);
        cv::Point2f vertices[4];
        wp.points(vertices);
        auto gcpu = GcodePointUpdater(gcodeSize, vertices, 45, 400);

        SECTION("Origin point")
        {
            auto o = GcodeUpdater::Point{0, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(o, 80);
            Approx x_Target = Approx(61).epsilon(0.01);
            Approx y_Target = Approx(182).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Bottom right corner")
        {
            auto p = GcodeUpdater::Point{100, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(132).epsilon(0.01);
            Approx y_Target = Approx(111).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Top right corner")
        {
            auto p = GcodeUpdater::Point{100, 150, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(238).epsilon(0.01);
            Approx y_Target = Approx(217).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

        SECTION("Point inside bound")
        {
            auto p = GcodeUpdater::Point{10, 20, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(82).epsilon(0.01);
            Approx y_Target = Approx(190).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == 65.5);
        }

    }

    SECTION("worpiece angle < 90, gcode x-side > y-side")
    {
        cv::Size gcodeSize = cv::Size(150,100);
        float worpieceAngle = 45;
        cv::RotatedRect wp(cv::Point(150, 200), cv::Size(150,100), - worpieceAngle);
        cv::Point2f vertices[4];
        wp.points(vertices);
        auto gcpu = GcodePointUpdater(gcodeSize, vertices, worpieceAngle, 400);

        int x;
        SECTION("Origin point")
        {
            auto o = GcodeUpdater::Point{0, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(o, 80);
            Approx x_Target = Approx(132).epsilon(0.01);
            Approx y_Target = Approx(111).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == -24.5);
        }

        SECTION("Bottom right corner")
        {
            auto p = GcodeUpdater::Point{150, 0, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(238).epsilon(0.01);
            Approx y_Target = Approx(217).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == -24.5);
        }

        SECTION("Top right corner")
        {
            auto p = GcodeUpdater::Point{150, 100, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(167).epsilon(0.01);
            Approx y_Target = Approx(288).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == -24.5);
        }

        SECTION("Point inside bound")
        {
            auto p = GcodeUpdater::Point{10, 20, 10, 20.5};
            GcodeUpdater::Point newP = gcpu.elaborate(p, 80);
            Approx x_Target = Approx(125).epsilon(0.01);
            Approx y_Target = Approx(133).epsilon(0.01);
            CHECK( newP[0] == x_Target);
            CHECK( newP[1] == y_Target);
            CHECK( newP[2] == float(90));
            CHECK( newP[3] == -24.5);
        }

    }

}