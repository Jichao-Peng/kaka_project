//
// Created by leo on 18-3-23.
//

#include "KakaBrain.h"

KakaBrain::KakaBrain(string name):
        Group(name)
{
    VisionResultSub = Node.subscribe("/vision_result",1,&KakaBrain::VisionResultCallBack,this);
    GripperCtrlPub = Node.advertise<kaka_drive_pkg::JointMsg>("/gripper_ctrl",1000);
    RobotState = READY;//状态机起始为READY
    GetTargetFlag = false;//现在的机制是视觉节点会一直发布数据，在机器人INIT的时候通过这个flag开始更新视觉数据，进入WAIT状态之后停止数据更新
    DataInit();
}

KakaBrain::~KakaBrain()
{

}

void KakaBrain::Run()
{
    ROS_INFO("[KAKA_BRAIN] Running");
    ros::Rate Rate(10);
    sleep(5);

    while (ros::ok())
    {
        //查询有位置用
//        GetRobotPose();
//        sleep(1);
        //目前没有反馈，简单采用延时处理
        switch(RobotState)
        {
            case READY:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Ready! Have A Good Time.");
                RobotState = INIT;
                GetTargetFlag = true;
                break;

            case INIT:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Initializing...");
                if(SendInitRobotPos())
                {
                    ROS_INFO("[KAKA_BRAIN] Initialization Success!");
                    RobotState = WAIT;
                    sleep(5);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Initialization Failed!");
                    RobotState = END;
                }
                break;

            case WAIT:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Waiting...");
                GetTargetFlag = false;
                RobotState = MOVE_TO_TARGET;
                break;

            case MOVE_TO_TARGET:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Moving To The Target...");
                cout<<TargetRobotPose<<endl;
                if(SendAbsRobotPose(TargetRobotPose))
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Success!");
                    RobotState = GRAP;//Test
                    sleep(5);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Failed!");
                    RobotState = END;
                }
                break;

            case GRAP:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Grapping...");
                if(GripperCtrl(0))
                {
                    ROS_INFO("[KAKA_BRAIN] Grapping Success!");
                    RobotState = MOVE_TO_HOLD;
                    sleep(5);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Grapping Failed!");
                    RobotState = END;
                }
                break;

            case MOVE_TO_HOLD:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Moving To Hold...");
                if(SendAbsRobotPose(HoldRobotPose))
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Success!");
                    RobotState = MOVE_TO_PLACE;
                    sleep(5);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Failed!");
                    RobotState = END;
                }
                break;

            case MOVE_TO_PLACE:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Moving To Place...");
                if(SendAbsRobotPose(PlaceRobotPose))
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Success!");
                    RobotState = UNGRAP;
                    sleep(5);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Moving Failed!");
                    RobotState = END;
                }
                break;

            case UNGRAP:
                ROS_INFO("[KAKA_BRAIN] Kaka Is Ungrapping...");
                if(GripperCtrl(1))
                {
                    ROS_INFO("[KAKA_BRAIN] Grapping Success!");
                    RobotState = END;
                    sleep(2);
                }
                else
                {
                    ROS_INFO("[KAKA_BRAIN] Grapping Failed!");
                    RobotState = END;
                }
                break;

            case END:
                ROS_INFO("[KAKA_BRAIN] Kaka Is End");
                //SendInitRobotPos();
                break;

            default:
                break;
        }
        Rate.sleep();
        ros::spinOnce();
    }
}

//[ INFO] [1525446354.197119362]: [KAKA_BRAIN] RobotPose:
//[ INFO] [1525446354.197178603]:                PX: 0.158403
//[ INFO] [1525446354.197206206]:                PY: -0.009961
//[ INFO] [1525446354.197227319]:                PZ: 0.253695
//[ INFO] [1525446354.197249144]:                 X: 0.017939
//[ INFO] [1525446354.197271117]:                 Y: 0.713965
//[ INFO] [1525446354.197293008]:                 Z: -0.026368
//[ INFO] [1525446354.197303935]:                 W: 0.699455

//[ INFO] [1525446410.232589934]:                PX: 0.009067
//[ INFO] [1525446410.232612645]:                PY: 0.164022
//[ INFO] [1525446410.232623735]:                PZ: 0.016169
//[ INFO] [1525446410.232633556]:                 X: -0.686690
//[ INFO] [1525446410.232643171]:                 Y: 0.713633
//[ INFO] [1525446410.232652230]:                 Z: 0.094354
//[ INFO] [1525446410.232661672]:                 W: 0.101401

void KakaBrain::DataInit()
{
    GrapPos = 540;
    UngrapPos = 400;

    HoldRobotPose.position.x = 0.158403;
    HoldRobotPose.position.y = -0.009961;
    HoldRobotPose.position.z = 0.253695;
    HoldRobotPose.orientation.x = 0.017939;
    HoldRobotPose.orientation.y = 0.713965;
    HoldRobotPose.orientation.z = -0.026368;
    HoldRobotPose.orientation.w = 0.699455;

    PlaceRobotPose.position.x = 0.009067;
    PlaceRobotPose.position.y = 0.164022;
    PlaceRobotPose.position.z = 0.016169;
    PlaceRobotPose.orientation.x = -0.686690;
    PlaceRobotPose.orientation.y = 0.713633;
    PlaceRobotPose.orientation.z = 0.094354;
    PlaceRobotPose.orientation.w = 0.101401;
}

