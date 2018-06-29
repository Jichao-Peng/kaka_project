//
// Created by leo on 18-4-11.
//

#include "KakaVision.h"

//RealSense标定结果
//606.678568 0.000000   324.123102
//0.000000   608.676854 232.570872
//0.000000   0.000000   1.000000
//width = 640；
//height = 480；

//xtion标定结果
//540.134058 0.000000 318.776150
//0.000000 541.550437 231.759493
//0.000000 0.000000 1.000000


//深度图节点   /camera/depth/image_raw
//彩色图节点   /camera/rgb/image_raw

KakaVision::KakaVision(string ColorTopic,string DepthTopic):
    ColorSub(Node,ColorTopic,1),
    DepthSub(Node,DepthTopic,1),
    Synchronizer(ColorSub,DepthSub,10)
{
    Synchronizer.registerCallback(boost::bind(&KakaVision::ColorDepthCallBack,this,_1,_2));
    CloudPub = Node.advertise<sensor_msgs::PointCloud2>("output",1);
    MarkerPub = Node.advertise<visualization_msgs::Marker>("visualization_marker",1);
    VisionResultPub = Node.advertise<kaka_vision_pkg::VisionMsg>("/vision_result",1);
    CloudMethod = new KakaCloudMethod;
    Coordinate = new  KakaCoordinate;

    //暂时先直接参数初始话，后期可以改成读xml文件来实现
    CloudTransform = new KakaCloudTransform(1/606.678568f, 1/608.676854f, 324.123102f, 232.570872f, 640, 480);
    //CloudTransform = new KakaCloudTransform(1/540.134058f, 1/541.550437f, 318.776150f, 231.759493f, 640, 480);

}

KakaVision::~KakaVision()
{
    delete CloudMethod;
}

