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


TEST_CASE("Extracting elaborate"){

    SECTION("Extracting elaborate from purpose-built matrix"){

        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
        Mat roi(mat(cv::Rect(100,100,250,300))); // roi points to a submatrix of the origina matrix
        roi.setTo(255); // white submatrix
        WorkPiece wp = WorkPieceExtractor().elaborate(mat);
        Approx X_target = Approx(225).epsilon(0.01);
        Approx Y_target = Approx(250).epsilon(0.01);
        Approx SS_target = Approx(250).epsilon(0.01);
        Approx LS_target = Approx(300).epsilon(0.01);
        REQUIRE(wp.getCenterPoint().x == X_target);
        REQUIRE(wp.getCenterPoint().y == Y_target);
        REQUIRE(wp.getShortSide() == SS_target);
        REQUIRE(wp.getLongSide() == LS_target);

    }

    SECTION("Extracting elaborate from a purpose-built image"){

        Image img = ImageLoader(img_path+"prova2.png").getM_image();
        WorkPiece wp = WorkPieceExtractor().elaborate(img.getM_mat());
        Approx X_target = Approx(225).epsilon(0.01);
        Approx Y_target = Approx(225).epsilon(0.01);
        Approx SS_target = Approx(150).epsilon(0.01);
        Approx LS_target = Approx(250).epsilon(0.01);
        REQUIRE(wp.getCenterPoint().y == Y_target);
        REQUIRE(wp.getCenterPoint().x  == X_target);
        REQUIRE(wp.getShortSide() == SS_target);
        REQUIRE(wp.getLongSide() == LS_target);

    }

    SECTION("Extracting elaborate from rotated purpose-built matrix"){

        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
        cv::RotatedRect rRect(cv::Point(225,250), cv::Size(250,300), 30);
        cv::Point2f vertices2f[4];
        cv::Point vertices[4];
        rRect.points(vertices2f);
        for(int i = 0; i < 4; ++i){
            vertices[i] = vertices2f[i];
        }
        cv::fillConvexPoly(mat, vertices, 4, Scalar(255,255,255));
        WorkPiece wp = WorkPieceExtractor().elaborate(mat);
        Rect r =rRect.boundingRect();
        rectangle(mat,r,Scalar(255,255,255));
        Approx X_target = Approx(rRect.center.x).epsilon(0.01);
        Approx Y_target = Approx(rRect.center.y).epsilon(0.01);
        Approx SS_target = Approx(250).epsilon(0.02);
        Approx LS_target = Approx(300).epsilon(0.02);
        Approx A_target = Approx(30).epsilon(0.01);
        CHECK(wp.getCenterPoint().x == X_target);
        CHECK(wp.getCenterPoint().y == Y_target);
        CHECK(wp.getShortSide() == SS_target);
        CHECK(wp.getLongSide() == LS_target);
        CHECK(wp.getAngle() ==A_target);

    }


    SECTION("Extracting non-rectangular elaborate"){

        cv::Mat mat = Mat::zeros(500,500,CV_8UC1);
        Mat roi(mat(cv::Rect(100,100,200,250))); // roi points to a submatrix of the origina matrix
        roi.setTo(255);
        cv::Point p[3] = {cv::Point(300,100), cv::Point(300,349), cv::Point(400,349)};
        fillConvexPoly(mat, p, 3,Scalar(255,255,255));
        WorkPiece wp = WorkPieceExtractor().elaborate(mat);

        Approx X_target = Approx(200).epsilon(0.01);
        Approx Y_target = Approx(225).epsilon(0.01);
        Approx SS_target = Approx(200).epsilon(0.01);
        Approx LS_target = Approx(250).epsilon(0.01);
        CHECK(wp.getCenterPoint().x == X_target);
        CHECK(wp.getCenterPoint().y == Y_target);
        CHECK(wp.getShortSide() == SS_target);
        CHECK(wp.getLongSide() == LS_target);
        bool angleCheck = wp.getAngle() ==float(180) || wp.getAngle() ==float(0);
        CHECK(angleCheck);
    }

}