//视觉结果反馈函数
void KakaBrain::VisionResultCallBack(const kaka_vision_pkg::VisionMsgConstPtr &Msg)
{
    if(GetTargetFlag)
    {
        TargetRobotPose.orientation.x = Msg->Quaternion.at(0);
        TargetRobotPose.orientation.y = Msg->Quaternion.at(1);
        TargetRobotPose.orientation.z = Msg->Quaternion.at(2);
        TargetRobotPose.orientation.w = Msg->Quaternion.at(3);
        TargetRobotPose.position.x = Msg->Position.at(0) / 1000;
        TargetRobotPose.position.y = Msg->Position.at(1) / 1000;
        TargetRobotPose.position.z = Msg->Position.at(2) / 1000;
    }
}


//查询机器人末端执行器姿态
void KakaBrain::GetRobotPosRPY()
{
    geometry_msgs::PoseStamped FeedbackPose;
    vector<double>  FeedbackRPY;

    FeedbackPose = Group.getCurrentPose();
    FeedbackRPY = Group.getCurrentRPY();

    FeedbackRobotPose.x = FeedbackPose.pose.position.x;
    FeedbackRobotPose.y = FeedbackPose.pose.position.y;
    FeedbackRobotPose.z = FeedbackPose.pose.position.z;
    FeedbackRobotPose.roll = FeedbackRPY.at(0);
    FeedbackRobotPose.pitch = FeedbackRPY.at(1);
    FeedbackRobotPose.yaw = FeedbackRPY.at(2);
    //打印机器人姿态
    ROS_INFO("[KAKA_BRAIN] RobotPose: ");
    ROS_INFO("                X: %f",FeedbackRobotPose.x);
    ROS_INFO("                Y: %f",FeedbackRobotPose.y);
    ROS_INFO("                Z: %f",FeedbackRobotPose.z);
    ROS_INFO("             Roll: %f",FeedbackRobotPose.roll);
    ROS_INFO("            Pitch: %f",FeedbackRobotPose.pitch);
    ROS_INFO("              Yaw: %f",FeedbackRobotPose.yaw);
    ROS_INFO(" ");
}

void KakaBrain::GetRobotPose()
{
    geometry_msgs::PoseStamped FeedbackPose;
    FeedbackPose = Group.getCurrentPose();
    //打印机器人姿态
    ROS_INFO("[KAKA_BRAIN] RobotPose: ");
    ROS_INFO("               PX: %f",FeedbackPose.pose.position.x);
    ROS_INFO("               PY: %f",FeedbackPose.pose.position.y);
    ROS_INFO("               PZ: %f",FeedbackPose.pose.position.z);
    ROS_INFO("                X: %f",FeedbackPose.pose.orientation.x);
    ROS_INFO("                Y: %f",FeedbackPose.pose.orientation.y);
    ROS_INFO("                Z: %f",FeedbackPose.pose.orientation.z);
    ROS_INFO("                W: %f",FeedbackPose.pose.orientation.w);
    ROS_INFO(" ");
}

//夹抓控制
bool KakaBrain::GripperCtrl(char State)
{
    float TargetGripperPos;
    kaka_drive_pkg::JointMsg TargetGripperMsg;

    if(State == 0)
    {
        TargetGripperPos = GrapPos;
    }
    else if(State == 1)
    {
        TargetGripperPos = UngrapPos;
    }
    else
    {
        return false;
    }

    TargetGripperMsg.JointPos.push_back(TargetGripperPos);
    GripperCtrlPub.publish(TargetGripperMsg);
    return true;
}


//发送机器人初始位姿
bool KakaBrain::SendInitRobotPos()
{
    bool TargetFlag = Group.setNamedTarget("INIT");
    Group.setGoalTolerance(0.01);
    Group.setStartStateToCurrentState();
    if(TargetFlag)
    {
        bool MoveFlag = Group.asyncMove();
        if(MoveFlag)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

//以RPY形式发送机器人绝对位姿
bool KakaBrain::SendAbsRobotPosRPY(ROBOT_POSE RobotPose)
{
    bool RPYTargetFlag = Group.setRPYTarget(RobotPose.roll,RobotPose.pitch,RobotPose.yaw);
    bool PosTargetFlag = Group.setPositionTarget(RobotPose.x,RobotPose.y,RobotPose.z);
    Group.setStartStateToCurrentState();
    Group.setGoalTolerance(0.01);
    Group.allowReplanning(true);

    if(RPYTargetFlag && PosTargetFlag)
    {
        ///bool MoveFlag = Group.asyncMove();
        moveit::planning_interface::MoveGroup::Plan Plan;
        bool PlanFlag = Group.plan(Plan);
        if(PlanFlag)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {

        return false;
    }
}

//以Pose形式发送机器人绝对位姿
bool KakaBrain::SendAbsRobotPose(geometry_msgs::Pose RobotPose)
{
    bool TargetFlag = Group.setPoseTarget(RobotPose);
    Group.setStartStateToCurrentState();
    Group.setGoalTolerance(0.01);
    Group.setPlanningTime(10);
    Group.allowReplanning(true);
    if(TargetFlag)
    {
        bool MoveFlag = Group.asyncMove();
        //moveit::planning_interface::MoveGroup::Plan Plan;
        //bool PlanFlag = Group.plan(Plan);
        if(MoveFlag)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"kaka_brain");
    KakaBrain KakaBrain("arm");
    KakaBrain.Run();
    return 0;
}


