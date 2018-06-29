//
// Created by leo on 18-4-11.
//

#ifndef PROJECT_KAKACLOUDMETHOD_H
#define PROJECT_KAKACLOUDMETHOD_H

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/sample_consensus/sac_model_sphere.h>
#include <pcl/segmentation/sac_segmentation.h>

class KakaCloudMethod
{
public:

////离散点过滤
    void StatisticalOutlierRemovalFilter(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,
                                         pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_out);


////点云数据采样，减少点云数据量
    void VoxelGridFilter(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,
                         pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_out,
                         float sampling_distance = 0.001);

////平面拟合,返回平面法向量以及拟合的平面点云
    void PlaneFitting(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,
                      pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_out,
                      Eigen::Vector3d& normal,
                      float plane_distance = 0.001);

////区域生长分割
    void RegionGrowingSegmentation(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud_in,
                                   std::vector<pcl::PointIndices>& clusters);

////移除大平面
    void RemoveDesktop(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in,
                       pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out);

};


#endif //PROJECT_KAKACLOUDMETHOD_H
