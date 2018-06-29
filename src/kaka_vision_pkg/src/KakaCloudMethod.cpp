//
// Created by leo on 18-4-11.
//

#include "KakaCloudMethod.h"

////离散点过滤
void KakaCloudMethod::StatisticalOutlierRemovalFilter(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                                                      pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_out)
{
    // Create the filtering object
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> Filter;
    Filter.setInputCloud(cloud_in);
    Filter.setMeanK(50);
    Filter.setStddevMulThresh(1);//值越小过滤越明显
    // sor.setNegative (true);//过滤集中点，保留离散点
    Filter.filter(*cloud_out);
}

////点云数据采样，减少点云数据量
void KakaCloudMethod::VoxelGridFilter(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                                      pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_out, float sampling_distance)
{
    // Create the filtering object
    pcl::VoxelGrid<pcl::PointXYZRGB> Filter;
    Filter.setInputCloud(cloud_in);
    Filter.setLeafSize(sampling_distance, sampling_distance, sampling_distance);
    Filter.filter(*cloud_out);
}


////平面拟合,返回平面法向量以及拟合的平面点云
void KakaCloudMethod::PlaneFitting(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,
                  pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_out,
                  Eigen::Vector3d &normal,
                  float plane_distance)
{
    std::vector<int> inliers;

    // created RandomSampleConsensus object and compute the appropriated model
    //采样一致性算法拟合平面
    pcl::SampleConsensusModelPlane<pcl::PointXYZRGB>::Ptr model_p(new pcl::SampleConsensusModelPlane<pcl::PointXYZRGB>(cloud_in));
    pcl::RandomSampleConsensus<pcl::PointXYZRGB> ransac(model_p);
    ransac.setDistanceThreshold(plane_distance);
    ransac.computeModel();
    ransac.getInliers(inliers);

    Eigen::VectorXf model_coeff;
    ransac.getModelCoefficients(model_coeff);
    //法向量朝向Ｚ轴正方向
    if (model_coeff[2] < 0) {
        model_coeff = -model_coeff;
    }

    // copies all inliers of the model computed to another PointCloud
    pcl::copyPointCloud<pcl::PointXYZRGB>(*cloud_in, inliers, *cloud_out);

    normal[0] = model_coeff[0];
    normal[1] = model_coeff[1];
    normal[2] = model_coeff[2];
}

////区域生长分割
void KakaCloudMethod::RegionGrowingSegmentation(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,std::vector<pcl::PointIndices> &clusters)
{
    pcl::search::Search<pcl::PointXYZRGB>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZRGB> >(new pcl::search::KdTree<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);

    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> normal_estimator;
    normal_estimator.setSearchMethod(tree);
    normal_estimator.setInputCloud(cloud_in);
    normal_estimator.setKSearch(50);
    normal_estimator.compute(*normals);

    pcl::RegionGrowing<pcl::PointXYZRGB, pcl::Normal> reg;
    reg.setMinClusterSize(50);
    reg.setMaxClusterSize(1000000);
    reg.setSearchMethod(tree);
    reg.setNumberOfNeighbours(30);
    reg.setInputCloud(cloud_in);
    reg.setInputNormals(normals);
    reg.setSmoothnessThreshold(3.5 / 180.0 * M_PI); //允许3.5度偏差，根据点云质量调整
    reg.setCurvatureThreshold(1.0);
    reg.extract(clusters);
}

////移除平面
void KakaCloudMethod::RemoveDesktop(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in,
                                    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out)
{
    //平面分割，获得平面模型
    pcl::ModelCoefficients::Ptr Coeffiecients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr Inliers(new pcl::PointIndices);
    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.01);
    seg.setInputCloud(cloud_in);
    seg.segment(*Inliers,*Coeffiecients);

    //从输入点云中提取平面模型的内点
    pcl::ExtractIndices<pcl::PointXYZRGB> eis;
    eis.setInputCloud(cloud_in);
    eis.setIndices(Inliers);
    eis.setNegative(true);
    eis.filter(*cloud_out);
}
