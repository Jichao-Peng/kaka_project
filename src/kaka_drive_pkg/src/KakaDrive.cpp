//
// Created by leo on 18-3-12.
//

#include "KakaDrive.h"


KakaDrive::KakaDrive(string Topic):
        Node("~"),
        Server(Node,Topic,boost::bind(&KakaDrive::TargetJointCallBack,this,_1),false)//初始化Server,GoalCallBack是所有任务执行完之后的程序
{
    Node.param("gripper_roll_joint",JointID["gripper_roll_joint"],0);
    Node.param("wrist_pitch_joint",JointID["wrist_pitch_joint"],1);
    Node.param("elbow_pitch_joint",JointID["elbow_pitch_joint"],2);
    Node.param("shoulder_pitch_joint",JointID["shoulder_pitch_joint"],3);
    Node.param("shoulder_roll_joint",JointID["shoulder_roll_joint"],4);

    //建立了一个DriveMoveitPub的Pulisher，订阅了主题fake_controller_joint_states，发布的消息类型是JointState，buffersize是1
    //这个Pulisher应该是用来发布机器人关节状态给Moveit
    DriveMoveitPub = Node.advertise<sensor_msgs::JointState>("/feedback_joint_states",1);
    //建立了一个DriveSerialPub的Pulisher，订阅了主题/target_joint，发布的消息类型是JointMsg,buffersize是1000，需要先有1000个数据在buff中才能发送
    //这个Pulisher应该是用来发布机器人需要转动的关节角度给下层控制器
    DriveSerialPub = Node.advertise<kaka_drive_pkg::JointMsg>("/target_joint",1000);
    DriveSerialSub = Node.subscribe("/feedback_joint",1000,&KakaDrive::FeedbackJointCallBack,this);

    Server.registerPreemptCallback(boost::bind(&KakaDrive::PreemptJointCallBack,this));//高优先级的中断响应
    Server.start();

    ROS_INFO("[KAKA_DRIVE] Running");
}

KakaDrive::~KakaDrive()
{

}

//目标回调函数
//目前的策略是收到一系列规划点之后只发最后一个点
void KakaDrive::TargetJointCallBack(const control_msgs::FollowJointTrajectoryGoalConstPtr &Msg)//理论上应该就是GoalConstPtr，不知道为什么会报错
{
    NumID.clear();//确定Moveit输出参数顺序，神坑呐！
    vector<string> TargetNames = (*Msg).trajectory.joint_names;
    vector<string>::iterator it;
    for(it = TargetNames.begin();it != TargetNames.end();it++)
    {
        NumID.push_back(JointID[(*it)]);
    }

    TargetPoints = (*Msg).trajectory.points;//Moveit规划出来的轨迹上的所有点
    vector<trajectory_msgs::JointTrajectoryPoint>::iterator itend = TargetPoints.end();
    itend--;
    PublishTargetJoint((*itend).positions);

    if(Server.isActive())
    {
        Server.setSucceeded();
    }
}


//反馈回调函数
//目前的策略是收到反馈值激活会回调函数，直接将值发送给Moveit
void KakaDrive::FeedbackJointCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg)
{
    vector<double> JointFBPos;
    JointFBPos.resize(Msg->JointPos.size());
    JointFBPos.assign(Msg->JointPos.begin(),Msg->JointPos.end());
    SetFeedbackJointPosition(JointFBPos);//反馈的关节角度

    //对从串口反馈回来的角度值进行打包发送给Moveit
    vector<string> JointName;
    JointName.push_back("gripper_roll_joint");
    JointName.push_back("wrist_pitch_joint");
    JointName.push_back("elbow_pitch_joint");
    JointName.push_back("shoulder_pitch_joint");
    JointName.push_back("shoulder_roll_joint");
    SetFeedbackJointName(JointName);//反馈的关节名称
    PublishFeedbackJoint();//将关节的角度反馈给Moveit

//    //打印当前反馈位置和发送的目标位置
//    vector<float>::iterator id;;
//    int i = 0;
//    ROS_INFO("End Position:");
//    for(id = TargetJointMsg.JointPos.begin();id != TargetJointMsg.JointPos.end();id++,i++)
//    {
//        ROS_INFO("[%d] %f",i,(*id));
//    }
//
//    vector<double>::iterator it;
//    int t = 0;
//    ROS_INFO("FB Position:");
//    for(it = JointFBPos.begin();it != JointFBPos.end();it++,t++)
//    {
//        ROS_INFO("[%d] %f",t,(*it));
//    }
//    ROS_INFO(" ");
}


//优先回调函数函数
void KakaDrive::PreemptJointCallBack()
{
    if(Server.isActive())
    {
        Server.setPreempted();
    }
}

void KakaDrive::SetFeedbackJointName(vector<string> JointName)
{
    FeedbackJointState.name.resize(JointName.size());
    FeedbackJointState.name.assign(JointName.begin(), JointName.end());
}

void KakaDrive::SetFeedbackJointPosition(vector<double> JointPos)
{
    FeedbackJointState.position.resize(JointPos.size());
    FeedbackJointState.position.assign(JointPos.begin(),JointPos.end());
}

//发布反馈值给Moveit
void KakaDrive::PublishFeedbackJoint()
{
    FeedbackJointState.header.stamp = ros::Time::now();
    DriveMoveitPub.publish(FeedbackJointState);
}

//发布目标值给串口
void KakaDrive::PublishTargetJoint(vector<double> JointPos)
{
    //调整目标位置顺序
    TargetJointMsg.JointPos.resize(JointPos.size());
    vector<int>::iterator it;
    int i = 0;
    for(it = NumID.begin();it != NumID.end();it++,i++)
    {
        TargetJointMsg.JointPos.at((*it)) = (float)JointPos.at(i);
    }

    TargetJointMsg.Time = 0;
    DriveSerialPub.publish(TargetJointMsg);
}

//判断反馈位置是否达到目标位置
bool KakaDrive::JudgePoints(vector<double> TargetPos, vector<double> FeedbackPos)
{
    //调整目标位置的顺序
    vector<double> TargetPosTemp;
    TargetPosTemp.resize(TargetPos.size());
    vector<int>::iterator it;
    int j = 0;
    for(it = NumID.begin();it != NumID.end();it++,j++)
    {
        TargetPosTemp.at((*it)) = (float)TargetPos.at(j);
    }

    double Limits = 3;
    vector<double> Result;
    for(int i=0 ; i<4 ; i++)
    {
        Result.push_back(abs(TargetPosTemp.at(i)-FeedbackPos.at(i)));
    }

    if(Result[max_element(Result.begin(),Result.end())-Result.begin()]<Limits)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"kaka_drive");//节点名称
    KakaDrive KakaDrive("/kaka_arm_controller/follow_joint_trajectory");//follow_joint_trajectory为topic名称
    ros::spin();
    return 0;
}




