//
// Created by leo on 18-4-13.
//

#include "KakaCloudTransform.h"


KakaCloudTransform::KakaCloudTransform()
{

}

//构造函数读入内参矩阵
KakaCloudTransform::KakaCloudTransform(cv::Mat camMatrixColor, int width, int height)
{
    fx = 1.0f / camMatrixColor.at<float>(0, 0);
    fy = 1.0f / camMatrixColor.at<float>(1, 1);
    cx = camMatrixColor.at<float>(0, 2);
    cy = camMatrixColor.at<float>(1, 2);

    this->width = width;
    this->height = height;

    createLookup();
}

//构造函数读入内参矩阵
KakaCloudTransform::KakaCloudTransform(float fX, float fY, float cX, float cY, int width, int height) : fx(fX), fy(fY),
                                                                                                      cx(cX), cy(cY)
{
    this->width = width;
    this->height = height;
    std::cout<<"fx:     "<<fx<<std::endl;
    std::cout<<"fy:     "<<fy<<std::endl;
    std::cout<<"cx:     "<<cx<<std::endl;
    std::cout<<"cy:     "<<cy<<std::endl;
    std::cout<<"width:  "<<width<<std::endl;
    std::cout<<"height: "<<height<<std::endl;
    createLookup();
}

KakaCloudTransform::~KakaCloudTransform()
{

}

//根据内参矩阵创建一个Lookup矩阵，这个矩阵在后面转换中会用到
void KakaCloudTransform::createLookup()
{
    float *it;
    lookupY = cv::Mat(1, height, CV_32F);
    it = lookupY.ptr<float>();
    for (size_t r = 0; r < height; ++r, ++it)
    {
        *it = (r - cy) * fy;
    }

    lookupX = cv::Mat(1, width, CV_32F);
    it = lookupX.ptr<float>();
    for (size_t c = 0; c < width; ++c, ++it)
    {
        *it = (c - cx) * fx;
    }
}

//深度彩色图转点云数据，输入深度和彩色图，输出点云图，中间采用Openmp多线程加速
void KakaCloudTransform::createCloud(const cv::Mat &depth, const cv::Mat &color,
                                     pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    float badPoint = std::numeric_limits<float>::quiet_NaN();

#pragma omp parallel for
    for (int r = 0; r < depth.rows; ++r)
    {
        pcl::PointXYZRGB *itP = &cloud->points[r * depth.cols];
        const uint16_t *itD = depth.ptr<uint16_t>(r);
        const cv::Vec3b *itC = color.ptr<cv::Vec3b>(r);
        const float y = lookupY.at<float>(0, r);
        const float *itX = lookupX.ptr<float>();

        for (size_t c = 0; c < (size_t) depth.cols; ++c, ++itP, ++itD, ++itC, ++itX)
        {
            register const float depthValue = *itD / 1000.0f;
             //Check for invalid measurements
            if (*itD == 0)
            {
                // not valid
                itP->x = itP->y = itP->z = badPoint;
                //itP->rgb = 0;
                continue;
            }
            itP->z = depthValue;
            itP->x = *itX * depthValue;
            itP->y = y * depthValue;
            itP->b = itC->val[2];
            itP->g = itC->val[1];
            itP->r = itC->val[0];
        }
    }
}

//深度图转点云数据
void KakaCloudTransform::createCloud(const cv::Mat &depth, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud)
{
    const float badPoint = std::numeric_limits<float>::quiet_NaN();

#pragma omp parallel for
    for (int r = 0; r < depth.rows; ++r)
    {
        pcl::PointXYZRGB *itP = &cloud->points[r * depth.cols];
        const uint16_t *itD = depth.ptr<uint16_t>(r);
        const float y = lookupY.at<float>(0, r);
        const float *itX = lookupX.ptr<float>();

        for (size_t c = 0; c < (size_t) depth.cols; ++c, ++itP, ++itD, ++itX)
        {
            register const float depthValue = *itD / 1000.0f;
            // Check for invalid measurements
            if (*itD == 0)
            {
                // not valid
                itP->x = itP->y = itP->z = badPoint;
                //itP->rgb = 0;
                continue;
            }
            itP->z = depthValue;
            itP->x = *itX * depthValue;
            itP->y = y * depthValue;
            itP->b = 0;
            itP->g = 255;
            itP->r = 0;
        }
    }
}

