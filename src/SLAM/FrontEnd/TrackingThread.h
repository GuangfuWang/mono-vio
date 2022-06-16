
#ifndef MONO_VIO_TRACKINGTHREAD_H
#define MONO_VIO_TRACKINGTHREAD_H

#include <atomic>

namespace gf{
    class TrackingThread {
    private:
        void obtain(){
            //🚧 read operation will after this.
            mCurrentDone.load(std::memory_order_acquire);
        }
        void set(){
            //🚦 write operation will before this.
            mCurrentDone.store(true,std::memory_order_release);
        }
    public:
        std::atomic<bool> mCurrentDone;
    private:

    };

}


#endif //MONO_VIO_TRACKINGTHREAD_H
