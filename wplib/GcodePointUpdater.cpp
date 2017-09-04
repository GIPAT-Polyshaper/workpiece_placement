//
// Created by riccardo on 01/09/17.
//

#include <map>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include "GcodePointUpdater.h"

#define PI 3.14159265

GcodePointUpdater::GcodePointUpdater(cv::Size gcodeSize, cv::Point2f vertices[4], float rotationAngle, float workingAreaHeight) :
         m_wpVerticesMM(vertices),
         m_gcodeSize(gcodeSize),
         m_rotationAngle(rotationAngle),
         m_sortedVertices(sortVertices()),
         m_workingAreaHeight(workingAreaHeight)
{
    GcodePointUpdater::rotoTranslation();
}


std::map<float, int> GcodePointUpdater::sortVertices() {

    std::map<float, int> pointsMap;
    cv::Point2f origin(0,0);
    for (int i = 0; i <4 ; ++i)
    {
        float distance = cv::norm(origin - m_wpVerticesMM[i]);
        pointsMap[distance] = i;
    }

    return pointsMap;

}

void GcodePointUpdater::rotoTranslation(){

    if(m_rotationAngle > 90)
    {
        if(m_gcodeSize.width > m_gcodeSize.height)
        {
            m_rotationAngle =  (m_rotationAngle - 90);
            m_translationPoint.x = smallestX().x;
            m_translationPoint.y = m_workingAreaHeight - smallestX().y;
        }
        else
        {
            m_translationPoint.x = smallestY().x;
            m_translationPoint.y = m_workingAreaHeight - smallestY().y;
        }

    }
    else //rotation angle <90
    {
        if(m_gcodeSize.width < m_gcodeSize.height)
        {
            m_translationPoint.x = smallestX().x;
            m_translationPoint.y = m_workingAreaHeight - smallestX().y;
        }
        else
        {
            m_rotationAngle =  - (90 - m_rotationAngle);
            m_translationPoint.x = biggestY().x;
            m_translationPoint.y = m_workingAreaHeight - biggestY().y;
        }

    }


//
//    std::map<float,int>::iterator it;
//    it = m_sortedVertices.begin();
//    int i = it->second;
//    cv::Point2f closestPoint = m_wpVerticesMM[i];
//    it++;
//    int j = it->second;
//    cv::Point2f secondClosestPoint = m_wpVerticesMM[j];
//    it++;
//    int k = it->second;
//    cv::Point2f thirdClosestPoint = m_wpVerticesMM[k];
//
//    cv::Point2f traslationPoint;
//    float rotationAngle;
//
//    if(m_rotationAngle > 90)
//    {
//        if(m_gcodeSize.width > m_gcodeSize.height)
//        {
//            m_rotationAngle =  (m_rotationAngle - 90);
//
//            //todo forse da rimuovere il controllo sul terzo punto
//            if(closestPoint.x < secondClosestPoint.x && secondClosestPoint.x < thirdClosestPoint.x)
//                traslationPoint = closestPoint;
//
//            else if(secondClosestPoint.x < closestPoint.x && closestPoint.x < thirdClosestPoint.x)
//                traslationPoint = secondClosestPoint;
//
//            else
//                traslationPoint = thirdClosestPoint;
//
//        }
//        else
//        {
//            if(closestPoint.y > secondClosestPoint.y && secondClosestPoint.y > thirdClosestPoint.y)
//                traslationPoint = closestPoint;
//            else if (secondClosestPoint.y > closestPoint.y && closestPoint.y > thirdClosestPoint.y)
//                traslationPoint = secondClosestPoint;
//            else
//                traslationPoint = thirdClosestPoint;
//        }
//    }
//    else //rotation angle <90
//    {
//
//        if(m_gcodeSize.width < m_gcodeSize.height)
//        {
//            m_rotationAngle = -(90-m_rotationAngle);
//            if(closestPoint.x < secondClosestPoint.x && secondClosestPoint.x < thirdClosestPoint.x)
//                traslationPoint = closestPoint;
//
//            else if(secondClosestPoint.x < closestPoint.x && closestPoint.x < thirdClosestPoint.x)
//                traslationPoint = secondClosestPoint;
//
//            else
//                traslationPoint = thirdClosestPoint;
//
//        }
//        else
//        {
//            if(closestPoint.y < secondClosestPoint.y && secondClosestPoint.y < thirdClosestPoint.y)
//                traslationPoint = closestPoint;
//            else if (secondClosestPoint.y < closestPoint.y && closestPoint.y < thirdClosestPoint.y)
//                traslationPoint = secondClosestPoint;
//            else
//                traslationPoint = thirdClosestPoint;
//        }
//    }
//
//    m_translationPoint = traslationPoint;
}

