#include "ORBTracker.h"
#include <src/Util/Logger.h>


namespace gf {
    ORBTracker::ORBTracker(const unsigned int &nFeatures, const float &scaleFactor, const unsigned int &nPyramid,
                           const unsigned int &edgeThreshold, const int &sourceImgToPyramidLevel, const int &wta_k,
                           const cv::ORB::ScoreType &sType, const unsigned int &fastThreshold,
                           const cv::DescriptorMatcher::MatcherType &matcherType) {
        mOrbTracker      = cv::ORB::create(nFeatures, scaleFactor, nPyramid,
                                           edgeThreshold, sourceImgToPyramidLevel, wta_k,
                                           sType, edgeThreshold, fastThreshold);
        mMatcher         = cv::DescriptorMatcher::create(matcherType);
        mImageFrameCount = 0;
        mTimer           = createSharedRef<Timer>();
    }

    bool ORBTracker::DetectAndMatch() {
        if (mImageFrameCount==0){
            //todo: return after feature extraction.
        }
        DetectKeyPoints(mImageCurr, mCurrentKeyPoints);
        ComputeDescriptors(mImageCurr, mCurrentKeyPoints, mCurrentDescriptors);
        Vector<cv::DMatch> mTempMatches, mTempGoodMatches;
        mMatcher->match(mPrevDescriptors, mCurrentDescriptors, mTempMatches);
        float    maxDist  = std::numeric_limits<float>::min();
        for (int i = 0; i < mTempMatches.size(); ++i) {
            maxDist = std::max(maxDist, mTempMatches[i].distance);
        }
        float mMatchesDistanceThreshold = 0.6f;
        for (int j = 0; j < mTempMatches.size(); ++j) {
            if (mTempMatches[j].distance < mMatchesDistanceThreshold * maxDist) {
                mTempGoodMatches.emplace_back(mTempMatches[j]);
            }
        }

        return false;
    }

    void ORBTracker::WriteTimeRecordToFile(const QString &file) {

    }

    void ORBTracker::DrawCurrentMatch() {

    }

    bool ORBTracker::FeatureMatch() {
        return false;
    }

    bool ORBTracker::DetectKeyPoints(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &dstKeyPoints) {
        mImageFrameCount++;
        mTimer->tick();
        mOrbTracker->detect(sourceImg, dstKeyPoints);
        unsigned int dur = mTimer->tock();
#ifdef MONO_DEBUG
        GF_INFO("%d-th KeyPoint detection consuming: %d ms", mImageFrameCount, dur);
#endif
        mKeyPointExtractionTime.insert(mKeyPointExtractionTime.end(), dur);
        return true;
    }

    bool ORBTracker::ComputeDescriptors(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &keyPoints,
                                        cv::OutputArray &descriptors) {
        mTimer->tick();
        mOrbTracker->compute(sourceImg, keyPoints, descriptors);
        unsigned int dur = mTimer->tock();
#ifdef MONO_DEBUG
        GF_INFO("%d-th Description consuming: %d ms", mImageFrameCount, dur);
#endif
        mComputeDescriptorTime.insert(mComputeDescriptorTime.end(), dur);
        return false;
    }

    void ORBTracker::Reset() {

    }
}

