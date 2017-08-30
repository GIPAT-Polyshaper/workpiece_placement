//
// Created by riccardo on 20/08/17.
//

#include "CameraCalibrator.h"


void CameraCalibrator::calibrate(int cameraId) {

    int numBoards = this->m_shots;
    int numCornersHor = this->boardSize.width;
    int numCornersVer = this->boardSize.height;

    int numSquares = numCornersHor * numCornersVer;
    Size board_sz = this->boardSize;

    VideoCapture capture = VideoCapture(cameraId);

    std::vector<std::vector<Point3f>> object_points;
    std::vector<std::vector<Point2f>> image_points;

    std::vector<Point2f> corners;
    int successes=0;

    cv::Mat image;

    cv::Mat gray_image;
    capture >> image;

    std::vector<Point3f> obj;
    for(int j=0;j<numSquares;j++)
        obj.emplace_back(j/numCornersHor, j%numCornersHor, 0.0f);

    while(successes<numBoards)
    {
        cvtColor(image, gray_image, CV_BGR2GRAY);
        bool found = findChessboardCorners(image, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if(found)
        {
            cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray_image, board_sz, corners, found);
        }
        imshow("win1", image);
        imshow("win2", gray_image);

        capture >> image;
        auto key = static_cast<char>(cv::waitKey(1));
        if(key==27)

            return;

        if(key==' ' && static_cast<int>(found) !=0)
        {
            image_points.push_back(corners);
            object_points.push_back(obj);

            successes++;

            std::cout<<"Snap " << successes <<"/"<<numBoards << " stored!" << std::endl;

            if(successes>=numBoards)
                break;
        }
    }
    Mat intrinsic = Mat(3, 3, CV_32FC1);
    Mat distCoeffs;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    intrinsic.ptr<float>(0)[0] = 1;
    intrinsic.ptr<float>(1)[1] = 1;
    Size imageSize = image.size();
    calibrateCamera(object_points, image_points, imageSize, intrinsic, distCoeffs, rvecs, tvecs);

    this->saveParams(intrinsic, distCoeffs, imageSize);

}


void CameraCalibrator::saveParams(const cv::Mat &intrinsic ,const cv::Mat &distCoeffs, const Size &imageSize) const                        //Write serialization for this class
{
    cv::FileStorage fs(this->filename, cv::FileStorage::WRITE);

    time_t tm;
    time( &tm );
    struct tm *t2 = localtime( &tm );
    char buf[1024];
    strftime( buf, sizeof(buf), "%c", t2 );

    fs << "calibration_time" << buf;
    fs << "calibration_pattern" << "CHESSBOARD";
    fs << "image_width" << imageSize.width;
    fs << "image_height" << imageSize.height;
    fs << "board_width" << this->boardSize.width;
    fs << "board_height" << this->boardSize.height;
    fs << "shots_number" << this->m_shots;
    fs << "distortion_coefficients" << distCoeffs;
    fs << "intrinsic_matrix" << intrinsic;

//    fs << "square_size" << s.squareSize;

    fs.release();
    std::cout << "Write Done." << std::endl;
}

CameraCalibrator::CameraCalibrator(int boardWidth, int boardHeight, int shots)
        :boardSize(boardWidth,boardHeight),
         m_shots(shots)
{}