std::array<double, 4> GcodePointUpdater::elaborate(std::array<double, 4> point, float z)
{
    cv::Mat_<double> p(3,1);

    p(0,0)=point[0];
    p(1,0)=point[1];
    p(2,0)=1.0;


    cv::Mat_<double> R(3,3);

//    float angle = - m_rotationAngle *  PI / 180.0 ;

    float angle = - m_rotationAngle *  PI / 180.0;




    R(0,0) = cos(angle);
    R(0,1) = -sin(angle);
    R(0,2) = m_translationPoint.x;
    R(1,0) = sin(angle);
    R(1,1) = cos(angle);
    R(1,2) = m_translationPoint.y;
    R(2,0) = 0;
    R(2,1) = 0;
    R(2,2) = 1;

    cv::Mat_<double> pRotated = R * p;


//    float pX = p(0,0);
//    float pY = p(0,1);
//    point[0] = pRotated(0,0) + m_translationPoint.x;
//    point[1] = pRotated(0,1) m_translationPoint.y;
//    point[2] += z;
//    point[3] += m_rotationAngle;

//    float x= pRotoTranslated(0,0);
//    float y= pRotoTranslated(0,1);

//    cv::Mat_<double> T(3,3);
//
//    T(0,0) = 1;
//    T(0,1) = 0;
//    T(0,2) = 0;
//    T(1,0) = 0;
//    T(1,1) = 1;
//    T(1,2) = 0;
//    T(2,0) = m_translationPoint.x;
//    T(2,1) = m_translationPoint.y;
//    T(2,2) = 1;
//
////     cv::Point2f pre = m_translationPoint;
    cv::Mat_<double> pTranslatedRotated = pRotated;

    float x = m_rotationAngle;

    point[0] = pTranslatedRotated(0,0);
    point[1] = pTranslatedRotated(0,1);
    point[2] += z;
    point[3] += m_rotationAngle;

    return point;
}

const cv::Point2f GcodePointUpdater::smallestX() {

    float minX = m_wpVerticesMM[0].x;
    int minXIndex = 0;
    for(int i = 1; i < 4; i++){

        if(m_wpVerticesMM[i].x < minX) {
            minX = m_wpVerticesMM[i].x;
            minXIndex = i;
        }

    }
    return m_wpVerticesMM[minXIndex];

}

const cv::Point2f GcodePointUpdater::smallestY() {

    float minY = m_wpVerticesMM[0].y;
    int minYIndex = 0;
    for(int i = 1; i < 4; i++){

        if(m_wpVerticesMM[i].y < minY) {
            minY = m_wpVerticesMM[i].y;
            minYIndex = i;
        }

    }
    return m_wpVerticesMM[minYIndex];

}

const cv::Point2f GcodePointUpdater::biggestY() {

    float maxY = m_wpVerticesMM[0].y;
    int maxYIndex = 0;
    for(int i = 1; i < 4; i++){

        if(m_wpVerticesMM[i].x > maxY) {
            maxY = m_wpVerticesMM[i].y;
            maxYIndex = i;
        }

    }
    return m_wpVerticesMM[maxYIndex];

}
