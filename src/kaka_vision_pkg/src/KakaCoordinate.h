//
// Created by leo on 18-4-28.
//

#ifndef PROJECT_KAKACOORDINATE_H
#define PROJECT_KAKACOORDINATE_H

#include <Eigen/Dense>

class KakaCoordinate
{
public:
    KakaCoordinate();
    ~KakaCoordinate();
    Eigen::Vector3d TransformPointFromCam2Base(const Eigen::Vector3d &Point);
    Eigen::Vector3d TransformVectorFromCam2Base(const Eigen::Vector3d &Vector);

private:
    Eigen::Matrix4d CamHBase;
};


#endif //PROJECT_KAKACOORDINATE_H
