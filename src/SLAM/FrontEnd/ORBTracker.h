#ifndef MONO_VIO_ORBTRACKER_H
#define MONO_VIO_ORBTRACKER_H

#include <opencv2/features2d.hpp>
#include <opencv2/sfm/fundamental.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <src/Util/Timer.h>
#include <src/Util/TypeDef.h>
#include <QString>
#include "ImageFrame.hpp"

namespace gf {
    class ORBTracker final {
    public:
        ORBTracker(const unsigned int &nFeatures, const float &scaleFactor,
                   const unsigned int &nPyramid, const unsigned int &edgeThreshold,
                   const int &sourceImgToPyramidLevel, const int &wta_k,
                   const cv::ORB::ScoreType &sType, const unsigned int &fastThreshold,
                   const cv::DescriptorMatcher::MatcherType &matcherType);

        ORBTracker(const ORBTracker &c) = delete;

        bool DetectAndMatch(ImageFrame& curr);

        void WriteTimeRecordToFile(const QString &file);

        void DrawCurrentMatch();

        void Reset();

        void Track(const cv::Mat& img,const TimeStampType &time);

    public:
        const List<unsigned int> &getMKeyPointExtractionTime() const;

        void setMKeyPointExtractionTime(const List<unsigned int> &mKeyPointExtractionTime);

        const List<unsigned int> &getMComputeDescriptorTime() const;

        void setMComputeDescriptorTime(const List<unsigned int> &mComputeDescriptorTime);

        const List<unsigned int> &getMFeatureMatchTime() const;

        void setMFeatureMatchTime(const List<unsigned int> &mFeatureMatchTime);

        unsigned int getMImageFrameCount() const;

        void setMImageFrameCount(unsigned int mImageFrameCount);

    private:
        bool DetectKeyPoints(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &dstKeyPoints);

        bool ComputeDescriptors(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &keyPoints,
                                cv::OutputArray &descriptors);

    private:
        /// orb tracker object, normally will not change during runtime.
        cv::Ptr<cv::ORB>               mOrbTracker;
        cv::Ptr<cv::DescriptorMatcher> mMatcher;
        cv::Point2d                    mPrinciplePoint;
        double                         mFocalLen;

        cv::Mat       mImagePrev;
        cv::Mat       mImageCurr;
        TimeStampType mCurrFrameTime;

        Vector<cv::KeyPoint> mPrevKeyPoints;
        Vector<cv::KeyPoint> mCurrentKeyPoints;

        cv::Mat      mPrevDescriptors;
        cv::Mat      mCurrentDescriptors;
        unsigned int mKeyPointFailCount;

        SharedRef<Timer>   mTimer;
        //time is in millisecond.
        List<unsigned int> mKeyPointExtractionTime;
        List<unsigned int> mComputeDescriptorTime;
        List<unsigned int> mFeatureMatchTime;
        ImageFrameIDType   mImageFrameCount;

    };
}


#endif //MONO_VIO_ORBTRACKER_H
