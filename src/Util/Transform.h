#ifndef MONO_VIO_TRANSFORM_H
#define MONO_VIO_TRANSFORM_H

#include "TypeDef.h"

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
}

#endif //MONO_VIO_TRANSFORM_H
