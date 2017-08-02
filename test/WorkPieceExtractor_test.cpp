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
#include "test_config.h"


TEST_CASE("Extracting workpiece"){
//
//    SECTION("Extracting workpiece from purpose-built matrix"){
//        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
//        Mat roi(mat(cv::Rect(100,100,250,300))); // roi points to a submatrix of the origina matrix
//        roi.setTo(255); // white submatrix
////        imshow("ret", mat);
////        waitKey(0);
//        WorkPiece wp = WorkPieceExtractor().workpiece(mat);
//        REQUIRE(wp.getM_point().x == 100);
//        REQUIRE(wp.getM_point().y == 398);
//        REQUIRE(wp.getM_height() == 300);
//        REQUIRE(wp.getM_width() == 250);
//    }
//
//    SECTION("Extracting workpiece from a purpose-built image")
//    {
//        Image img = ImageLoader(img_path+"prova2.png").getM_image();
//        WorkPiece wp = WorkPieceExtractor().workpiece(img.getM_mat());
//        REQUIRE(wp.getM_point().x == 100);
//        REQUIRE(wp.getM_point().y == 298);
//        REQUIRE(wp.getM_height() == 151);
//        REQUIRE(wp.getM_width() == 250);
//    }

    SECTION("Extracting workpiece from rotated purpose-built matrix"){
        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
        cv::RotatedRect rRect(cv::Point(225,250), cv::Size(250,300), 0);
        cv::Point2f vertices2f[4];
        cv::Point vertices[4];
        rRect.points(vertices2f);
        for(int i = 0; i < 4; ++i){
            vertices[i] = vertices2f[i];
        }
        cv::fillConvexPoly(mat, vertices, 4, Scalar(255,255,255));
        imshow("rotret", mat);

        WorkPiece wp = WorkPieceExtractor().workpiece(mat);
        Rect r =rRect.boundingRect();
        rectangle(mat,r,Scalar(255,255,255));
        imshow("rotret1", mat);
        waitKey(0);
//        REQUIRE(wp.getM_point().x == vertices[0].x);
        CHECK(wp.getM_point().y == vertices[0].y);
        CHECK(wp.getM_height() == 300);
        CHECK(wp.getM_width() == 250);
        CHECK(wp.getM_angle() == rRect.angle - 90);
    }


}