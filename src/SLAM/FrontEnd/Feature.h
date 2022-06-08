#ifndef MONO_VIO_FEATURE_H
#define MONO_VIO_FEATURE_H

#include <src/Util/TypeDef.h>

namespace gf {
    struct Feature {
        FeatureIDType          mID;
        ImageFrameIDType       mStartFrame;
        List<ImageFrameIDType> mProceedingFrame;
    };
}


#endif //MONO_VIO_FEATURE_H
