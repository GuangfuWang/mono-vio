#include "ORBTracker.h"
#include <src/Util/Logger.h>
#include <src/ConfMap/ConfMap.h>
#include <src/Util/Transform.h>


namespace gf {
    ORBTracker::ORBTracker(const unsigned int &nFeatures, const float &scaleFactor, const unsigned int &nPyramid,
                           const unsigned int &edgeThreshold, const int &sourceImgToPyramidLevel, const int &wta_k,
                           const cv::ORB::ScoreType &sType, const unsigned int &fastThreshold,
                           const cv::DescriptorMatcher::MatcherType &matcherType) {
        mOrbTracker = cv::ORB::create(nFeatures, scaleFactor, nPyramid,
                                      edgeThreshold, sourceImgToPyramidLevel, wta_k,
                                      sType, edgeThreshold, fastThreshold);
        mMatcher    = cv::DescriptorMatcher::create(matcherType);

        mImageFrameCount   = 0;
        mKeyPointFailCount = 0;
        mCurrFrameTime     = 0;
        mPrinciplePoint    = {ConfMap::Cx(), ConfMap::Cy()};
        mFocalLen          = (ConfMap::Fx() + ConfMap::Fy()) / 2.0f;
        mTimer             = createSharedRef<Timer>();
        mTimer->start();
    }

    //================================================================================================================//

