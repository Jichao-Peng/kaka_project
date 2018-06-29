//
// Created by leo on 18-4-22.
//

#ifndef PROJECT_KAKACALIBMETHOD_H
#define PROJECT_KAKACALIBMETHOD_H

#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>


using namespace cv;
using namespace std;


struct HandEyeCalibData
{
    Mat CamHBase;
    Mat CalHTool;
};


class KakaCalibMethod
{
public:
    KakaCalibMethod(Size boardsize, float squaresize);
    ~KakaCalibMethod();


    bool CalculateImageCorners(Mat Image, vector<Point2f> &Corner, Mat& ImageOutput);
    bool CalculateChessboardCorners(vector<Point3f> &Corner);
    Mat CalculateCameraHomogeneous(Mat RotationVector, Mat TransitionVector);
    Mat CalculateTCPHomogeneous(vector<double> TCPPose);
    HandEyeCalibData HandEyeCalibration(vector<Mat> CamHCal, vector<Mat> ToolHBase);


private:
    Size BoardSize;
    float SquareSize;

    Mat TsaiSolver(vector<Mat> Hc,vector<Mat> Hd);
    Mat CreatAntisymmetricMatrix(Mat src);
};


#endif //PROJECT_KAKACALIBMETHOD_H
