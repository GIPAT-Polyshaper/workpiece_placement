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
        cv::Rect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(50.0f).epsilon(0.01);
        Approx Y_target = Approx(100.0f).epsilon(0.01);
        REQUIRE(wa.x == X_target);
        REQUIRE(wa.y == Y_target);
        Approx W_target = Approx(600).epsilon(0.01);
        Approx H_target = Approx(500).epsilon(0.01);
        REQUIRE(wa.width == W_target);
        REQUIRE(wa.height == H_target);
    }

    SECTION("extracting working area from image not having frame"){
        Image img = ImageLoader(img_path + "prova2.png").getImage();
        cv::Rect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(0.0f).epsilon(0.01);
        Approx Y_target = Approx(0.0f).epsilon(0.01);
        REQUIRE(wa.x == X_target);
        REQUIRE(wa.y == Y_target);
        Approx W_target = Approx(600).epsilon(0.01);
        Approx H_target = Approx(500).epsilon(0.01);
        REQUIRE(wa.width == W_target);
        REQUIRE(wa.height == H_target);
    }

    SECTION("extracting working area from image having half frame"){
        Image img = ImageLoader(img_path + "workingArea300x400.png").getImage();
        cv::Rect wa = WorkingAreaExtractor().elaborate(img);
        Approx X_target = Approx(0.0f).epsilon(0.01);
        Approx Y_target = Approx(0.0f).epsilon(0.01);
        REQUIRE(wa.x == X_target);
        REQUIRE(wa.y == Y_target);
        Approx W_target = Approx(300).epsilon(0.01);
        Approx H_target = Approx(400).epsilon(0.01);
        REQUIRE(wa.width == W_target);
        REQUIRE(wa.height == H_target);
    }

}