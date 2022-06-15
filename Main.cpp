#include <src/ConfMap/ConfMap.h>
#include <Eigen/Core>
#include <QApplication>
using namespace gf;

void InitSystem(){
    ConfMap::Init();
    ///this is used for multi-thread applications when using eigen,optional
    ///@see https://eigen.tuxfamily.org/dox/TopicMultiThreading.html
    Eigen::initParallel();
}

int main(int argc, char **argv) {
    InitSystem();
    QApplication app(argc, argv);
    app.setStyleSheet(QString("QLabel{ font-family:'Arial, 微软雅黑' }"));
    //todo: add windows creation and loop.
    QApplication::exec();
    return 0;
}