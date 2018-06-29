//
// Created by leo on 18-4-11.
//

#ifndef PROJECT_KAKAVISION_H
#define PROJECT_KAKAVISION_H

#include <string>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>
#include <visualization_msgs/Marker.h>
#include <kaka_vision_pkg/VisionMsg.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/common.h>
#include <pcl/common/centroid.h>
#include <pcl/common/distances.h>
#include <pcl/common/intersections.h>
#include <pcl/common/io.h>
#include <pcl/common/eigen.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/features/feature.h>
#include <gtest/gtest.h>

#include "KakaCloudMethod.h"
#include "KakaCloudTransform.h"
#include "KakaCoordinate.h"

using namespace std;

typedef struct
{
    Eigen::Vector3d Pose;
    pcl::PointXYZ Position;
    float Score;
}TARGET;

class KakaVision
{
public:
    KakaVision(string ColorTopic, string DepthTopic);

    ~KakaVision();

private:
    ros::NodeHandle Node;
    //ros::Subscriber CloudSub;

    message_filters::Subscriber<sensor_msgs::Image> ColorSub;
    message_filters::Subscriber<sensor_msgs::Image> DepthSub;
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> Synchronizer;
    ros::Publisher CloudPub;
    ros::Publisher MarkerPub;
    ros::Publisher VisionResultPub;

    KakaCloudMethod *CloudMethod;
    KakaCloudTransform *CloudTransform;
    KakaCoordinate *Coordinate;

    void ColorDepthCallBack(const sensor_msgs::ImageConstPtr &ColorMsg, const sensor_msgs::ImageConstPtr &DepthMsg);

    void CreatMarker(const Eigen::Vector3d &StartPoint, const Eigen::Vector3d &Vector, visualization_msgs::Marker &Marker,int ID);
    void CreatMarker(const Eigen::Vector4f &StartPoint, const Eigen::Vector3f &Vector, visualization_msgs::Marker &Marker,int ID);
    static bool ChoosePlane(const pcl::PointIndices &Points1, const pcl::PointIndices &Points2)
    {
        return Points1.indices.size() > Points2.indices.size();
    }

};



#endif //PROJECT_KAKAVISION_H
