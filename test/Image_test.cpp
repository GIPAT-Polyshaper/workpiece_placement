//
// Created by riccardo on 10/07/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"

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

TEST_CASE("Image comparison"){

    Image img1 = ImageLoader("IMG_2215.JPG").getM_image();
    
    SECTION("is an image  equal to itself?")
    {
        Image img2 = ImageLoader("IMG_2215.JPG").getM_image();
        REQUIRE(img1.isEqualTo(img2));


    }
    SECTION("is an image equal to a different one?")
    {
        Image img3 = ImageLoader("IMG_2216.JPG").getM_image();
        REQUIRE_FALSE(img1.isEqualTo(img3));
    }


}

