#ifndef MONO_VIO_INITIALIZATION_H
#define MONO_VIO_INITIALIZATION_H

#include <src/Util/TypeDef.h>

namespace gf {

    struct SFMFeature {
        Vector<Pair<unsigned int, Vector2f>> observations;

        Vector3f     position;
        unsigned int frameID;
        float        depth;
        bool         hasTrianglated;
    };

    class Initialization final {
    public:

        Initialization();

        ~Initialization();

    public:
        //public methods

    private:
        bool     mInitialized = false;
        float    mSceneScale;
        Vector3f mImuGyroBias;
        Vector3f mImuAccelerationBias;
        Vector3f mGravity;

    };

}


#endif //MONO_VIO_INITIALIZATION_H
