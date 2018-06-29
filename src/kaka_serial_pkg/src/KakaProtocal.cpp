//
// Created by leo on 18-3-17.
//

#include <stdint.h>
#include "KakaProtocal.h"

void KakaProtocal::CodetoPos(vector<float> &Pos,const vector<unsigned short> &Code)
{
    Pos.clear();
    vector<unsigned short>::const_iterator it;
    for(it = Code.begin();it != Code.end();it++)
    {
        Pos.push_back(((((*it) - 500) * 0.24) / 180) * 3.14);
    }
    Pos.at(2) = -Pos.at(2);
}

void KakaProtocal::PostoCode(const vector<float> &Pos, vector<unsigned short> &Code)
{
    Code.clear();
    vector<float>::const_iterator it;
    for(it = Pos.begin();it != Pos.end();it++)
    {
        Code.push_back((unsigned short)((180 * (*it) / 3.14) / 0.24 + 500));
    }
    Code.at(2) = 1000 - Code.at(2);//因为第四个舵机读数是反的
}

void KakaProtocal::GripperPostoCode(const float &Pos, unsigned short &Code)
{
    Code = (unsigned short)Pos;
}

void KakaProtocal::GripperCodetoPos(float &Pos, const unsigned short &Code)
{
    Pos = (float)Code;
}

int KakaProtocal::DecodeReadData(const vector<unsigned char> &Data,vector<unsigned short> &JointFBCode, unsigned short &GripperFBCode)
{
    if(Data.size() == 23)
    {
        JointFBCode.clear();
        if (Data.at(0) == 0x55 && Data.at(1) == 0x55)
        {
            if (Data.at(2) == 0x15)
            {
                if (Data.at(3) == 0x15)
                {
                    short JointPos1 = 0;
                    short JointPos2 = 0;
                    short JointPos3 = 0;
                    short JointPos4 = 0;
                    short JointPos5 = 0;
                    GripperFBCode = (short) ((Data.at(6)) | (Data.at(7)) << 8);
                    JointPos1 = (short) ((Data.at(9)) | (Data.at(10)) << 8);
                    JointPos2 = (short) ((Data.at(12)) | (Data.at(13)) << 8);
                    JointPos3 = (short) ((Data.at(15)) | (Data.at(16)) << 8);
                    JointPos4 = (short) ((Data.at(18)) | (Data.at(19)) << 8);
                    JointPos5 = (short) ((Data.at(21)) | (Data.at(22)) << 8);
                    JointFBCode.clear();
                    JointFBCode.push_back(JointPos1);
                    JointFBCode.push_back(JointPos2);
                    JointFBCode.push_back(JointPos3);
                    JointFBCode.push_back(JointPos4);
                    JointFBCode.push_back(JointPos5);
                    return 0;
                }else{return -1;};
            }else{return -2;}
        } else{return -3;}
    } else{return -4;}
}

void KakaProtocal::CreatSendCmd(CMD_TYPE Cmd,vector<unsigned char> &SendCmd,vector<unsigned short> TarCode, unsigned short RunTime)
{
    SendCmd.clear();
    switch(Cmd)
    {
        case GET_ALL_POS://格式比较固定
            SendCmd.push_back(0x55);
            SendCmd.push_back(0x55);//帧头
            SendCmd.push_back(0x09);//数据长度
            SendCmd.push_back(0x15);//指令
            SendCmd.push_back(0x06);//参数
            SendCmd.push_back(0x01);
            SendCmd.push_back(0x02);
            SendCmd.push_back(0x03);
            SendCmd.push_back(0x04);
            SendCmd.push_back(0x05);
            SendCmd.push_back(0x06);
            break;
        case SEND_ALL_JPINT_POS:
            SendCmd.push_back(0x55);
            SendCmd.push_back(0x55);//帧头
            SendCmd.push_back(0x14);//数据长度
            SendCmd.push_back(0x03);//指令
            SendCmd.push_back(0x05);//舵机个数
            SendCmd.push_back((RunTime)&0xFF);
            SendCmd.push_back((RunTime>>8)&0xFF);//时间
            if(TarCode.size() == 5)
            {
                unsigned short TarCodeTmp;
                vector<unsigned short>::iterator it;
                char i = 2;
                for(it = TarCode.begin();it != TarCode.end();it++)
                {
                    TarCodeTmp = (unsigned short)(*it);
                    SendCmd.push_back(i);
                    SendCmd.push_back((TarCodeTmp)&0xFF);
                    SendCmd.push_back((TarCodeTmp>>8)&0xFF);
                    i++;
                }
            }
            break;
        case SEND_GRIPPER_POS:
            SendCmd.push_back(0x55);
            SendCmd.push_back(0x55);//帧头
            SendCmd.push_back(0x08);//数据长度
            SendCmd.push_back(0x03);//指令
            SendCmd.push_back(0x01);//舵机个数
            SendCmd.push_back((RunTime)&0xFF);
            SendCmd.push_back((RunTime>>8)&0xFF);//时间
            if(TarCode.size() == 1)
            {
                unsigned short TarCodeTmp;
                TarCodeTmp = TarCode.at(0);
                SendCmd.push_back(0x01);
                SendCmd.push_back((TarCodeTmp)&0xFF);
                SendCmd.push_back((TarCodeTmp>>8)&0xFF);
            }
            break;
        default:
            break;
    }
}