//
// Created by leo on 18-3-15.
//

#ifndef PROJECT_KAKASERIAL_H
#define PROJECT_KAKASERIAL_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <kaka_drive_pkg/JointMsg.h>
#include "KakaProtocal.h"

using namespace std;

class KakaSerial
{
public:
    KakaSerial();
    ~KakaSerial();
    void Run();

private:
    int SerialBaudRate;
    string SerialPortName;
    ros::NodeHandle Node;
    ros::NodeHandle ParamNode;
    ros::Subscriber SerialJointSub;
    ros::Publisher SerialJointPub;
    ros::Subscriber SerialGripperSub;
    ros::Publisher SerialGripperPub;

    serial::Serial *SerialPort;
    KakaProtocal *Protocal;

    vector<float> JointTarPos;
    vector<unsigned short> JointTarCode;
    vector<float> JointFBPos;
    vector<unsigned short> JointFBCode;
    float GripperTarPos;
    unsigned short GripperTarCode;
    float GripperFBPos;
    unsigned short GripperFBCode;

    unsigned short RunTime;
    vector<unsigned char> SendCmd;
    vector<unsigned char> ReadData;


    void TargetJointCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg);
    void TargetGripperCallBack(const kaka_drive_pkg::JointMsg::ConstPtr &Msg);
    void PulishFeedbackJoint(vector<float> JointPos);
    void PulishFeedbackGripper(float GripperPos);
    bool OpenSerialPort();
    bool IsOpened();
    void DemandSerialData();
    void ReadSerialData();
};


#endif //PROJECT_KAKASERIAL_H
