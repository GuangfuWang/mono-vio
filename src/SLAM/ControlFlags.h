#ifndef MONO_VIO_CONTROLFLAGS_H
#define MONO_VIO_CONTROLFLAGS_H

namespace gf {
    enum class SolverFlag {
        Initial   = 0,
        NonLinear = 1,
    };
    enum class InterpolationStrategy {
        MidPoint = 0,
        Euler    = 1,
    };
}

#endif //MONO_VIO_CONTROLFLAGS_H
