//
// Created by riccardo on 25/07/17.
//

#include "WorkPiece.h"



const cv::Point &WorkPiece::getCenterPoint() const {
    return m_centerPoint;
}


float WorkPiece::getM_angle() const {
    return std::roundf(m_angle * 10)/10;
}

int WorkPiece::getM_longSide() const {
    return m_longSide;
}

int WorkPiece::getM_shortSide() const {
    return m_shortSide;
}

const cv::Point *WorkPiece::getVertices() const {
    return m_vertices;
}

void WorkPiece::setCenterPoint(int x, int y) {
    WorkPiece::m_centerPoint.x = x;
    WorkPiece::m_centerPoint.y = y;
}

void WorkPiece::setM_angle(float m_angle) {
    WorkPiece::m_angle = m_angle;
}


void WorkPiece::setM_longSide(int longSide) {
    WorkPiece::m_longSide = longSide;
}


void WorkPiece::setM_shortSide(int shortSide) {
    WorkPiece::m_shortSide = shortSide;
}

WorkPiece::WorkPiece(const cv::Point &point, float angle, int side1, int side2) : m_centerPoint(point),
                                                                                           m_angle(angle),
                                                                                           m_longSide(side1 > side2 ? side1 : side2),
                                                                                           m_shortSide(side1 < side2 ? side1 : side2)
{
    //todo calculate vertices
}

WorkPiece::WorkPiece(const cv::RotatedRect& rRect):m_angle(rRect.size.width < rRect.size.height ? rRect.angle + 180 : rRect.angle + 90),
                                                  m_longSide(rRect.size.width >= rRect.size.height ? rRect.size.width : rRect.size.height),
                                                  m_shortSide(rRect.size.height <= rRect.size.width ? rRect.size.height : rRect.size.width),
                                                  m_centerPoint(rRect.center.x,rRect.center.y)
{
    cv::Point2f pts[4];
    rRect.points(pts);
    for(int i = 0; i < 4; i++){
        m_vertices[i] = cv::Point((int) pts[i].x, (int) pts[i].y);
    }

}

