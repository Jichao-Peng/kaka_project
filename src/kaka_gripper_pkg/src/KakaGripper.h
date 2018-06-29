//
// Created by leo on 18-3-23.
//

#ifndef PROJECT_KAKAGRIPPER_H
#define PROJECT_KAKAGRIPPER_H

#include <ros/ros.h>
#include <kaka_drive_pkg/JointMsg.h>

class KakaGripper
{
public:
    KakaGripper();
    ~KakaGripper();

private:
    ros::NodeHandle Node;
    ros::Subscriber GripperSub;
    ros::Subscriber GripperCtrlSub;
    ros::Publisher GripperPub;

    float TargetGripperPos;
    float FeedbackGripperPos;

    void FeedbackGripperCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg);
    void GripperCtrlCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg);
    void PulishTargetGripper(float GripperPos);
};


#endif //PROJECT_KAKAGRIPPER_H
