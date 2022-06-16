#ifndef MONO_VIO_TRANSFORM_H
#define MONO_VIO_TRANSFORM_H

#include <opencv2/core/mat.hpp>
#include <QtGlobal>
#include "TypeDef.h"

#pragma
namespace gf {
    inline Eigen::Matrix<double, 3, 3> SkewMatrix(const Vector3d &v) {
        Eigen::Matrix<double, 3, 3> skew_ret = Eigen::Matrix<double, 3, 3>::Zero();
        skew_ret(0, 1) = -v.z();
        skew_ret(1, 0) = v.z();
        skew_ret(0, 2) = v.y();
        skew_ret(2, 0) = -v.y();
        skew_ret(1, 2) = -v.x();
        skew_ret(2, 1) = v.x();
        return skew_ret;
    }

    inline RotationMat CV2EigenRot(const cv::Mat &source) {
        GF_ASSERT(source.cols == 3, "Rotation matrix from cv should be 3X3");
        GF_ASSERT(source.rows == 3, "Rotation matrix from cv should be 3X3");
        RotationMat ret;
        ret << source.at<float>(0, 0), source.at<float>(0, 1), source.at<float>(0, 2),
                source.at<float>(1, 0), source.at<float>(1, 1), source.at<float>(1, 2),
                source.at<float>(2, 0), source.at<float>(2, 1), source.at<float>(2, 2);
        return ret;
    }

    inline cv::Mat EigenRot2CV(const RotationMat &r) {
        GF_ASSERT(r.rows() == 3, "Rotation matrix from eigen should be 3X3");
        GF_ASSERT(r.cols() == 3, "Rotation matrix from eigen should be 3X3");
        cv::Mat ret = cv::Mat(3, 3, CV_32F);
        ret.at<float>(0, 0) = r(0, 0);
        ret.at<float>(0, 1) = r(0, 1);
        ret.at<float>(0, 2) = r(0, 2);
        ret.at<float>(1, 0) = r(1, 0);
        ret.at<float>(1, 1) = r(1, 1);
        ret.at<float>(1, 2) = r(1, 2);
        ret.at<float>(2, 0) = r(2, 0);
        ret.at<float>(2, 1) = r(2, 1);
        ret.at<float>(2, 2) = r(2, 2);
        return ret;
    }

    inline Translation CV2EigenTrans(const cv::Mat &tt) {
        GF_ASSERT(tt.cols == 1, "Translation matrix from cv should be 3X1");
        GF_ASSERT(tt.rows == 3, "Translation matrix from cv should be 3X1");
        Translation ret;
        ret << tt.at<float>(0, 0), tt.at<float>(1, 0), tt.at<float>(2, 0);
        return ret;
    }

    inline cv::Mat EigenTrans2CV(const Translation &t) {
        GF_ASSERT(t.cols() == 1, "Translation matrix from eigen should be 3X1");
        GF_ASSERT(t.rows() == 3, "Translation matrix from eigen should be 3X1");
        cv::Mat ret = cv::Mat(3, 1, CV_32F);
        ret.at<float>(0, 0) = t.x();
        ret.at<float>(1, 0) = t.y();
        ret.at<float>(2, 0) = t.z();
        return ret;
    }
}

#endif //MONO_VIO_TRANSFORM_H
