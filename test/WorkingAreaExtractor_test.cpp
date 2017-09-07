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
        Image img = ImageLoader(img_path + "prova.png").getImage();
        cv::RotatedRect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(350.0f).epsilon(0.01);
        Approx Y_target = Approx(350.0f).epsilon(0.01);
        REQUIRE(wa.center.x == X_target);
        REQUIRE(wa.center.y == Y_target);
        REQUIRE(wa.angle == -90.0f);
        Approx W_target = Approx(500).epsilon(0.01);
        Approx H_target = Approx(600).epsilon(0.01);
        REQUIRE(wa.size.width == W_target);
        REQUIRE(wa.size.height == H_target);
    }

    SECTION("extracting working area from image not having frame"){
        Image img = ImageLoader(img_path + "prova2.png").getImage();
        cv::RotatedRect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(300.0f).epsilon(0.01);
        Approx Y_target = Approx(250.0f).epsilon(0.01);
        REQUIRE(wa.center.x == X_target);
        REQUIRE(wa.center.y == Y_target);
        Approx W_target = Approx(500).epsilon(0.01);
        Approx H_target = Approx(600).epsilon(0.01);
        REQUIRE(wa.size.width == W_target);
        REQUIRE(wa.size.height == H_target);
    }

    SECTION("extracting working area from image having half frame"){
        Image img = ImageLoader(img_path + "workingArea300x400.png").getImage();
        cv::RotatedRect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(150.0f).epsilon(0.01);
        Approx Y_target = Approx(200.0f).epsilon(0.01);
        REQUIRE(wa.center.x == X_target);
        REQUIRE(wa.center.y == Y_target);
        Approx W_target = Approx(400).epsilon(0.01);
        Approx H_target = Approx(300).epsilon(0.01);
        REQUIRE(wa.size.width == W_target);
        REQUIRE(wa.size.height == H_target);
    }

}