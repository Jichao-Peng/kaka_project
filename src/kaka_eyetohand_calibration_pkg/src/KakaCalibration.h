//
// Created by leo on 18-4-18.
//

#ifndef PROJECT_KAKACALIBRATION_H
#define PROJECT_KAKACALIBRATION_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#include <string>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <message_filters/subscriber.h>
#include <image_transport/image_transport.h>
#include <kaka_interface_pkg/InterfaceCtrl.h>
#include <message_filters/time_synchronizer.h>
#include <moveit/move_group_interface/move_group.h>

#include "KakaCalibMethod.h"

using namespace std;
using namespace cv;

class KakaCalibration
{
public:
    KakaCalibration(string ColorTopic,string DepthTopic,string GroupName);
    ~KakaCalibration();

protected:
    void CalibCmdCallBack(const kaka_interface_pkg::InterfaceCtrl::ConstPtr &Msg);
    void ColorDepthCallBack(const sensor_msgs::ImageConstPtr &ColorMsg, const sensor_msgs::ImageConstPtr &DepthMsg);

    ros::NodeHandle Node;
    moveit::planning_interface::MoveGroup Group;
    image_transport::ImageTransport ImageNode;
    image_transport::Publisher ImagePub;
    ros::Subscriber CalibCmdSub;
    message_filters::Subscriber<sensor_msgs::Image> ColorSub;
    message_filters::Subscriber<sensor_msgs::Image> DepthSub;
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> Synchronizer;

    KakaCalibMethod* CalibMethod;

    Mat CameraMatrix;
    Mat DistCoeffs;

    vector<Mat> CamHCamBuffer,ToolHBaseBuffer;

    HandEyeCalibData CalibrationResult;

    int SampleCount;

    bool StartFlag;
    bool SampleFlag;
};
#endif //PROJECT_KAKACALIBRATION_H
