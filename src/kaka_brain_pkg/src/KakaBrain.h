//
// Created by leo on 18-3-23.
//

#ifndef PROJECT_KAKABRAIN_H
#define PROJECT_KAKABRAIN_H

#include <vector>
#include <Eigen/Dense>
#include <kaka_drive_pkg/JointMsg.h>
#include <kaka_vision_pkg/VisionMsg.h>
#include <moveit/move_group_interface/move_group.h>


using namespace std;

typedef struct
{
    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
}ROBOT_POSE;

typedef enum
{
    READY,
    INIT,
    WAIT,
    MOVE_TO_TARGET,
    GRAP,
    MOVE_TO_HOLD,
    MOVE_TO_PLACE,
    UNGRAP,
    END
}ROBOT_STATE;


class KakaBrain
{
public:
    KakaBrain(string name);

    ~KakaBrain();

    void Run();

private:
    ros::NodeHandle Node;
    ros::Publisher GripperCtrlPub;
    ros::Subscriber VisionResultSub;
    moveit::planning_interface::MoveGroup Group;
    moveit::planning_interface::MoveGroup::Plan Plan;

    bool GetTargetFlag;
    ROBOT_STATE RobotState;
    ROBOT_POSE FeedbackRobotPose;
    geometry_msgs::Pose TargetRobotPose;

    float GrapPos;
    float UngrapPos;
    geometry_msgs::Pose HoldRobotPose;
    geometry_msgs::Pose PlaceRobotPose;

    void DataInit();

    void GetRobotPosRPY();

    void GetRobotPose();

    bool GripperCtrl(char State);

    bool SendInitRobotPos();

    bool SendAbsRobotPosRPY(ROBOT_POSE RobotPose);

    bool SendAbsRobotPose(geometry_msgs::Pose RobotPose);

    void VisionResultCallBack(const kaka_vision_pkg::VisionMsgConstPtr &Msg);
};


#endif //PROJECT_KAKABRAIN_H
