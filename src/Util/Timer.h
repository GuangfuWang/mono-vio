#ifndef MONO_VIO_TIMER_H
#define MONO_VIO_TIMER_H

#include <chrono>
#include <thread>

namespace gf {

/**
 * this class is used for clocking.
 * @note this is not thread safe.
 */
    class Timer {
    public:
        Timer() {}

        Timer(const Timer &) = delete;

        ~Timer() {}

    public:
        /**
         * start timing when clocking.
         */
        inline void start() {
            t_     = std::chrono::system_clock::now();
            start_ = t_;
        }

        /**
         * duration between last tick in milliSeconds.
         * @return
         */
        inline unsigned int tick() {
            unsigned int start = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - t_).count();
            t_ = std::chrono::system_clock::now();
            return start;
        }

        /**
         * duration between whole timing period in milli seconds.
         * @return
         */
        inline unsigned int tock() {
            unsigned int total = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - t_).count();
            start_ = t_ = std::chrono::system_clock::now();
            return total;
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> t_;
        std::chrono::time_point<std::chrono::system_clock> start_;
    };

    /**
     * sleep a certain amount of time in milli seconds.
     * @param milliSeconds time to be sleep.
     */
    inline void sleep(unsigned int milliSeconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
    }

    inline uint64_t GetCurrentMilliTimeStamp() {
        uint64_t ret = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
        return ret;
    }

}


#endif //MONO_VIO_TIMER_H
