//
// Created by riccardo on 10/08/17.
//

#include "CameraCapture.h"


CameraCapture::CameraCapture(int cam): m_camera(cam) {}

cv::Mat CameraCapture::capturing() {

    cv::Mat m;

    cv::VideoCapture cap(this->m_camera); // open the video camera

    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    cv::namedWindow("Capturing",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (1)
    {
        cv::Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        imshow("Capturing", frame); //show the frame in "MyVideo" window
        char ch = cv::waitKey(30);

        if (ch == 's'){
            frame.copyTo(m);
            cv::destroyWindow("Capturing");
            break;
        }

        if (ch == 27){
            std::cout << "esc key is pressed by user" << std::endl;
            break;

        }
    }
    return  m;

}
