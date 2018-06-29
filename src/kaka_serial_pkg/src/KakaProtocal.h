//
// Created by leo on 18-3-17.
//

#ifndef PROJECT_KAKAPROTOCAL_H
#define PROJECT_KAKAPROTOCAL_H

#include <vector>

using namespace std;

typedef enum
{
    GET_ALL_POS,
    SEND_ALL_JPINT_POS,
    SEND_GRIPPER_POS
}CMD_TYPE;


class KakaProtocal
{
public:
    void PostoCode(const vector<float> &Pos,vector<unsigned short> &Code);
    void CodetoPos(vector<float> &Pos,const vector<unsigned short> &Code);
    void GripperPostoCode(const float &Pos, unsigned short &Code);
    void GripperCodetoPos(float &Pos, const unsigned short &Code);
    int DecodeReadData(const vector<unsigned char> &Data,vector<unsigned short> &FBCode, unsigned short &GripperFBCode);
    void CreatSendCmd(CMD_TYPE Cmd,vector<unsigned char> &SendCmd,vector<unsigned short> TarCode = vector<unsigned short>(), unsigned short RunTime = 0);
};


#endif //PROJECT_KAKAPROTOCAL_H
