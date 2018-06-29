//
// Created by leo on 18-5-2.
//

#include "KakaTest.h"

KakaTest::KakaTest()
{
    MarkerPub = Node.advertise<visualization_msgs::Marker>("visualization_marker",1);
    VisionResultPub = Node.advertise<kaka_vision_pkg::VisionMsg>("/vision_result",1);
}

KakaTest::~KakaTest()
{

}

void KakaTest::Run()
{
    ros::Rate Rate(1);
    while (ros::ok())
    {
        Rate.sleep();
        ros::spinOnce();
        SendResult();
    }
}

void KakaTest::SendResult()
{
    //用坐标计算出来的姿态
    Eigen::Matrix3d PoseInBase;
    Eigen::Vector3d PositionInBase;
    Eigen::Vector3d VectorXInBase, VectorYInBase, VectorZInBase;
    Eigen::Quaterniond Quaternion;
    Eigen::Vector4d QuatInBase;

    PositionInBase(0) = 20.087286;
    PositionInBase(1) = 50.848721;
    PositionInBase(2) = 100.863286;

//    PositionInBase(0) = 100;
//    PositionInBase(1) = 0;
//    PositionInBase(2) = 140;


    VectorXInBase(0) = -PositionInBase(0);
    VectorXInBase(1) = -PositionInBase(1);
    VectorXInBase.normalize();
    VectorXInBase(0) = VectorXInBase(0) * 0.6;
    VectorXInBase(1) = VectorXInBase(1) * 0.6;
    VectorXInBase(2) = -0.8;

    VectorZInBase(0) = PositionInBase(0);
    VectorZInBase(1) = PositionInBase(1);
    VectorZInBase.normalize();
    VectorZInBase(0) = VectorZInBase(0) * 0.8;
    VectorZInBase(1) = VectorZInBase(1) * 0.8;
    VectorZInBase(2) = -0.6;

    VectorYInBase = VectorZInBase.cross(VectorXInBase);
    PoseInBase.col(0) = VectorXInBase;
    PoseInBase.col(1) = VectorYInBase;
    PoseInBase.col(2) = VectorZInBase;

    Quaternion = PoseInBase;
    QuatInBase = Quaternion.coeffs();


//    ROS_INFO("[KAKA_VISION]");
//    ROS_INFO("Position in Base:");
//    ROS_INFO("px     %f", PositionInBase(0)/1000);
//    ROS_INFO("py     %f", PositionInBase(1)/1000);
//    ROS_INFO("pz     %f", PositionInBase(2)/1000);
//    ROS_INFO("vx     %f", VectorXInBase(0));
//    ROS_INFO("vx     %f", VectorXInBase(1));
//    ROS_INFO("vx     %f", VectorXInBase(2));
//    ROS_INFO("vy     %f", VectorYInBase(0));
//    ROS_INFO("vy     %f", VectorYInBase(1));
//    ROS_INFO("vy     %f", VectorYInBase(2));
//    ROS_INFO("vz     %f", VectorZInBase(0));
//    ROS_INFO("vz     %f", VectorZInBase(1));
//    ROS_INFO("vz     %f", VectorZInBase(2));
//    ROS_INFO("qx     %f", Quaternion.x());
//    ROS_INFO("qy     %f", Quaternion.y());
//    ROS_INFO("qz     %f", Quaternion.z());
//    ROS_INFO("qw     %f", Quaternion.w());
//    ROS_INFO(" ");

    //发布视觉结果
    kaka_vision_pkg::VisionMsg VisionResult;
    VisionResult.Quaternion.push_back(QuatInBase(0));
    VisionResult.Quaternion.push_back(QuatInBase(1));
    VisionResult.Quaternion.push_back(QuatInBase(2));
    VisionResult.Quaternion.push_back(QuatInBase(3));
    VisionResult.Position.push_back(PositionInBase(0));
    VisionResult.Position.push_back(PositionInBase(1));
    VisionResult.Position.push_back(PositionInBase(2));
    VisionResultPub.publish(VisionResult);

    //发布Marker
    //
    //根据发布的Marker可得col(0)为垂直于平面的法向量，col（1）为短轴方向，col（2）为长轴方向
    //因此我们应该把短轴作为Y，长轴作为X，法向量作为Z
    visualization_msgs::Marker ArrowXMark, ArrowYMark, ArrowZMark;
    //发布给moviet
    CreatMarker(PositionInBase, PoseInBase.col(0), ArrowXMark, 0);
    CreatMarker(PositionInBase, PoseInBase.col(1), ArrowYMark, 1);
    CreatMarker(PositionInBase, PoseInBase.col(2), ArrowZMark, 2);
    MarkerPub.publish(ArrowXMark);
    MarkerPub.publish(ArrowYMark);
    MarkerPub.publish(ArrowZMark);
}

//发布给moviet
void KakaTest::CreatMarker(const Eigen::Vector3d &StartPoint, const Eigen::Vector3d &Vector, visualization_msgs::Marker &Marker, int ID)
{
    Marker.header.frame_id = "base_link";
    Marker.header.stamp = ros::Time::now();
    Marker.id = ID;
    Marker.type = visualization_msgs::Marker::ARROW;
    Marker.action = visualization_msgs::Marker::ADD;

    geometry_msgs::Point PointA,PointB;
    PointA.x = StartPoint[0]/1000;
    PointA.y = StartPoint[1]/1000;
    PointA.z = StartPoint[2]/1000;
    Marker.points.push_back(PointA);

    PointB.x = PointA.x+Vector[0]*0.1;
    PointB.y = PointA.y+Vector[1]*0.1;
    PointB.z = PointA.z+Vector[2]*0.1;
    Marker.points.push_back(PointB);

    Marker.scale.x = 0.01;
    Marker.scale.y = 0.02;
    Marker.scale.z = 0;
    Marker.color.a = 1;


    int ColorID = ID%3;
    if(ColorID == 0)
    {
        Marker.color.g = 0;
        Marker.color.b = 0;
        Marker.color.r = 1;
    }
    else if(ColorID == 1)
    {
        Marker.color.g = 1;
        Marker.color.b = 0;
        Marker.color.r = 0;
    }
    else if(ColorID == 2)
    {
        Marker.color.g = 0;
        Marker.color.b = 1;
        Marker.color.r = 0;
    }
    else
    {}
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"kaka_test");
    KakaTest KakaTest;
    KakaTest.Run();
    return 0;
}