//深度图转点云数据
void KakaCloudTransform::createCloud(const cv::Mat &depth, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
    const float badPoint = std::numeric_limits<float>::quiet_NaN();

#pragma omp parallel for
    for (int r = 0; r < depth.rows; ++r)
    {
        pcl::PointXYZ *itP = &cloud->points[r * depth.cols];
        const uint16_t *itD = depth.ptr<uint16_t>(r);
        const float y = lookupY.at<float>(0, r);
        const float *itX = lookupX.ptr<float>();

        for (size_t c = 0; c < (size_t) depth.cols; ++c, ++itP, ++itD, ++itX)
        {
            register const float depthValue = *itD / 1000.0f;
            // Check for invalid measurements
            if (*itD == 0)
            {
                // not valid
                itP->x = itP->y = itP->z = badPoint;
                continue;
            }
            itP->z = depthValue;
            itP->x = *itX * depthValue;
            itP->y = y * depthValue;
        }
    }
}

//点云数据转成图像
void KakaCloudTransform::cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud, pcl::PointIndices pointIndices,
                                cv::Mat &thred)
{

    if (cloud->empty() || thred.empty())
    {
        std::cerr << "cloud2Image: NULL ptr error!" << std::endl;
        return;
    }
#pragma omp parallel for
    for (size_t i = 0; i < pointIndices.indices.size(); i++)
    {
        cv::Point pt;
        pcl::PointXYZRGB point = cloud->points[pointIndices.indices[i]];
        if (isnan(point.x) || isnan(point.y) || isnan(point.z))
        {
            continue;
        }
        pt.x = (point.x / point.z) / fx + cx;
        pt.y = (point.y / point.z) / fy + cy;

        cv::circle(thred, pt, 1, cv::Scalar(255), 2);

    }
}


//点云数据转成图像,先设置图像大小
void KakaCloudTransform::cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud, cv::Mat &thred)
{
    if (cloud->empty() || thred.empty())
    {
        std::cerr << "cloud2Image: NULL ptr error!" << std::endl;
        return;
    }

#pragma omp parallel for
    for (size_t i = 0; i < cloud->points.size(); i++)
    {
        cv::Point pt;
        pcl::PointXYZRGB point = cloud->points[i];
        if (isnan(point.x) || isnan(point.y) || isnan(point.z))
        {
            cv::circle(thred, pt, 1, cv::Scalar(0), 1);
            continue;
        }
        if (point.x == 0 && point.y == 0 && point.z == 0)
        {
            cv::circle(thred, pt, 1, cv::Scalar(0), 1);
            continue;
        }
        pt.x = (point.x / point.z) / fx + cx;
        pt.y = (point.y / point.z) / fy + cy;

        cv::circle(thred, pt, 1, cv::Scalar(255), 1);
    }
}

//点云数据转成图像,先设置图像大小
void KakaCloudTransform::cloud2Image(const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                                     cv::Mat &thred)
{

    if (cloud->empty() || thred.empty())
    {
        std::cerr << "cloud2Image: NULL ptr error!" << std::endl;
        return;
    }

#pragma omp parallel for
    for (size_t i = 0; i < cloud->points.size(); i++)
    {
        cv::Point pt;
        pcl::PointXYZ point = cloud->points[i];
        if (isnan(point.x) || isnan(point.y) || isnan(point.z))
        {
            cv::circle(thred, pt, 1, cv::Scalar(0), 1);
            continue;
        }
        if (point.x == 0 && point.y == 0 && point.z == 0)
        {
            cv::circle(thred, pt, 1, cv::Scalar(0), 1);
            continue;
        }
        pt.x = (point.x / point.z) / fx + cx;
        pt.y = (point.y / point.z) / fy + cy;

        cv::circle(thred, pt, 1, cv::Scalar(255), 1);
    }
}

//点云数据转成图像
void KakaCloudTransform::cloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud,
                                     pcl::PointIndices pointIndices, cv::Mat &thred, cv::Mat &depth)
{

    if (cloud->empty() || thred.empty())
    {
        std::cerr << "cloud2Image: NULL ptr error!" << std::endl;
        return;
    }
#pragma omp parallel for
    for (size_t i = 0; i < pointIndices.indices.size(); i++)
    {
        cv::Point pt;
        pcl::PointXYZRGB point = cloud->points[pointIndices.indices[i]];
        if (isnan(point.x) || isnan(point.y) || isnan(point.z))
        {
            continue;
        }
        pt.x = (point.x / point.z) / fx + cx;
        pt.y = (point.y / point.z) / fy + cy;

        cv::circle(thred, pt, 1, cv::Scalar(255), 2);
        depth.at<ushort>(pt) = point.z * 1000;
    }
}
