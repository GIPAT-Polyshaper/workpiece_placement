//
// Created by riccardo on 10/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "./test_config.h"

TEST_CASE("Image creation"){

    SECTION("creating image from zeros matrix"){
        cv::Mat zMat = Mat::zeros(400,400,CV_8UC1);
        Image zImg = Image(zMat);
        cv::Mat dst;
        cv::bitwise_xor(zImg.getMat(), zMat, dst);
        REQUIRE_FALSE(cv::countNonZero(dst));
    }

    SECTION("creating image from ones matrix"){
        cv::Mat oMat = Mat::ones(400,400,CV_8UC1);
        Image oImg = Image(oMat);
        cv::Mat dst;
        cv::bitwise_xor(oImg.getMat(), oMat, dst);
        REQUIRE_FALSE(cv::countNonZero(dst));
    }

}

TEST_CASE("Image comparison"){

    Image img1 = ImageLoader(img_path + "IMG_2215.JPG").getImage();
    
    SECTION("is an image  equal to itself?")
    {
        Image img2 = ImageLoader(img_path + "IMG_2215.JPG").getImage();
        REQUIRE(img1.isEqualTo(img2));


    }
    SECTION("is an image equal to a different one?")
    {
        Image img3 = ImageLoader(img_path + "IMG_2216.JPG").getImage();
        REQUIRE_FALSE(img1.isEqualTo(img3));
    }


}

