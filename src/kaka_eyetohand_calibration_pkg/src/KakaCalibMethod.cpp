//
// Created by leo on 18-4-22.
//

#include "KakaCalibMethod.h"

KakaCalibMethod::KakaCalibMethod(Size boardsize, float squaresize) :
        BoardSize(boardsize),
        SquareSize(squaresize)
{

}

KakaCalibMethod::~KakaCalibMethod() {}

//利用opencv寻找图像中的角点并返回实际坐标
bool KakaCalibMethod::CalculateImageCorners(Mat Image, vector<Point2f> &Corner, Mat& ImageOutput)
{
    Corner.clear();

    Mat ImageRGB, ImageGray;
    Image.copyTo(ImageRGB);
    cvtColor(ImageRGB, ImageGray, COLOR_BGR2GRAY);

    //寻找角点
    bool FoundFlag = findChessboardCorners(ImageGray, BoardSize, Corner,CALIB_CB_ADAPTIVE_THRESH |CALIB_CB_FAST_CHECK |
                                           CALIB_CB_NORMALIZE_IMAGE);
    if(FoundFlag)
    {
        //亚像素级处理
        cornerSubPix(ImageGray,Corner,Size(11,11),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,30,0.1));
        drawChessboardCorners(ImageRGB,BoardSize,Corner,true);
        ImageRGB.copyTo(ImageOutput);
    }
    else
    {
        ImageRGB.copyTo(ImageOutput);
        return false;
    }
    return true;
}

//生成棋盘格的虚拟坐标
bool KakaCalibMethod::CalculateChessboardCorners(vector<Point3f> &Corner)
{
    Corner.clear();

    for(int i = 0; i < BoardSize.height; i++)
    {
        for(int j = 0; j < BoardSize.width; j++)
        {
            Corner.push_back(Point3f((i * SquareSize), (j * SquareSize), 0));
        }
    }
    return true;
}

//将旋转向量和平移向量转化成齐次矩阵
Mat KakaCalibMethod::CalculateCameraHomogeneous(Mat RotationVector, Mat TransitionVector)
{
    Mat Homogeneous;
    Homogeneous = Mat::zeros(4,4,CV_64FC1);

    Rodrigues(RotationVector,Homogeneous(Rect(0,0,3,3)));
    TransitionVector.copyTo(Homogeneous(Rect(3,0,1,3)));
    Homogeneous.at<double>(3,3) = 1;

    return Homogeneous;
}


//计算机器人末端姿态的齐次矩阵，主要是讲欧拉角转化成旋转矩阵
Mat KakaCalibMethod::CalculateTCPHomogeneous(vector<double> TCPPose)
{
    Mat Rotation, Homogeneous;//旋转举证和齐次矩阵
    Rotation = Mat::zeros(3, 3, CV_64FC1);
    Homogeneous = Mat::zeros(4, 4, CV_64FC1);

    double Tx, Ty, Tz, Roll, Pitch, Yaw;
    Tx = TCPPose[0];
    Ty = TCPPose[1];
    Tz = TCPPose[2];
    Roll = TCPPose[3];
    Pitch = TCPPose[4];
    Yaw = TCPPose[5];

    double Ca1, Cb1, Cc1, Sa1, Sb1, Sc1;

    Cc1 = cos(Roll);
    Sc1 = sin(Roll);
    Cb1 = cos(Pitch);
    Sb1 = sin(Pitch);
    Ca1 = cos(Yaw);
    Sa1 = sin(Yaw);

    Rotation.at<double>(0, 0) = Ca1 * Cb1;
    Rotation.at<double>(0, 1) = Ca1 * Sb1 * Sc1 - Sa1 * Cc1;
    Rotation.at<double>(0, 2) = Ca1 * Sb1 * Cc1 + Sa1 * Sc1;

    Rotation.at<double>(1, 0) = Sa1 * Cb1;
    Rotation.at<double>(1, 1) = Sa1 * Sb1 * Sc1 + Ca1 * Cc1;
    Rotation.at<double>(1, 2) = Sa1 * Sb1 * Cc1 - Ca1 * Sc1;

    Rotation.at<double>(2, 0) = -Sb1;
    Rotation.at<double>(2, 1) = Cb1 * Sc1;
    Rotation.at<double>(2, 2) = Cb1 * Cc1;

    Rotation.copyTo(Homogeneous(cv::Rect(0, 0, 3, 3)));
    Homogeneous.at<double>(0, 3) = Tx * 1000;
    Homogeneous.at<double>(1, 3) = Ty * 1000;
    Homogeneous.at<double>(2, 3) = Tz * 1000;
    Homogeneous.at<double>(3, 3) = 1;

    return Homogeneous;
}

