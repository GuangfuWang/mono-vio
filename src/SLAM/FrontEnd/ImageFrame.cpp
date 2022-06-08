#include "ImageFrame.h"
#include <src/Util/Timer.h>
namespace gf{

    ImageFrame::ImageFrame():mFeatures(Map<FeatureIDType,Vector<FeaturesWithFrameID>>()),
    mCurrentFrameTimeStamp(GetCurrentMilliTimeStamp()),mKeyFrame(false),mImagePose(LieAlgebrase3::Zero()){

    }

    ImageFrame::ImageFrame(const Map<FeatureIDType, Vector<FeaturesWithFrameID>> &points_,
                           const TimeStampType &timestamp_):
                           mFeatures(points_),mCurrentFrameTimeStamp(timestamp_) ,
                           mKeyFrame(false),mImagePose(LieAlgebrase3::Zero()){

    }
}