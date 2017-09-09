//
// Created by riccardo on 01/09/17.
//


#include "GcodePointUpdater.h"


GcodePointUpdater::GcodePointUpdater(cv::Size gcodeSize, cv::Point2f vertices[4], float rotationAngle, float workingAreaHeight) :
         m_wpVerticesMM(vertices),
         m_gcodeSize(gcodeSize),
         m_rotationAngle(rotationAngle),
         m_sortedVertices(sortVertices()),
         m_workingAreaHeight(workingAreaHeight)
{
    GcodePointUpdater::rotoTranslation();
}


std::map<float, int> GcodePointUpdater::sortVertices()
{

    std::map<float, int> pointsMap;
    cv::Point2f origin(0,0);
    for (int i = 0; i <4 ; ++i)
    {
        float distance = cv::norm(origin - m_wpVerticesMM[i]);
        pointsMap[distance] = i;
    }

    return pointsMap;

}


void GcodePointUpdater::rotoTranslation()
{

    if(m_rotationAngle >= 90)
    {
        if(m_gcodeSize.width > m_gcodeSize.height)
        {
            m_rotationAngle =  (m_rotationAngle - 90);
            m_translationPoint.x = smallestX().x;
            if(m_rotationAngle == 90)
                m_translationPoint.y = m_workingAreaHeight - biggestY().y;
            else
                m_translationPoint.y = m_workingAreaHeight - smallestX().y;
        }
        else
        {
            m_translationPoint.y = m_workingAreaHeight - smallestY().y;
            if(m_rotationAngle == 90)
                m_translationPoint.x = smallestX().x;
            else
                m_translationPoint.x = smallestY().x;
        }

    }
    else //rotation angle <90
    {

        if(m_gcodeSize.width < m_gcodeSize.height)
        {
            m_translationPoint.x = smallestX().x;
            if(m_rotationAngle == 0)
                m_translationPoint.y = smallestY().y;
            else
                m_translationPoint.y = m_workingAreaHeight - smallestX().y;
        }
        else
        {
            cv::Point2f p = biggestY();
            m_rotationAngle =  - (90 - m_rotationAngle);
            m_translationPoint.y = m_workingAreaHeight - biggestY().y;
            if(m_rotationAngle == 0)
                m_translationPoint.x = biggestX().x;
            else
                m_translationPoint.x = biggestY().x;

        }

    }

}


std::array<double, 4> GcodePointUpdater::elaborate(std::array<double, 4> point, float z)
{

    cv::Mat_<double> p(3,1);

    p(0,0)=point[0];
    p(1,0)=point[1];
    p(2,0)=1.0;

    cv::Mat_<double> rotoTranslationMatrix(3,3);


    float angle = - m_rotationAngle *  PI / 180.0;


    rotoTranslationMatrix(0,0) = cos(angle);
    rotoTranslationMatrix(0,1) = -sin(angle);
    rotoTranslationMatrix(0,2) = m_translationPoint.x;
    rotoTranslationMatrix(1,0) = sin(angle);
    rotoTranslationMatrix(1,1) = cos(angle);
    rotoTranslationMatrix(1,2) = m_translationPoint.y;
    rotoTranslationMatrix(2,0) = 0;
    rotoTranslationMatrix(2,1) = 0;
    rotoTranslationMatrix(2,2) = 1;

    cv::Mat_<double> pTranslatedRotated = rotoTranslationMatrix * p;


    float angle2 = (m_rotationAngle * 10) /float(180);
    point[0] = pTranslatedRotated(0,0);
    point[1] = pTranslatedRotated(0,1);
    point[2] += z;
    point[3] += - angle2 + 5;

    return point;
}

const cv::Point2f GcodePointUpdater::smallestX()
{

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


const cv::Point2f GcodePointUpdater::smallestY()
{

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


const cv::Point2f GcodePointUpdater::biggestY()
{

    float maxY = m_wpVerticesMM[0].y;
    int maxYIndex = 0;
    for(int i = 1; i < 4; i++){

        if(m_wpVerticesMM[i].y > maxY) {
            maxY = m_wpVerticesMM[i].y;
            maxYIndex = i;
        }

    }
    return m_wpVerticesMM[maxYIndex];

}


const cv::Point2f GcodePointUpdater::biggestX()
{

    float maxX = m_wpVerticesMM[0].x;
    int maxXIndex = 0;
    for(int i = 1; i < 4; i++){

        if(m_wpVerticesMM[i].x > maxX) {
            maxX = m_wpVerticesMM[i].y;
            maxXIndex = i;
        }

    }
    return m_wpVerticesMM[maxXIndex];

}