//手眼标定的主要程序，可以标定两个矩阵，因此EyetoHand和EyeinHand应该都可以标定
HandEyeCalibData KakaCalibMethod::HandEyeCalibration(vector<Mat> CamHCal, vector<Mat> ToolHBase)
{
    HandEyeCalibData CalibData;
    std::vector<cv::Mat> Hc, Hd, He, Hf;

    if (ToolHBase.size() == CamHCal.size() && ToolHBase.size() > 1)
    {
        /// 构建方程参数 A*X = X*B
        for (size_t i = 0; i < ToolHBase.size(); i++)
        {
            for (size_t j = 0; j < ToolHBase.size(); j++)
            {

                if (j > i)
                {
                    cv::Mat hc, hd;
                    hc = CamHCal[j] * CamHCal[i].inv();
                    hd = ToolHBase[j] * ToolHBase[i].inv();
                    Hc.push_back(hc);
                    Hd.push_back(hd);

                    cv::Mat he, hf;
                    he = CamHCal[j].inv() * CamHCal[i];
                    hf = ToolHBase[j].inv() * ToolHBase[i];
                    He.push_back(he);
                    Hf.push_back(hf);
                }
            }
        }
    }

    /// 求解方程 A*X = X*B
    if (Hc.size() == Hd.size() && He.size() == Hf.size() &&  Hc.size() == He.size() && Hc.size() > 1)
    {
        //采用Tasi算法
        CalibData.CamHBase = TsaiSolver(Hd, Hc);
        CalibData.CalHTool = TsaiSolver(Hf, He);
    }
    return CalibData;
}


//Tsai算法，用于求解AX=XB的问题
Mat KakaCalibMethod::TsaiSolver(vector<Mat> Hc, vector<Mat> Hd)
{
    Mat eyeM, camHbase;
    eyeM = Mat::eye(3, 3, CV_64FC1);
    camHbase = Mat::zeros(4, 4, CV_64FC1);

    assert(Hc.size() == Hd.size());
    int nStatus = (int) Hc.size();

    /// 计算Rx
    Mat A, b, pinA;

    for (int i = 0; i < nStatus; i++)
    {
        Mat Rc, Rd, alpha, beta, normAlpha, normBeta, Pc, Pd, tempA, tempAA, tempb;
        Hc[i](Rect(0, 0, 3, 3)).copyTo(Rc);
        Hd[i](Rect(0, 0, 3, 3)).copyTo(Rd);//取得旋转矩阵

        Rodrigues(Rc, alpha);
        Rodrigues(Rd, beta);//利用罗德里格斯变换讲旋转矩阵转化成旋转向量

        double normRc = norm(alpha, NORM_L2);
        double normRd = norm(beta, NORM_L2);//向量归一化

        normAlpha = alpha / normRc;
        normBeta = beta / normRd;

        Pc = 2 * sin(normRc / 2) * normAlpha;
        Pd = 2 * sin(normRd / 2) * normBeta;//修正的罗德里格斯参数表示姿态变化

        tempAA = (Pc + Pd);
        tempA = CreatAntisymmetricMatrix(tempAA);
        tempb = Pd - Pc;

        A.push_back(tempA);
        b.push_back(tempb);//Mat的push_back是在矩阵的行方向添加列数相同的矩阵
    }

    invert(A, pinA, DECOMP_SVD);//之前有担心这样会不会将初始旋转向量放大了，但是求逆相当于常数求倒，因此没关系

    Mat Pcg_prime, Pcg, Rx1, Rx2;
    Pcg_prime = pinA * b;//求得出事旋转向量

    Pcg = 2 * Pcg_prime / sqrt(1 + norm(Pcg_prime, NORM_L2) * norm(Pcg_prime, NORM_L2));//计算旋转向量

    Rx1 = (1 - norm(Pcg, NORM_L2) * norm(Pcg, NORM_L2) / 2) * eyeM;
    Rx2 = Pcg * Pcg.t() + sqrt(4 - norm(Pcg, NORM_L2) * norm(Pcg, NORM_L2)) * CreatAntisymmetricMatrix(Pcg);//计算旋转矩阵

    Mat Rx, tx;
    Rx = Mat::zeros(3, 3, CV_64FC1);
    tx = Mat::zeros(3, 1, CV_64FC1);

    Rx = Rx1 + 0.5 * Rx2;

    /// 计算tx（平移向量）
    Mat AA, pinAA, bb;

    for (int i = 0; i < nStatus; i++)
    {
        Mat Rc, tc, Rd, td;
        Hc[i](Rect(0, 0, 3, 3)).copyTo(Rc);
        Hd[i](Rect(0, 0, 3, 3)).copyTo(Rd);
        Hc[i](Rect(3, 0, 1, 3)).copyTo(tc);
        Hd[i](Rect(3, 0, 1, 3)).copyTo(td);

        Mat tempC, tempd;
        tempC = Rc - eyeM;
        tempd = Rx * td - tc;

        AA.push_back(tempC);
        bb.push_back(tempd);
    }
    invert(AA, pinAA, DECOMP_SVD);
    tx = pinAA * bb;

    Rx.copyTo(camHbase(Rect(0, 0, 3, 3)));
    tx.copyTo(camHbase(Rect(3, 0, 1, 3)));
    camHbase.at<double>(3, 3) = 1;

    return camHbase;
}

//计算向量的反对成矩阵
Mat KakaCalibMethod::CreatAntisymmetricMatrix(Mat src)
{
    assert(src.rows == 1 || src.cols == 1);

    Mat dst;
    dst = cv::Mat::zeros(3, 3, CV_64FC1);

    double a = src.at<double>(0, 0);
    double b = src.at<double>(1, 0);
    double c = src.at<double>(2, 0);

    dst.at<double>(0, 1) = -c;
    dst.at<double>(1, 0) = c;

    dst.at<double>(0, 2) = b;
    dst.at<double>(2, 0) = -b;

    dst.at<double>(1, 2) = -a;
    dst.at<double>(2, 1) = a;

    return dst;
}




























