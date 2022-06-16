#ifndef MONO_VIO_IMUFRAME_HPP
#define MONO_VIO_IMUFRAME_HPP

#include <src/Util/TypeDef.h>

namespace gf{
    typedef struct ImuFrame_ final{
        //🧮 timestamp,acceleration_x,acceleration_y,acceleration_z,
        // gyroscope_x,gyroscope_y,gyroscope_z,
        // theta_x, theta_y, theta_z
        /// @note when using mpu6050 imu, we have offer its drivers with kalman filtered theta.
        List<VectorNd<10>> mFrameData;
    }ImuFrame;
}

#endif //MONO_VIO_IMUFRAME_HPP
