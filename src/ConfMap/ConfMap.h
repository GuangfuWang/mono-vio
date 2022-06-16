#ifndef MONO_VIO_CONFMAP_H
#define MONO_VIO_CONFMAP_H

#include <QString>
#include <yaml-cpp/yaml.h>
#include <src/Util/TypeDef.h>

namespace gf {
    enum class SolverFlag {
        Initial   = 0,
        NonLinear = 1,
    };
    enum class InterpolationStrategy {
        MidPoint = 0,
        Euler    = 1,
    };

    enum class RobustKernel {
        Huber = 0,
        NoKernel = INT_MAX
    };
    enum class CameraType {
        MONO   = 0,
        STEREO = 1,
        RGBD   = 2
    };

    class ConfMap final {
    public:
        static void Init();

        //==============Project info=================================================================
        static const QString &RootDir() { return mRootDir; }

        static unsigned char getMVersionMajor();

        static void setMVersionMajor(unsigned char mVersionMajor);

        static unsigned char getMVersionMinor();

        static void setMVersionMinor(unsigned char mVersionMinor);

        static unsigned char getMVersionPatch();

        static void setMVersionPatch(unsigned char mVersionPatch);

        static const QString &getMAuthor();

        static void setMAuthor(const QString &mAuthor);

        static const QString &getMDate();

        static void setMDate(const QString &mDate);

        static const QString &getMFacility();

        static void setMFacility(const QString &mFacility);

        static const QString &getMLicense();

        static void setMLicense(const QString &mLicense);

        static const QString &getMStatus();

        static void setMStatus(const QString &mStatus);

        static const QStringList &getMContributionList();

        static void setMContributionList(const QStringList &mContributionList);

        static const QStringList &getMContributeEmail();

        static void setMContributeEmail(const QStringList &mContributeEmail);

        //===============Camera Sensor.===============================================================
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

        static const QString &getMVendor();

        static void setMVendor(const QString &mVendor);

        static const QString &getMSeries();

        static void setMSeries(const QString &mSeries);

        static CameraType getMCameraType();

        static void setMCameraType(CameraType mCameraType);

        //============IMU Info==================================================================
        static InterpolationStrategy &GetInterpolationMethod() { return mInterpolationMethod; }


        //===========Tracking values============================================================
        static unsigned char getMFastThreshold();

        static void setMFastThreshold(unsigned char mFastThreshold);

        static float getMScaleFactor();

        static void setMScaleFactor(float mScaleFactor);

        static unsigned char getMNumPyramid();

        static void setMNumPyramid(unsigned char mNumPyramid);

        static unsigned char getMFailIfFeatureLessThan();

        static void setMFailIfFeatureLessThan(unsigned char mFailIfFeatureLessThan);

        static unsigned char getMLowKeyPointThreshold();

        static void setMLowKeyPointThreshold(unsigned char mLowKeyPointThreshold);

        static RobustKernel getMRobustKernel();

        static void setMRobustKernel(RobustKernel mRobustKernel);

        static unsigned char getMNumCamera();

        static void setMNumCamera(unsigned char mNumCamera);

        static float getMGravity();

        static void setMGravity(float mGravity);

        static unsigned char getMLowKeyPointFrame();

        static void setMLowKeyPointFrame(unsigned char mLowKeyPointFrame);

        static float getMMaxFeatureDescriptorDist();

        static void setMMaxFeatureDescriptorDist(float mMaxFeatureDescriptorDist);

        static const Vector3d &getMInitTrans();

        static void setMInitTrans(const Vector3d &mInitTrans);

        static const Quaternion &getMInitRot();

        static void setMInitRot(const Quaternion &mInitRot);

    private:
        ///Camera Sensor configurations
        static float      mFx;
        static float      mFy;
        static float      mCx;
        static float      mCy;
        static float      mK1;
        static float      mK2;
        static float      mP1;
        static float      mP2;
        static QString    mVendor;
        static QString    mSeries;
        static CameraType mCameraType;

        ///IMU Sensor configurations
        static float                 mAccelerationNoise;
        static float                 mAccelerationBiasNoise;
        static float                 mGyroscopeNoise;
        static float                 mGyroscopeBiasNoise;
        static float                 mInitExcitationAccThreshold;
        static unsigned int          mImuCameraExtrinsicFlag;
        static Vector3d              mImuCameraExtrinsicTranslation;
        static Quaternion            mImuCameraExtrinsicQuaternion;
        static InterpolationStrategy mInterpolationMethod;
        static unsigned int          mImuFrequency;

        ///Project information.
        static QString       mRootDir;
        static unsigned char mVersionMajor;
        static unsigned char mVersionMinor;
        static unsigned char mVersionPatch;
        static QString       mAuthor;
        static QString       mDate;
        static QString       mFacility;
        static QString       mLicense;
        static QString       mStatus;
        static QStringList   mContributionList;
        static QStringList   mContributeEmail;

        ///Tracking thread configurations
        static unsigned char mFastThreshold;
        static float         mScaleFactor;
        static unsigned char mNumPyramid;
        static unsigned char mFailIfFeatureLessThan;
        static unsigned char mLowKeyPointThreshold;
        static unsigned char mLowKeyPointFrame;
        static float         mMaxFeatureDescriptorDist;
        static RobustKernel  mRobustKernel;
        static unsigned char mNumCamera;
        static float         mGravity;
        static Vector3d      mInitTrans;
        static Quaternion    mInitRot;
    };
}


#endif //MONO_VIO_CONFMAP_H
