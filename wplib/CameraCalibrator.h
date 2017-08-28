//
// Created by riccardo on 20/08/17.
//

#ifndef WORKPIECE_PLACEMENT_CAMERACALIBRATOR_H
#define WORKPIECE_PLACEMENT_CAMERACALIBRATOR_H


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class CameraCalibrator {

private:

    /**
     * where to write calibration parameters
     */
    const std::string filename = "calibrationParams.xml";

    /**
     * size of the chessboard
     */
    cv::Size boardSize;

    /**
     * number of shots used for calibration
     */
    int m_shots;


public:

    /**
     * Find calibration parameters
     * @param cameraId ID number of the used camera
     */
    void calibrate(int cameraId);

    /**
     * Constructor
     * @param boardWidth number of squares on the long side
     * @param boardHeight number of squares on the short side
     * @param shots number of shots
     */
    CameraCalibrator(int boardWidth, int boardHeight, int shots);

private:

    /**
     * Write parameter on file
     * @param intrinsic Matrix of intrisic parameters
     * @param distCoeffs Distortion coefficent Matrix
     * @param imageSize Size of the image
     */
    void saveParams(Mat &intrinsic, Mat &distCoeffs, Size &imageSize) const;
};


#endif //WORKPIECE_PLACEMENT_CAMERACALIBRATOR_H
