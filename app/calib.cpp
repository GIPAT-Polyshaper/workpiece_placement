//
// Created by riccardo on 15/10/17.
//

#include <iostream>
#include "../wplib/CameraCalibrator.h"
#include "../wplib/CameraCapture.h"
#include "../wplib/Image.h"
#include "../wplib/WorkingAreaExtractor.h"
#include "../wplib/WorkingAreaSaver.h"

//use this main for camera calibration and working area search
int main(){

    int numBoards = 0;
    int numCornersHor;
    int numCornersVer;

    std::cout<<("Enter number of corners along width: ");
    std::cin>>numCornersHor;

    std::cout<<("Enter number of corners along height: ");
    std::cin>>numCornersVer;

    std::cout<<("Enter number of boards: ");
    std::cin>>numBoards;

    CameraCalibrator cc( numCornersHor, numCornersVer, numBoards);
    cc.elaborate(1);

    std::cout<<"Press 's' to capture and start working area detection, 'Esc' to abort"<<std::endl;

    cv::Mat mCapture = CameraCapture(1).capturing();
    if(mCapture.empty())
        return 0;

//    Image img = ImageLoader("../../sample_imgs/provaSenzaWorkpiece.png").getImage();

    Image img("captured", mCapture);

    img.show();

    cv::Mat copyMat;
    img.getMat().copyTo(copyMat);

//    extracting working area from copy
    cv::Rect r = WorkingAreaExtractor().elaborate(Image("imgCopy", copyMat));

    rectangle(copyMat, r,Scalar(0,0,255), 2);
    imshow("ciao", copyMat);
    waitKey(0);

//    saving working area in a file
    try {
        WorkingAreaSaver().elaborate(r);
    }catch (std::exception &ex) {
        std::cout << "An error occurred: "
                  << ex.what() << "!\n";
    }

    return 0;
}
