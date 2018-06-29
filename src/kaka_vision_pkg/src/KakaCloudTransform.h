//
// Created by leo on 18-4-13.
//

#ifndef PROJECT_KAKACLOUDTRANSFORM_H
#define PROJECT_KAKACLOUDTRANSFORM_H

#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

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
#include <boost/thread/thread.hpp>


class KakaCloudTransform {
public:
    KakaCloudTransform();

    KakaCloudTransform(cv::Mat camMatrixColor, int width, int height);

    KakaCloudTransform(float fX, float fY, float cX, float cY, int width, int height);

    ~KakaCloudTransform();

    void createLookup();

    void createCloud(const cv::Mat& depth, const cv::Mat& color,
                     pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud);

    void createCloud(const cv::Mat& depth,
                     pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud);

    //深度图转点云数据
    void createCloud(const cv::Mat& depth,
                     pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);

    //点云数据转成图像
    void cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud,
                     pcl::PointIndices pointIndices, cv::Mat& thred);

    //点云数据转成图像,先设置图像大小
    void cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud,
                     cv::Mat& thred);

    //点云数据转成图像,先设置图像大小
    void cloud2Image(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud,
                     cv::Mat& thred);

    void cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud,
                     pcl::PointIndices pointIndices,
                     cv::Mat& thred,
                     cv::Mat& depth);

private:

    cv::Mat lookupX, lookupY;
    float fx, fy, cx, cy;//相机内参
    int width;
    int height;
};


#endif //PROJECT_KAKACLOUDTRANSFORM_H
