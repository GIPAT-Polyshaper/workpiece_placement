//
// Created by riccardo on 25/07/17.
//

#include "WorkPiece.h"


const cv::Point &WorkPiece::getM_point() const {
    return m_point;
}


float WorkPiece::getM_angle() const {
    return m_angle;
}

int WorkPiece::getM_width() const {
    return m_width;
}

int WorkPiece::getM_height() const {
    return m_height;
}


void WorkPiece::setM_point(int x, int y) {
    WorkPiece::m_point.x = x;
    WorkPiece::m_point.y = y;
}

void WorkPiece::setM_angle(float m_angle) {
    WorkPiece::m_angle = m_angle;
}


void WorkPiece::setM_width(int m_width) {
    WorkPiece::m_width = m_width;
}


void WorkPiece::setM_height(int m_height) {
    WorkPiece::m_height = m_height;
}

WorkPiece::WorkPiece(const cv::Point &m_point, float m_angle, int m_width, int m_height) : m_point(m_point),
                                                                                           m_angle(m_angle),
                                                                                           m_width(m_width),
                                                                                           m_height(m_height) {}
