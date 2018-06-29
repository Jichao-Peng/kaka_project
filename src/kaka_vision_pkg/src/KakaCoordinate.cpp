//
// Created by leo on 18-4-28.
//

#include "KakaCoordinate.h"

KakaCoordinate::KakaCoordinate()
{
    //在这里输入手眼标定的结果矩阵
    CamHBase << 0.07667585666155152,   0.7510243230984076, -0.6558073490894991,   348.3711773540727,
                0.99703468733851,     -0.05344625468840247, 0.05536542335774353, -18.18611185556252,
                0.006530332994342469, -0.6581078665191302, -0.7528953385276215,   226.7168111796017,
                0,                     0,                   0,                    1;
}

KakaCoordinate::~KakaCoordinate() {}

Eigen::Vector3d KakaCoordinate::TransformPointFromCam2Base(const Eigen::Vector3d &Point)
{
    Eigen::Vector4d P;
    P.block(0,0,3,1) = Point;
    P(3) = 1;
    Eigen::Vector4d PointInBase = CamHBase * P;
    return PointInBase.block(0,0,3,1);
}

Eigen::Vector3d KakaCoordinate::TransformVectorFromCam2Base(const Eigen::Vector3d &Vector)
{
    Eigen::Vector4d V(0,0,0,0);
    V.block(0,0,3,1) = Vector;
    V(3) = 0;
    Eigen::Vector4d VectorInBase = CamHBase * V;
    return VectorInBase.block(0,0,3,1);
}





