#ifndef MONO_VIO_VISIONDB_HPP
#define MONO_VIO_VISIONDB_HPP

#include "src/Util/TypeDef.h"

namespace gf {

    typedef struct Feature_ {
        FeatureIDType            mFeatureID;
        Vector3f                 mPosition;
        Vector<Vector2i>         mFeatureCoordinates;
        Vector<ImageFrameIDType> mInFrame;//🏛 item should be frame position in FrameDB
    } Feature;

    typedef struct Frame_ {
        ImageFrameIDType     mFrameID;
        Vector<unsigned int> mFeatures;//🏛 item should be feature position in FeatureDB
    } Frame;

    using FeatureDB = Vector<Feature>;
    using KeyFrameDB = Vector<Frame>;
}


#endif //MONO_VIO_VISIONDB_HPP
