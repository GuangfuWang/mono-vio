#ifndef MONO_VIO_IMUMODEL_H
#define MONO_VIO_IMUMODEL_H

#include <src/Util/TypeDef.h>

namespace gf {
    class IMUModel final {
    public:
        IMUModel();

        IMUModel(const Vector3d &acc_, const Vector3d &gyro_);

        ~IMUModel();

    private:
        Vector3d mAcc;
        Vector3d mGyro;
        Vector3d mAccBias;
        Vector3d mGyroBias;
    };
}


#endif //MONO_VIO_IMUMODEL_H
