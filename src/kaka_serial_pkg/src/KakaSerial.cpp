//
// Created by leo on 18-3-15.
//

#include "KakaSerial.h"

KakaSerial::KakaSerial()
{
    //和Joint相关的
    SerialJointSub = Node.subscribe("/target_joint",1000,&KakaSerial::TargetJointCallBack,this);
    SerialJointPub = Node.advertise<kaka_drive_pkg::JointMsg>("/feedback_joint",1000);

    //和Gripper相关的
    SerialGripperSub = Node.subscribe("/target_gripper",1000,&KakaSerial::TargetGripperCallBack,this);
    SerialGripperPub = Node.advertise<kaka_drive_pkg::JointMsg>("/feedback_gripper",1000);

    //这么写的作用是可以从launch文件中直接选择串口以及波特率
    ParamNode.param<string>("serial_port",SerialPortName,"/dev/ttyUSB0");
    ParamNode.param<int>("serial_baudrate",SerialBaudRate,9600);

    Protocal = new KakaProtocal;
    SerialPort = new serial::Serial;
}

KakaSerial::~KakaSerial()
{
    delete Protocal;
    delete SerialPort;
}

void KakaSerial::Run()
{
    ROS_INFO("[KAKA_SERIAL] Running");
    OpenSerialPort();//如果一直打不开可能是串口权限的问题

    ros::Rate Rate(8);
    while (ros::ok())
    {
        if(IsOpened())
        {
            DemandSerialData();
            ReadSerialData();
        }
        else
        {
            //ROS_INFO("[KAKA SERIAL] Open Serial Port Failed, Try Again");
            OpenSerialPort();
        }
        Rate.sleep();
        ros::spinOnce();
    }

}

//发送目标位姿给机械臂
void KakaSerial::TargetJointCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg)
{
    JointTarPos.resize(Msg->JointPos.size());
    JointTarPos.assign(Msg->JointPos.begin(),Msg->JointPos.end());
    RunTime = 1000;
    Protocal->PostoCode(JointTarPos,JointTarCode);
    Protocal->CreatSendCmd(SEND_ALL_JPINT_POS,SendCmd,JointTarCode,RunTime);
    SerialPort->write(SendCmd);
}

//发送目标位置给夹爪
void KakaSerial::TargetGripperCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg)
{
    GripperTarPos = Msg->JointPos.at(0);
    Protocal->GripperPostoCode(GripperTarPos,GripperTarCode);
    RunTime = 1000;
    vector<unsigned short> GripperTarPosTmp;
    GripperTarPosTmp.push_back(GripperTarCode);
    Protocal->CreatSendCmd(SEND_GRIPPER_POS,SendCmd,GripperTarPosTmp,RunTime);

    SerialPort->write(SendCmd);
}

//请求串口数据，以一定频率执行
void KakaSerial::DemandSerialData()
{
    Protocal->CreatSendCmd(GET_ALL_POS, SendCmd);
    SerialPort->write(SendCmd);
}

//读取串口数据，以同样频率解析成机械臂位姿和夹爪位置
void KakaSerial::ReadSerialData()
{
    ReadData.clear();
    if(SerialPort->available())
    {
        SerialPort->read(ReadData, 23);
        Protocal->DecodeReadData(ReadData, JointFBCode, GripperFBCode);
        Protocal->CodetoPos(JointFBPos, JointFBCode);\
        Protocal->GripperCodetoPos(GripperFBPos,GripperFBCode);
        PulishFeedbackJoint(JointFBPos);
        PulishFeedbackGripper(GripperFBPos);
    }
}

//发送机械臂位姿
void KakaSerial::PulishFeedbackJoint(vector<float> JointPos)
{
    kaka_drive_pkg::JointMsg FeedbackJointMsg;
    FeedbackJointMsg.JointPos.resize(JointPos.size());
    FeedbackJointMsg.JointPos.assign(JointPos.begin(),JointPos.end());
    FeedbackJointMsg.Time = 0;
    SerialJointPub.publish(FeedbackJointMsg);
}

//发送夹爪位置
void KakaSerial::PulishFeedbackGripper(float GripperPos)
{
    kaka_drive_pkg::JointMsg FeedbackGripperMsg;
    FeedbackGripperMsg.JointPos.push_back(GripperPos);
    FeedbackGripperMsg.Time = 0;
    SerialGripperPub.publish(FeedbackGripperMsg);
}

//打开串口
bool KakaSerial::OpenSerialPort()
{
    try
    {
        SerialPort->setPort(SerialPortName);
        SerialPort->setBaudrate(SerialBaudRate);
        serial::Timeout Time = serial::Timeout::simpleTimeout(1000);
        SerialPort->setTimeout(Time);
        SerialPort->open();
        ROS_INFO("[KAKA SERIAL] Open Serial Port Success!");
        return true;
    }
    catch (serial::IOException &Err)
    {
        //ROS_INFO("[KAKA SERIAL] Unable to Open Serial Port");
        return false;
    }
}

bool KakaSerial::IsOpened()
{
    if(SerialPort->isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"kaka_serial");
    KakaSerial KakaSerial;
    KakaSerial.Run();
    return 0;
}