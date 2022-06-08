#include "ImuPreIntegration.h"
#include <src/ConfMap/ConfMap.h>

namespace gf {

    void ImuPreIntegration::MidPointInterpolation(const bool &update_jacobian,
                                                  double imu_delta_t_i,
                                                  const Vector3d &acceleration_i,
                                                  const Vector3d &gyroscope_i,
                                                  const Vector3d &acceleration_iPlus1,
                                                  const Vector3d &gyroscope_iPlus1,
                                                  const Vector3d &linearized_bAcc_i,
                                                  const Vector3d &linearized_bGyro_i,
                                                  const Vector3d &delta_p_i,
                                                  const Vector3d &delta_v_i,
                                                  const Quaternion &delta_q_i,
                                                  Vector3d &delta_p_iPlus1,
                                                  Vector3d &delta_v_iPlus1,
                                                  Quaternion &delta_q_iPlus1,
                                                  Vector3d &linearized_bAcc_iPlus1,
                                                  Vector3d &linearized_bGyro_iPlus1) {
        ///calculate delta_q_i+1.
        Vector3d unbiased_mean_gyroscope = (gyroscope_i + gyroscope_iPlus1) / 2.0 - linearized_bGyro_i;
        delta_q_iPlus1 = delta_q_i * Quaternion(1.0,
                                                (unbiased_mean_gyroscope.x() * imu_delta_t_i) / 2.0,
                                                (unbiased_mean_gyroscope.y() * imu_delta_t_i) / 2.0,
                                                (unbiased_mean_gyroscope.z() * imu_delta_t_i) / 2.0);
        ///calculate delta_p_i+1.
        Vector3d unbiased_acc_i      = delta_q_i * (acceleration_i - linearized_bAcc_i);
        Vector3d unbiased_acc_iPlus1 = delta_q_iPlus1 * (acceleration_iPlus1 - linearized_bAcc_i);
        delta_p_iPlus1          = delta_p_i + delta_v_i * imu_delta_t_i +
                                  imu_delta_t_i * imu_delta_t_i * (unbiased_acc_i + unbiased_acc_iPlus1) / 4.0;
        ///calculate delta_v_i+1.
        delta_v_iPlus1          = delta_v_i + imu_delta_t_i * (unbiased_acc_i + unbiased_acc_iPlus1) / 2.0;
        ///ba and bg will remain the same.
        linearized_bAcc_iPlus1  = linearized_bAcc_i;
        linearized_bGyro_iPlus1 = linearized_bGyro_i;
        //---------------have finished p,v,q,update from imu timestamp ( i -> i+1 )-----------------//
        ///update jacobian matrix and covariance,
        ///used for optimization update:
        ///alpha_bk_bk+1 ^ t= alpha_bk_bk+1 ^ (t-1) + J_alpha_ba*delta_ba+J_alpha_bg*delta_bg
        if (update_jacobian) {
            //todo: add jacobian and covariance update here.
        }
    }

    void ImuPreIntegration::EulerInterpolation(const bool &update_jacobian, double delta_t_imu,
                                               const Vector3d &acceleration_i, const Vector3d &gyroscope_i,
                                               const Vector3d &acceleration_iPlus1, const Vector3d &gyroscope_iPlus1,
                                               const Vector3d &linearized_bAcc_i, const Vector3d &linearized_bGyro_i,
                                               const Vector3d &delta_p_i, const Vector3d &delta_v_i,
                                               const Quaternion &delta_q_i, Vector3d &delta_p_iPlus1,
                                               Vector3d &delta_v_iPlus1, Quaternion &delta_q_iPlus1,
                                               Vector3d &linearized_bAcc_iPlus1, Vector3d &linearized_bGyro_iPlus1) {

    }

    /**
     * this method is used to update each p v q at imu timestamp.
     * @param update_jacobian update jacobian matrix and covariance matrix or not.
     * @param delta_t_imu time duration between imu time i -> i+1.
     * @param acceleration_i imu acceleration measurement at imu time i.
     * @param gyroscope_i imu gyroscope measurement at imu time i.
     * @param acceleration_iPlus1
     * @param gyroscope_iPlus1
     * @param linearized_bAcc_i
     * @param linearized_bGyro_i
     * @param delta_p_i
     * @param delta_v_i
     * @param delta_q_i
     * @param delta_p_iPlus1
     * @param delta_v_iPlus1
     * @param delta_q_iPlus1
     * @param linearized_bAcc_iPlus1
     * @param linearized_bGyro_iPlus1
     */
    void ImuPreIntegration::Interpolation(const bool &update_jacobian,
                                          double delta_t_imu,
                                          const Vector3d &acceleration_i, const Vector3d &gyroscope_i,
                                          const Vector3d &acceleration_iPlus1, const Vector3d &gyroscope_iPlus1,
                                          const Vector3d &linearized_bAcc_i, const Vector3d &linearized_bGyro_i,
                                          const Vector3d &delta_p_i, const Vector3d &delta_v_i,
                                          const Quaternion &delta_q_i,
                                          Vector3d &delta_p_iPlus1, Vector3d &delta_v_iPlus1,
                                          Quaternion &delta_q_iPlus1,
                                          Vector3d &linearized_bAcc_iPlus1, Vector3d &linearized_bGyro_iPlus1) {
        if (ConfMap::GetInterpolationMethod() == InterpolationStrategy::MidPoint) {
            MidPointInterpolation(update_jacobian, delta_t_imu,
                                  acceleration_i, gyroscope_i,
                                  acceleration_iPlus1, gyroscope_iPlus1,
                                  linearized_bAcc_i, linearized_bGyro_i,
                                  delta_p_i, delta_v_i, delta_q_i,
                                  delta_p_iPlus1, delta_v_iPlus1, delta_q_iPlus1,
                                  linearized_bAcc_iPlus1, linearized_bGyro_iPlus1);
        } else {
            EulerInterpolation(update_jacobian, delta_t_imu,
                               acceleration_i, gyroscope_i,
                               acceleration_iPlus1, gyroscope_iPlus1,
                               linearized_bAcc_i, linearized_bGyro_i,
                               delta_p_i, delta_v_i, delta_q_i,
                               delta_p_iPlus1, delta_v_iPlus1, delta_q_iPlus1,
                               linearized_bAcc_iPlus1, linearized_bGyro_iPlus1);
        }
    }


}