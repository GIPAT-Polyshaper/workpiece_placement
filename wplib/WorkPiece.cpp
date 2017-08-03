//
// Created by riccardo on 25/07/17.
//

#include "WorkPiece.h"



const cv::Point &WorkPiece::getM_point() const {
    return m_point;
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


void WorkPiece::setM_point(int x, int y) {
    WorkPiece::m_point.x = x;
    WorkPiece::m_point.y = y;
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

WorkPiece::WorkPiece(const cv::Point &point, float angle, int side1, int side2) : m_point(point),
                                                                                           m_angle(angle),
                                                                                           m_longSide(side1 > side2 ? side1 : side2),
                                                                                           m_shortSide(side1 < side2 ? side1 : side2) {}

WorkPiece::WorkPiece(const cv::RotatedRect rRect):m_angle(rRect.size.width < rRect.size.height ? rRect.angle + 180 : rRect.angle + 90),
                                                  m_longSide(rRect.size.width >= rRect.size.height ? rRect.size.width : rRect.size.height),
                                                  m_shortSide(rRect.size.height <= rRect.size.width ? rRect.size.height : rRect.size.width),
                                                  m_point(rRect.center.x,rRect.center.y)
{}