void KakaVision::ColorDepthCallBack(const sensor_msgs::ImageConstPtr &ColorMsg, const sensor_msgs::ImageConstPtr &DepthMsg)
{
    //根据彩色图和深度图生成点云
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudCreat(new pcl::PointCloud<pcl::PointXYZRGB>);
    cv::Mat Color = cv_bridge::toCvCopy(ColorMsg, sensor_msgs::image_encodings::TYPE_8UC3)->image;
    cv::Mat Depth = cv_bridge::toCvCopy(DepthMsg, sensor_msgs::image_encodings::TYPE_16UC1)->image;
    if ((!Color.empty()) && (!Depth.empty()))
    {
        CloudCreat->height = Color.rows;
        CloudCreat->width = Color.cols;
        CloudCreat->is_dense = false;
        CloudCreat->points.resize(CloudCreat->height * CloudCreat->width);
        CloudCreat->header.frame_id = "camera_depth_frame";
        CloudTransform->createCloud(Depth, Color, CloudCreat);
    }

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudGrid(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudROI(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudPlane(new pcl::PointCloud<pcl::PointXYZRGB>);

    std::vector<pcl::PointIndices> Clusters;


    //过滤掉离群点
    CloudMethod->StatisticalOutlierRemovalFilter(CloudCreat, CloudFiltered);

    //网格化
    CloudMethod->VoxelGridFilter(CloudFiltered, CloudGrid);

    //去除桌面
    CloudMethod->RemoveDesktop(CloudGrid, CloudROI);

    //区域生长分割
    CloudMethod->RegionGrowingSegmentation(CloudROI, Clusters);


    if (Clusters.empty())
    {
        ROS_INFO("[KAKA_VISION] No Target Detected!");
    } else
    {
        //因为分割出来会有两个平面，取点数较多的平面肯定是上平面，这个算法不鲁棒，简单地先这样，之后再改
        std::sort(Clusters.begin(), Clusters.end(), KakaVision::ChoosePlane);

        //提取点数最大的平面的法向量
        pcl::copyPointCloud(*CloudROI, Clusters[0], *CloudPlane);

        //主成分分析求物体坐标系
        Eigen::Vector4f PCACentroid;
        pcl::compute3DCentroid(*CloudPlane, PCACentroid);//计算点云中心
        Eigen::Matrix3f Convariace;
        pcl::computeCovarianceMatrixNormalized(*CloudPlane, PCACentroid, Convariace);//点云标准化
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> EigenSolver(Convariace, Eigen::ComputeEigenvectors);
        Eigen::Matrix3f PCAVectors = EigenSolver.eigenvectors();//主成分分析
        PCAVectors(0, 1) = -PCAVectors(0, 1);
        PCAVectors(1, 1) = -PCAVectors(1, 1);
        PCAVectors(2, 1) = -PCAVectors(2, 1);
        if (PCAVectors(2, 0) > 0)
        {
            PCAVectors.col(2) = PCAVectors.col(0).cross(PCAVectors.col(1));
        } else
        {
            PCAVectors(2, 0) = -PCAVectors(2, 0);
            PCAVectors(1, 0) = -PCAVectors(1, 0);
            PCAVectors(0, 0) = -PCAVectors(0, 0);
            PCAVectors.col(2) = PCAVectors.col(0).cross(PCAVectors.col(1));
        }//使Z轴永远朝一个方向
        PCAVectors(0, 2) = -PCAVectors(0, 2);
        PCAVectors(1, 2) = -PCAVectors(1, 2);
        PCAVectors(2, 2) = -PCAVectors(2, 2);

        //求出姿态和位置在基座坐标系中的表示
        Eigen::Vector3d PositionInCamera, PositionInBase;
        Eigen::Vector4d QuatInBase;
        Eigen::Matrix3d PoseInBase;
        Eigen::Quaterniond Quaternion;
        //坐标
        PositionInCamera(0) = PCACentroid[0] * 1000;
        PositionInCamera(1) = PCACentroid[1] * 1000;
        PositionInCamera(2) = PCACentroid[2] * 1000;
        PositionInBase = Coordinate->TransformPointFromCam2Base(PositionInCamera);
        //姿态
        //用物体坐标系的姿态
        //        PoseInBase.col(0) = Coordinate->TransformVectorFromCam2Base(PCAVectors.col(2).cast<double>());//X轴
        //        PoseInBase.col(1) = Coordinate->TransformVectorFromCam2Base(PCAVectors.col(1).cast<double>());//Y轴
        //        PoseInBase.col(2) = Coordinate->TransformVectorFromCam2Base(PCAVectors.col(0).cast<double>());//Z轴
        //用坐标计算出来的姿态
        Eigen::Vector3d VectorXInBase, VectorYInBase, VectorZInBase;
        VectorXInBase(0) = -PositionInBase(0);
        VectorXInBase(1) = -PositionInBase(1);
        VectorXInBase.normalize();
        VectorXInBase(0) = VectorXInBase(0) * 0.8;
        VectorXInBase(1) = VectorXInBase(1) * 0.8;
        VectorXInBase(2) = -0.6;

        VectorZInBase(0) = PositionInBase(0);
        VectorZInBase(1) = PositionInBase(1);
        VectorZInBase.normalize();
        VectorZInBase(0) = VectorZInBase(0) * 0.6;
        VectorZInBase(1) = VectorZInBase(1) * 0.6;
        VectorZInBase(2) = -0.8;

        VectorYInBase = VectorZInBase.cross(VectorXInBase);
        PoseInBase.col(0) = VectorXInBase;
        PoseInBase.col(1) = VectorYInBase;
        PoseInBase.col(2) = VectorZInBase;

        Quaternion = PoseInBase;
        QuatInBase = Quaternion.coeffs();


//                ROS_INFO("[KAKA_VISION]");
//                ROS_INFO("Position in Base:");
//                ROS_INFO("     %f", PositionInBase(0)/1000);
//                ROS_INFO("     %f", PositionInBase(1)/1000);
//                ROS_INFO("     %f", PositionInBase(2)/1000);
        //        ROS_INFO("X in Base:");
        //        ROS_INFO("     %f", PoseInBase(0,0));
        //        ROS_INFO("     %f", PoseInBase(1,0));
        //        ROS_INFO("     %f", PoseInBase(2,0));
        //        ROS_INFO("Y in Base:");
        //        ROS_INFO("     %f", PoseInBase(0,1));
        //        ROS_INFO("     %f", PoseInBase(1,1));
        //        ROS_INFO("     %f", PoseInBase(2,1));
        //        ROS_INFO("Z in Base:");
        //        ROS_INFO("     %f", PoseInBase(0,2));
        //        ROS_INFO("     %f", PoseInBase(1,2));
        //        ROS_INFO("     %f", PoseInBase(2,2));
        //        ROS_INFO("Q in Base:");
//                ROS_INFO("     %f", Quaternion.x());
//                ROS_INFO("     %f", Quaternion.y());
//                ROS_INFO("     %f", Quaternion.z());
//                ROS_INFO("     %f", Quaternion.w());
//                ROS_INFO(" ");

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
        //发布给点云
        //        CreatMarker(PCACentroid,PCAVectors.col(0),ArrowXMark,0);
        //        CreatMarker(PCACentroid,PCAVectors.col(1),ArrowYMark,1);
        //        CreatMarker(PCACentroid,PCAVectors.col(2),ArrowZMark,2);
        MarkerPub.publish(ArrowXMark);
        MarkerPub.publish(ArrowYMark);
        MarkerPub.publish(ArrowZMark);
    }

    //ROS_INFO("Size: %d",(int)Clusters.size());

    if (CloudPlane->empty())
    {
        ROS_INFO("[KAKA_VISION] No Plane Exist");
    }

    sensor_msgs::PointCloud2 CloudOutput;
    pcl::toROSMsg(*CloudGrid, CloudOutput);
    CloudPub.publish(CloudOutput);
}

//发布给moviet
void KakaVision::CreatMarker(const Eigen::Vector3d &StartPoint, const Eigen::Vector3d &Vector, visualization_msgs::Marker &Marker, int ID)
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

//发布给点云
void KakaVision::CreatMarker(const Eigen::Vector4f &StartPoint, const Eigen::Vector3f &Vector, visualization_msgs::Marker &Marker, int ID)
{
    Marker.header.frame_id = "camera_depth_frame";
    Marker.header.stamp = ros::Time::now();
    Marker.id = ID;
    Marker.type = visualization_msgs::Marker::ARROW;
    Marker.action = visualization_msgs::Marker::ADD;

    geometry_msgs::Point PointA,PointB;
    PointA.x = StartPoint[0];
    PointA.y = StartPoint[1];
    PointA.z = StartPoint[2];
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
    ros::init(argc,argv,"kaka_vision");
    KakaVision KakaVision("/camera/rgb/image_raw","/camera/depth_registered/sw_registered/image_rect_raw");
    ros::spin();
    return 0;
}