    void ORBTracker::Track(const cv::Mat &img, const TimeStampType &time) {
        std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
        mImageCurr     = img.clone();
        mCurrFrameTime = time;
        ImageFrame curr;
        if (DetectAndMatch(curr)) {
            unsigned int dur = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - t).count();
#ifdef GF_LOG_FRONTEND
            GF_INFO("Image Frame %d processed with %dms", mImageFrameCount, dur);
#endif
            mImageFrameCount++;
        }
    }

    bool ORBTracker::DetectAndMatch(ImageFrame &curr) {
        //todo: un-distort image operation.

        if (mImageFrameCount == 0) {
            mImagePrev = mImageCurr.clone();
            mPrevKeyPoints.clear();
            mPrevDescriptors.setTo(0);
            if (DetectKeyPoints(mImagePrev, mPrevKeyPoints)) {
                ComputeDescriptors(mImagePrev, mPrevKeyPoints, mPrevDescriptors);
                curr.mKeyFrame              = true;
                curr.mImagePose             = LieGroupSE3(ConfMap::getMInitRot(), ConfMap::getMInitTrans()).log();
                curr.mCurrentFrameTimeStamp = mCurrFrameTime;
                curr.mFrameID               = mImageFrameCount;
                //todo: add untrackedFeature vector to curr image frame.
                //curr.mUnTrackedFeatures;
                //reset fail count.
                mKeyPointFailCount = 0;
                return true;
            } else {
                mKeyPointFailCount++;
                if (mKeyPointFailCount > ConfMap::getMLowKeyPointFrame()) {
                    GF_WARN("ORB Tracking is lost due to low key point extracted...");
                }
                return false;
            }
        }
        if (DetectKeyPoints(mImageCurr, mCurrentKeyPoints)) {
            mKeyPointFailCount = 0;
            ComputeDescriptors(mImageCurr, mCurrentKeyPoints, mCurrentDescriptors);
            Vector<cv::DMatch> mTempMatches, mTempGoodMatches;
            mTimer->tick();
            mMatcher->match(mPrevDescriptors, mCurrentDescriptors, mTempMatches);
            unsigned int dur = mTimer->tock();
#ifdef GF_LOG_MATCH
            GF_INFO("Matching consumes %d ms", dur);
#endif
#ifdef GF_TIME_FEATURE_MATCH
            mFeatureMatchTime.insert(mFeatureMatchTime.end(), dur);
#endif
            float     maxDist = std::numeric_limits<float>::min();
            for (auto &mTempMatche: mTempMatches) {
                maxDist = std::max(maxDist, mTempMatche.distance);
            }
            for (auto &mTempMatche: mTempMatches) {
                if (mTempMatche.distance < ConfMap::getMMaxFeatureDescriptorDist() * maxDist) {
                    mTempGoodMatches.emplace_back(mTempMatche);
                }
            }
            if (mTempGoodMatches.size() < ConfMap::getMFailIfFeatureLessThan()) {
                GF_WARN("Matches %d is too low", mTempGoodMatches.size());
                curr.mKeyFrame = true;
            } else {
                curr.mKeyFrame = false;
            }
#ifdef GF_LOG_MATCH
            GF_INFO("Image Frame %d with %d Matches", mImageFrameCount, mTempGoodMatches.size());
#endif
            Vector<cv::Point2f> firstKeyPoints;
            Vector<cv::Point2f> secondKeyPoints;

            for (int k = 0; k < mTempGoodMatches.size(); ++k) {
                firstKeyPoints.emplace_back(mPrevKeyPoints[mTempGoodMatches[k].queryIdx].pt);
                secondKeyPoints.emplace_back(mCurrentKeyPoints[mTempGoodMatches[k].trainIdx].pt);
            }
            ///@note here R&t is point1->point2, in our case is current pose -> prev pose.
            cv::Mat  R = cv::Mat(3, 3, CV_32F);
            cv::Mat  t = cv::Mat(3, 1, CV_32F);
            cv::Mat  e = cv::findEssentialMat(secondKeyPoints, firstKeyPoints,
                                              mFocalLen, mPrinciplePoint);
            cv::recoverPose(e, secondKeyPoints, firstKeyPoints,
                            R, t, mFocalLen, mPrinciplePoint);

            curr.mFrameID               = mImageFrameCount;
            curr.mCurrentFrameTimeStamp = mCurrFrameTime;
            curr.mImagePose             = LieGroupSE3(CV2EigenRot(R), CV2EigenTrans(t)).log();
            //todo: warp features to ImageFrame Object curr.

            //reset parameters.
            mImagePrev     = mImageCurr.clone();
            mPrevKeyPoints = mCurrentKeyPoints;
            mCurrentKeyPoints.clear();
            mPrevDescriptors = mCurrentDescriptors.clone();
            mCurrentDescriptors.setTo(0);
            return true;
        } else {
            mKeyPointFailCount++;
            if (mKeyPointFailCount > ConfMap::getMLowKeyPointFrame()) {
                GF_WARN("ORB Tracking is lost due to %d times failure", mKeyPointFailCount);
            }
            return false;
        }
    }

    bool ORBTracker::DetectKeyPoints(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &dstKeyPoints) {
        mTimer->tick();
        mOrbTracker->detect(sourceImg, dstKeyPoints);
        unsigned int dur = mTimer->tock();
        if (dstKeyPoints.size() < ConfMap::getMLowKeyPointThreshold()) {
            GF_WARN("Key points %d is too low", dstKeyPoints.size());
            return false;
        }
#ifdef GF_TIME_FEATURE_DETECT
#ifdef GF_LOG_KEYPOINT
        GF_INFO("%d-th KeyPoint detection consuming: %d ms", mImageFrameCount, dur);
#endif
        mKeyPointExtractionTime.insert(mKeyPointExtractionTime.end(), dur);
#endif
        return true;
    }

    bool ORBTracker::ComputeDescriptors(const cv::Mat &sourceImg, Vector<cv::KeyPoint> &keyPoints,
                                        cv::OutputArray &descriptors) {
        mTimer->tick();
        mOrbTracker->compute(sourceImg, keyPoints, descriptors);
        unsigned int dur = mTimer->tock();
#ifdef GF_TIME_FEATURE_DESCRIPTOR
#ifdef GF_LOG_DESCRIPTOR
        GF_INFO("%d-th Description consuming: %d ms", mImageFrameCount, dur);
#endif
        mComputeDescriptorTime.insert(mComputeDescriptorTime.end(), dur);
#endif
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void ORBTracker::WriteTimeRecordToFile(const QString &file) {

    }

    void ORBTracker::DrawCurrentMatch() {

    }

    void ORBTracker::Reset() {

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int ORBTracker::getMImageFrameCount() const {
        return mImageFrameCount;
    }

    void ORBTracker::setMImageFrameCount(unsigned int ImageFrameCount) {
        ORBTracker::mImageFrameCount = ImageFrameCount;
    }

    const List<unsigned int> &ORBTracker::getMKeyPointExtractionTime() const {
        return mKeyPointExtractionTime;
    }

    void ORBTracker::setMKeyPointExtractionTime(const List<unsigned int> &KeyPointExtractionTime) {
        ORBTracker::mKeyPointExtractionTime = KeyPointExtractionTime;
    }

    const List<unsigned int> &ORBTracker::getMComputeDescriptorTime() const {
        return mComputeDescriptorTime;
    }

    void ORBTracker::setMComputeDescriptorTime(const List<unsigned int> &ComputeDescriptorTime) {
        ORBTracker::mComputeDescriptorTime = ComputeDescriptorTime;
    }

    const List<unsigned int> &ORBTracker::getMFeatureMatchTime() const {
        return mFeatureMatchTime;
    }

    void ORBTracker::setMFeatureMatchTime(const List<unsigned int> &FeatureMatchTime) {
        ORBTracker::mFeatureMatchTime = FeatureMatchTime;
    }

}

