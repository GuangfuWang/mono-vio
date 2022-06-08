#ifndef MONO_VIO_IMUPREINTEGRATION_H
#define MONO_VIO_IMUPREINTEGRATION_H

#include <src/Util/TypeDef.h>
#include <src/SLAM/Sensors/IMUModel.h>

namespace gf {
    class ImuPreIntegration {
    public:

        void Interpolation(const bool &update_jacobian,
                           double delta_t_imu,
                           const Vector3d &acceleration_i, const Vector3d &gyroscope_i,
                           const Vector3d &acceleration_iPlus1, const Vector3d &gyroscope_iPlus1,
                           const Vector3d &linearized_bAcc_i, const Vector3d &linearized_bGyro_i,
                           const Vector3d &delta_p_i, const Vector3d &delta_v_i, const Quaternion &delta_q_i,
                           Vector3d &delta_p_iPlus1, Vector3d &delta_v_iPlus1, Quaternion &delta_q_iPlus1,
                           Vector3d &linearized_bAcc_iPlus1, Vector3d &linearized_bGyro_iPlus1);

    private:
        void MidPointInterpolation(
                const bool &update_jacobian,
                double delta_t_imu,
                const Vector3d &acceleration_i, const Vector3d &gyroscope_i,
                const Vector3d &acceleration_iPlus1, const Vector3d &gyroscope_iPlus1,
                const Vector3d &linearized_bAcc_i, const Vector3d &linearized_bGyro_i,
                const Vector3d &delta_p_i, const Vector3d &delta_v_i, const Quaternion &delta_q_i,
                Vector3d &delta_p_iPlus1, Vector3d &delta_v_iPlus1, Quaternion &delta_q_iPlus1,
                Vector3d &linearized_bAcc_iPlus1, Vector3d &linearized_bGyro_iPlus1
        );

        void EulerInterpolation(const bool &update_jacobian,
                                double delta_t_imu,
                                const Vector3d &acceleration_i, const Vector3d &gyroscope_i,
                                const Vector3d &acceleration_iPlus1, const Vector3d &gyroscope_iPlus1,
                                const Vector3d &linearized_bAcc_i, const Vector3d &linearized_bGyro_i,
                                const Vector3d &delta_p_i, const Vector3d &delta_v_i, const Quaternion &delta_q_i,
                                Vector3d &delta_p_iPlus1, Vector3d &delta_v_iPlus1, Quaternion &delta_q_iPlus1,
                                Vector3d &linearized_bAcc_iPlus1, Vector3d &linearized_bGyro_iPlus1);


    private:
        Vector3d      mPreIntegratedTranslation;
        Vector3d      mPreIntegratedVelocity;
        LieAlgebraso3 mPreIntegratedRotation;
        Vector3d      mKthTranslation;
        Vector3d      mKthVelocity;
        LieAlgebraso3 mKthRotation;
        Vector3d      mKPlusTranslation;
        Vector3d      mKPlusVelocity;
        LieAlgebraso3 mKPlusRotation;

        CovarianceType<15>   mPreIntegratedCovariance;
        SquareMatrixType<15> mFMatrix;
        SquareMatrixType<12> mVMatrix;
        JacobianType<15, 15> mPreIntegratedJacob;
        DeltaType<15>        mPreIntegratedDeltaVariable;
        SquareMatrixType<18> mNoise;
        SharedRef<IMUModel>  mImuModel;
    };
}


#endif //MONO_VIO_IMUPREINTEGRATION_H
