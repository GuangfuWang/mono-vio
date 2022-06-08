#include <src/ConfMap/ConfMap.h>
#include <Eigen/Core>
using namespace gf;

void InitSystem(){
    ConfMap::Init();
    ///this is used for multi-thread applications when using eigen,optional
    ///@see https://eigen.tuxfamily.org/dox/TopicMultiThreading.html
    Eigen::initParallel();
}

int main() {
    InitSystem();
    return 0;
}