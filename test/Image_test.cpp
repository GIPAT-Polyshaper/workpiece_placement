//
// Created by riccardo on 10/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"

TEST_CASE("Image creation"){

    SECTION("creating image from zeros matrix"){
        cv::Mat zMat = Mat::zeros(400,400,CV_8UC1);
        Image zImg = Image(zMat);
        cv::Mat dst;
        cv::bitwise_xor(zImg.getM_mat(), zMat, dst);
        REQUIRE_FALSE(cv::countNonZero(dst));
    }

    SECTION("creating image from ones matrix"){
        cv::Mat oMat = Mat::ones(400,400,CV_8UC1);
        Image oImg = Image(oMat);
        cv::Mat dst;
        cv::bitwise_xor(oImg.getM_mat(), oMat, dst);
        REQUIRE_FALSE(cv::countNonZero(dst));
    }

}

//
//TEST_CASE("Image"){
//
//
//    SECTION("opening image from file sistem and initializing Image object")
//    {
//        Image *img1 = new Image("IMG_2215.JPG");
//        REQUIRE(img1->getImgMat().size);
//    }
//
//    SECTION("is an image  equal to itself?")
//    {
//        Image *img1 = new Image("IMG_2215.JPG");
//        Image *img2 = new Image("IMG_2215.JPG");
//        REQUIRE(img1->isEqualTo(*img2));
//
//        SECTION("is an image equal to a different one?")
//        {
//            Image *img3 = new Image("IMG_2216.JPG");
//            REQUIRE_FALSE(img1->isEqualTo(*img3));
//        }
//    }
//
//    SECTION("working area extraction")
//    {
//        Image *img = new Image("workingArea300x400.png");
//        Image waImg = img->extractWorkingArea();
//        REQUIRE(waImg.getImgMat().rows == 399);
//        REQUIRE(waImg.getImgMat().cols == 299);
//    }
//
//}
//
