#ifndef MONO_VIO_CONFMAP_H
#define MONO_VIO_CONFMAP_H

#include <QString>
#include <yaml-cpp/yaml.h>
#include "../Util/TypeDef.h"
#include "src/SLAM/ControlFlags.h"

namespace gf {
    class ConfMap final {
    public:
        static void Init();

        static const float &Gravity() { return mGravity; }

        static const QString &RootDir() { return mRootDir; }

        static const IntrinsicType Intrinsic() {
            IntrinsicType ret;
            ret << mFx, 0., mCx,
                    0., mFy, mCy,
                    0., 0., 1.;
            return ret;
        }

        static const IntrinsicType InverseIntrinsic() {
            IntrinsicType ret;
            const float   det = 1 / (mFx * mFy);
            ret << mFy, 0., -mCx * mFy,
                    0., mFx, -mFx * mCy,
                    0., 0., mFx * mFy;
            return det * ret;
        }

        static float &Fx() { return mFx; }

        static float &Fy() { return mFy; }

        static float &Cx() { return mCx; }

        static float &Cy() { return mCy; }

        static float &K1() { return mK1; }

        static float &K2() { return mK2; }

        static float &P1() { return mP1; }

        static float &P2() { return mP2; }

        static InterpolationStrategy &GetInterpolationMethod() { return mInterpolationMethod; }

    private:
        static float mGravity;
        static float mFx;
        static float mFy;
        static float mCx;
        static float mCy;
        static float mK1;
        static float mK2;
        static float mP1;
        static float mP2;

        //imu
        static float                 mAccelerationNoise;
        static float                 mAccelerationBiasNoise;
        static float                 mGyroscopeNoise;
        static float                 mGyroscopeBiasNoise;
        static float                 mInitExcitationAccThreshold;
        static unsigned int          mImuCameraExtrinsicFlag;
        static Vector3d              mImuCameraExtrinsicTranslation;
        static Quaternion            mImuCameraExtrinsicQuaternion;
        static InterpolationStrategy mInterpolationMethod;

        static unsigned int mImuFrequency;

        static QString mRootDir;

        static unsigned char mVersionMajor;
        static unsigned char mVersionMinor;
        static unsigned char mVersionPatch;

        static QString     mAuthor;
        static QString     mDate;
        static QString     mFacility;
        static QString     mLicense;
        static QString     mStatus;
        static QStringList mContributionList;
    };
}


#endif //MONO_VIO_CONFMAP_H
