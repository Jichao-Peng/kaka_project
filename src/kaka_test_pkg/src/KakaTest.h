//
// Created by leo on 18-5-2.
//

#ifndef PROJECT_KAKATEST_H
#define PROJECT_KAKATEST_H

#include <ros/ros.h>
#include <Eigen/Dense>
#include <visualization_msgs/Marker.h>
#include <kaka_vision_pkg/VisionMsg.h>

class KakaTest
{
public:
    KakaTest();
    ~KakaTest();
    void Run();

private:
    ros::NodeHandle Node;
    ros::Publisher MarkerPub;
    ros::Publisher VisionResultPub;

    void SendResult();
    void CreatMarker(const Eigen::Vector3d &StartPoint, const Eigen::Vector3d &Vector, visualization_msgs::Marker &Marker,int ID);

};


#endif //PROJECT_KAKATEST_H
