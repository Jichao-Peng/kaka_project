//
// Created by leo on 18-3-23.
//

#include "KakaGripper.h"


KakaGripper::KakaGripper()
{
    //和Gripper相关的
    GripperCtrlSub = Node.subscribe("/gripper_ctrl",1000,&KakaGripper::GripperCtrlCallBack,this);
    GripperSub = Node.subscribe("/feedback_gripper",1000,&KakaGripper::FeedbackGripperCallBack,this);
    GripperPub = Node.advertise<kaka_drive_pkg::JointMsg>("/target_gripper",1000);
    ROS_INFO("[KAKA_GRIPPER] Running");
}

KakaGripper::~KakaGripper()
{}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"kaka_gripper");
    KakaGripper KakaGripper;
    ros::spin();
    return 0;
}

void KakaGripper::FeedbackGripperCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg)
{
    FeedbackGripperPos = Msg->JointPos.at(0);
}

void KakaGripper::GripperCtrlCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg)
{
    PulishTargetGripper(Msg->JointPos.at(0));
}

void KakaGripper::PulishTargetGripper(float GripperPos)
{
    ROS_INFO("[KAKA_GRIPPER]Pulish!");

    TargetGripperPos = GripperPos;
    kaka_drive_pkg::JointMsg TargetGripperMsg;
    TargetGripperMsg.JointPos.push_back(GripperPos);

    GripperPub.publish(TargetGripperMsg);
}