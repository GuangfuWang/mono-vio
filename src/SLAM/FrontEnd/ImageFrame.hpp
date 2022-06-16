#ifndef MONO_VIO_IMAGEFRAME_HPP
#define MONO_VIO_IMAGEFRAME_HPP

#include <src/Util/TypeDef.h>

namespace gf {

    typedef struct TrackFeature_ {
        //🍏 considering 8-byte alignment in modern CPU.
        // memory should be dividable by 8, in this case: 4+12+4*4+8=40.
        FeatureIDType mFeatureID;
        Vector3f      mPos;
        Vector2i      mImageCoordinates;
        Vector2f      mUVVelocity;
        //high 32-bit represent position, low 32-bit represents id.
        uint64_t      mStartFrame = 0xffffffffffffffff;
    } TrackFeature;

    typedef struct UnTrackedFeature_ {
        //🍏 considering 8-byte alignment in modern CPU.
        // memory should be dividable by 8, in this case: 4+12+4*4=32.
        FeatureIDType mFeatureID;
        Vector3f      mPos;
        Vector2i      mImageCoordinates;
        Vector2f      mUVVelocity;
    } UnTrackedFeature;

    typedef struct ImageFrame_ final {
        ImageFrameIDType         mFrameID;
        Vector<UnTrackedFeature> mUnTrackedFeatures;
        Vector<TrackFeature>     mTrackedFeatures;
        ///@note here pose represents current -> prev pose,
        ///a.k.a T_w,k
        LieAlgebrase3    mImagePose;//denotes current pose.
        TimeStampType    mCurrentFrameTimeStamp;//denotes timestamp.
        KeyFrameFlagType mKeyFrame;//denotes whether this image is key frame or not.
    } ImageFrame;
}


#endif //MONO_VIO_IMAGEFRAME_HPP
