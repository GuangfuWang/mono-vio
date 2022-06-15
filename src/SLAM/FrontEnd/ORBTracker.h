#ifndef MONO_VIO_ORBTRACKER_H
#define MONO_VIO_ORBTRACKER_H

#include <opencv2/features2d.hpp>
#include <opencv2/sfm/fundamental.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <src/Util/Timer.h>
#include <src/Util/TypeDef.h>
#include <QString>

namespace gf {
    class ORBTracker final {
    public:
        ORBTracker(const unsigned int &nFeatures, const float &scaleFactor,
                   const unsigned int &nPyramid, const unsigned int &edgeThreshold,
                   const int &sourceImgToPyramidLevel, const int &wta_k,
                   const cv::ORB::ScoreType &sType, const unsigned int &fastThreshold,
                   const cv::DescriptorMatcher::MatcherType &matcherType);

        ORBTracker(const ORBTracker &c) = delete;

        bool DetectAndMatch();

        void WriteTimeRecordToFile(const QString &file);

        void DrawCurrentMatch();

        void Reset();

    private:
        bool DetectKeyPoints(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &dstKeyPoints);

        bool ComputeDescriptors(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &keyPoints,
                                cv::OutputArray &descriptors);

        bool FeatureMatch();

    private:
        cv::Ptr<cv::ORB>               mOrbTracker;
        cv::Ptr<cv::DescriptorMatcher> mMatcher;

        cv::Mat              mImagePrev;
        cv::Mat              mImageCurr;
        Vector<cv::KeyPoint> mPrevKeyPoints;
        Vector<cv::KeyPoint> mCurrentKeyPoints;
        cv::Mat              mPrevDescriptors;
        cv::Mat              mCurrentDescriptors;
        Vector<cv::DMatch>   mCurrentMatches;
        cv::Mat              mCurrentRotation;
        cv::Mat              mCurrentTranslate;

        SharedRef<Timer> mTimer;
        List<double>     mKeyPointExtractionTime;
        List<double>     mComputeDescriptorTime;
        List<double>     mFeatureMatchTime;
        unsigned int     mImageFrameCount;

    };
}


#endif //MONO_VIO_ORBTRACKER_H
