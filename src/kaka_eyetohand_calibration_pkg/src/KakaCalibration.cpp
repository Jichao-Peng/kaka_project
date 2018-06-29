//
// Created by leo on 18-4-18.
//
//相机标定的程序相对比较独立，按道理来说应该分成相机driver和机器人driver，但是懒得写了，写成一个程序吧

#include "KakaCalibration.h"

KakaCalibration::KakaCalibration(string ColorTopic,string DepthTopic,string GroupName):
        ImageNode(Node),
        ColorSub(Node,ColorTopic,1),
        DepthSub(Node,DepthTopic,1),
        Synchronizer(ColorSub,DepthSub,10),
        Group(GroupName)
{
    CalibCmdSub = Node.subscribe("/calibration_cmd",1000,&KakaCalibration::CalibCmdCallBack,this);
    Synchronizer.registerCallback(boost::bind(&KakaCalibration::ColorDepthCallBack,this,_1,_2));
    ImagePub = ImageNode.advertise("/output",1);

    CalibMethod = new KakaCalibMethod(Size(6,9),7);

    StartFlag = false;
    SampleFlag = false;

    CameraMatrix = (Mat_<float>(3,3)<<606.678568f, 0.000000,    324.123102f,
                                      0.000000,    608.676854f, 232.570872f,
                                      0.000000,    0.000000,    1.000000);
    DistCoeffs = (Mat_<float>(5,1)<<0.115292, -0.228710f, -0.000350f, -0.001468f, 0.000000);//列向量
}

KakaCalibration::~KakaCalibration()
{
    delete CalibMethod;
}

void KakaCalibration::CalibCmdCallBack(const kaka_interface_pkg::InterfaceCtrl::ConstPtr &Msg)
{
    if(Msg->Cmd == 1)//Start命令,系统进入标定状态
    {
        SampleCount = 0;
        CamHCamBuffer.clear();
        ROS_INFO("[KAKA_CALIBRATION] Calibration Start!");
        StartFlag = true;
    }
    if(Msg->Cmd == 2)//Stop命令，系统停止标定状态
    {
        ToolHBaseBuffer.clear();
        ROS_INFO("[KAKA_CALIBRATION] Calibration Stop!");
        StartFlag = false;
    }
    if(Msg->Cmd == 3)//Sample命令，进行标定点采样
    {
        ROS_INFO("[KAKA_CALIBRATION] Sampling!");
        SampleFlag = true;
    }
    if(Msg->Cmd == 4)//Calculation命令，进行AX = XB计算
    {
        ROS_INFO("[KAKA_CALIBRATION] Calculating!");
        if((!CamHCamBuffer.empty())&&(!ToolHBaseBuffer.empty()))
        {
            CalibrationResult = CalibMethod->HandEyeCalibration(CamHCamBuffer,ToolHBaseBuffer);
            cout << "[KAKA_CALIBRATION] CalHTool: " << endl << CalibrationResult.CalHTool << endl << endl;
            cout << "[KAKA_CALIBRATION] CamHBase: " << endl << CalibrationResult.CamHBase << endl << endl;
        }
        else
        {
            ROS_INFO("[KAKA_CALIBRATION] No Data to Calculat!");
        }

    }
}

void KakaCalibration::ColorDepthCallBack(const sensor_msgs::ImageConstPtr &ColorMsg,const sensor_msgs::ImageConstPtr &DepthMsg)
{
    cv_bridge::CvImagePtr CvColorPtr(new cv_bridge::CvImage);
    Mat Color = cv_bridge::toCvCopy(ColorMsg,sensor_msgs::image_encodings::BGR8)->image;
    cvtColor(Color,Color,COLOR_BGR2RGB);

    Mat Output;
    vector<Point2f> Corners;

    if(StartFlag)
    {
        bool CornerFlag = CalibMethod->CalculateImageCorners(Color, Corners, Output);//计算并显示棋盘格的角点，开始标定之后用户可以观察到棋盘格

        if(SampleFlag)
        {
            if(CornerFlag)
            {
                vector<Point3f> StandCorners;
                ROS_INFO("[KAKA_CALIBRATION] Get Corner!");
                if (CalibMethod->CalculateChessboardCorners(StandCorners))
                {
                    //求得CamHCal
                    Mat RotationVector, TransitionVector, CamHCal;
                    //求得ToolHBase
                    geometry_msgs::PoseStamped FeedbackPose;
                    vector<double> FeedbackRPY;
                    vector<double> TCPPose;
                    Mat ToolHBase;

                    //求得ToolHBase
                    FeedbackPose = Group.getCurrentPose();
                    FeedbackRPY = Group.getCurrentRPY();
                    if (FeedbackPose.pose.position.x == 0 ||
                        FeedbackPose.pose.position.y == 0 ||
                        FeedbackPose.pose.position.z == 0 ||
                        FeedbackRPY.at(0) == 0 ||
                        FeedbackRPY.at(1) == 0 ||
                        FeedbackRPY.at(2) == 0
                            )
                    {
                        ROS_INFO("[KAKA_CALIBRATION] The Data May be Error!Abandon");
                    }
                    else
                    {
                        SampleCount++;
                        ROS_INFO("[KAKA_CALIBRATION] SampleTimes: %d",SampleCount);

                        TCPPose.push_back(FeedbackPose.pose.position.x);
                        TCPPose.push_back(FeedbackPose.pose.position.y);
                        TCPPose.push_back(FeedbackPose.pose.position.z);
                        TCPPose.push_back(FeedbackRPY.at(0));
                        TCPPose.push_back(FeedbackRPY.at(1));
                        TCPPose.push_back(FeedbackRPY.at(2));


                        vector<double>::iterator it;
                        for (it = TCPPose.begin(); it != TCPPose.end(); it++)
                        {
                            ROS_INFO("%f", *it);
                        }


                        ToolHBase = CalibMethod->CalculateTCPHomogeneous(TCPPose);
                        ToolHBaseBuffer.push_back(ToolHBase);
                        cout << "[KAKA_CALIBRATION] ToolHBase: " << endl << ToolHBase << endl << endl;

                        //求得CamHCal
                        solvePnP(StandCorners, Corners, CameraMatrix, DistCoeffs, RotationVector,
                                 TransitionVector);//输出也是列向量
                        CamHCal = CalibMethod->CalculateCameraHomogeneous(RotationVector, TransitionVector);
                        CamHCamBuffer.push_back(CamHCal);
                        cout << "[KAKA_CALIBRATION] CamHCal: " << endl << CamHCal << endl << endl;
                    }
                    SampleFlag = false;
                }
            }
            else
            {
                ROS_INFO("[KAKA_CALIBRATION] Can't Find Corner!");
            }

        }
    }
    else
    {
        Color.copyTo(Output);//直接将输出图像
    }

    CvColorPtr->encoding = "rgb8";
    CvColorPtr->header.stamp = ros::Time::now();
    CvColorPtr->header.frame_id = "camera_depth_frame";
    CvColorPtr->image = Output;
    ImagePub.publish(CvColorPtr->toImageMsg());
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"kaka_calibration");
    KakaCalibration KakaCalibration("/camera/rgb/image_raw","/camera/depth_registered/sw_registered/image_rect_raw","arm");
    ros::spin();
    return 0;
}



