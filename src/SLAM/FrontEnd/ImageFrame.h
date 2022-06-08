#ifndef MONO_VIO_IMAGEFRAME_H
#define MONO_VIO_IMAGEFRAME_H

#include <src/Util/TypeDef.h>

namespace gf {
    struct FeaturesWithFrameID {
        ImageFrameIDType mImageFrameID;//Image Frame ID
        VectorNd<7>      mFeaturePoint;//x,y,z,u,v,v_x,v_y
    };

    class ImageFrame final{
    public:
        ImageFrame();

        ImageFrame(const Map<FeatureIDType, Vector<FeaturesWithFrameID>> &points_,
                   const TimeStampType &timestamp_);

    private:
        Map<FeatureIDType, Vector<FeaturesWithFrameID>> mFeatures;

        LieAlgebrase3    mImagePose;//denotes current pose.
        TimeStampType    mCurrentFrameTimeStamp;//denotes timestamp.
        KeyFrameFlagType mKeyFrame;//denotes whether this image is key frame or not.
    };
}


#endif //MONO_VIO_IMAGEFRAME_H
