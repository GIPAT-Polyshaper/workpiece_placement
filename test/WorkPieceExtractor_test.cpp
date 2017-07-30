//
// Created by riccardo on 29/07/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/WorkPiece.h"
#include "../wplib/WorkPieceExtractor.h"
#include "../wplib/ImageLoader.h"


TEST_CASE("Extracting workpiece"){

    SECTION("Extracting workpiece from purpose-built matrix"){
        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
        Mat roi(mat(cv::Rect(100,100,250,300))); // roi points to a submatrix of the origina matrix
        roi.setTo(255); // white submatrix
        WorkPiece wp = WorkPieceExtractor().workpiece(mat);
        REQUIRE(wp.getM_point().x == 100);
        REQUIRE(wp.getM_point().y == 400);
        REQUIRE(wp.getM_height() == 300);
        REQUIRE(wp.getM_width() == 250);
    }

    SECTION("Extracting workpiece from a purpose-built image")
    {
        Image img = ImageLoader("prova2.png").getM_image();
        WorkPiece wp = WorkPieceExtractor().workpiece(img.getM_mat());
        REQUIRE(wp.getM_point().x == 100);
        REQUIRE(wp.getM_point().y == 300);
        REQUIRE(wp.getM_height() == 150);
        REQUIRE(wp.getM_width() == 250);
    }



}