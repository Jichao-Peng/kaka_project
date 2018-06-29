//
// Created by leo on 18-3-12.
//

#ifndef PROJECT_KAKADRIVE_H
#define PROJECT_KAKADRIVE_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <kaka_drive_pkg/JointMsg.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <actionlib/server/simple_action_server.h>//实现action的所应该包含的基本的库
#include <control_msgs/FollowJointTrajectoryAction.h>



using namespace std;

class KakaDrive
{
public:
    KakaDrive(string Topic);
    ~KakaDrive();

private:
    ros::NodeHandle Node;//该Handle用于和ROS系统交互
    ros::Publisher DriveMoveitPub;
    ros::Publisher DriveSerialPub;
    ros::Subscriber DriveSerialSub;
    actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> Server;//构造一个action的server，FollowJointTrajectoryAction是规定了通讯的message的类型

    vector<int> NumID;
    map<string,int>  JointID;
    sensor_msgs::JointState FeedbackJointState;//Moveit的接口，反馈给Moveit的消息
    kaka_drive_pkg::JointMsg TargetJointMsg;//Serial的接口，发送给Serial的消息
    vector<trajectory_msgs::JointTrajectoryPoint> TargetPoints;//Moveit的接口，接受Moveit的消息里面轨迹点

    void TargetJointCallBack(const control_msgs::FollowJointTrajectoryGoalConstPtr &Msg);
    void PreemptJointCallBack();
    void FeedbackJointCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg);
    void SetFeedbackJointName(vector<string> JointName);
    void SetFeedbackJointPosition(vector<double> JointPos);
    void PublishFeedbackJoint();
    void PublishTargetJoint(vector<double> JointPos);
    bool JudgePoints(vector<double> TargetPos,vector<double> FeedbackPos);
};


#endif //PROJECT_KAKADRIVE_H
