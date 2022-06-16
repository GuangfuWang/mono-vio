#include "ConfMap.h"
#include <filesystem>
#include "../Util/Logger.h"

namespace gf {

    ///Sensor Camera configuration default value.
    float        ConfMap::mFx         = 364.032f;
    float        ConfMap::mFy         = 364.032f;
    float        ConfMap::mCx         = 258.891f;
    float        ConfMap::mCy         = 209.32f;
    float        ConfMap::mK1         = -1.0f;
    float        ConfMap::mK2         = -1.0f;
    float        ConfMap::mP1         = -1.0f;
    float        ConfMap::mP2         = -1.0f;
    QString      ConfMap::mVendor     = "Microsoft";
    QString      ConfMap::mSeries     = "Kinect Azure";
    CameraType   ConfMap::mCameraType = CameraType::MONO;

    ///Sensor IMU default configuration value
    unsigned int          ConfMap::mImuFrequency                  = 100;
    float                 ConfMap::mAccelerationNoise             = 0.04f;
    float                 ConfMap::mAccelerationBiasNoise         = 0.0004f;
    float                 ConfMap::mGyroscopeNoise                = 0.004f;
    float                 ConfMap::mGyroscopeBiasNoise            = 2.0e-5;
    float                 ConfMap::mInitExcitationAccThreshold    = 0.25f;
    unsigned int          ConfMap::mImuCameraExtrinsicFlag        = 2;
    Vector3d              ConfMap::mImuCameraExtrinsicTranslation = Vector3d::Zero();
    Quaternion            ConfMap::mImuCameraExtrinsicQuaternion  = Quaternion(1, 0, 0, 0);
    InterpolationStrategy ConfMap::mInterpolationMethod           = InterpolationStrategy::MidPoint;

    ///Project info default value.
    QString         ConfMap::mRootDir          = "";
    unsigned char   ConfMap::mVersionMajor     = 1;
    unsigned char   ConfMap::mVersionMinor     = 2;
    unsigned char   ConfMap::mVersionPatch     = 0;
    QString         ConfMap::mAuthor           = "Guangfu Wang";
    QString         ConfMap::mDate             = "2022-06-02";
    QString         ConfMap::mFacility         = "Bigdata Department, CCTEG";
    QString         ConfMap::mLicense          = "MIT";
    QString         ConfMap::mStatus           = "active";
    QStringList     ConfMap::mContributionList = {"Guangfu Wang"};
    QStringList     ConfMap::mContributeEmail  = {"thuwgf@gmail.com"};

    ///Tracking thread default configuration values.
    unsigned char ConfMap::mFastThreshold            = 9;
    float         ConfMap::mScaleFactor              = 1.2f;
    unsigned char ConfMap::mNumPyramid               = 8;
    unsigned char ConfMap::mFailIfFeatureLessThan    = 25;
    unsigned char ConfMap::mLowKeyPointThreshold     = 30;
    unsigned char ConfMap::mLowKeyPointFrame         = 8;
    float         ConfMap::mMaxFeatureDescriptorDist = 0.6f;
    RobustKernel  ConfMap::mRobustKernel             = RobustKernel::Huber;
    unsigned char ConfMap::mNumCamera                = 1;
    float         ConfMap::mGravity                  = 9.80766f;
    Vector3d      ConfMap::mInitTrans                = {0.0, 0.0, 0.0};
    Quaternion    ConfMap::mInitRot                  = {1.0, 0.0, 0.0, 0.0};

    void ConfMap::Init() {
        std::filesystem::path curr = std::filesystem::current_path();
        curr     = curr.parent_path();
        mRootDir = QString(curr.string().c_str());
        YAML::Node config;
        try {
            string path = curr.string() + "/conf/conf.yaml";
            config = YAML::LoadFile(path);
            GF_INFO("Loaded configuration file: %s", path.c_str());
        } catch (YAML::BadFile &e) {
            GF_ERROR("Load configuration file failed with reason: %s", e.what());
            return;
        }
        YAML::Node projectInfoNode = config["ProjectInfo"];
        YAML::Node SensorCamera    = config["Sensor"]["sensorCamera"];
        YAML::Node SensorIMU       = config["Sensor"]["sensorIMU"];
        YAML::Node TrackerSet      = config["Tracker"];
        YAML::Node LoopDetect      = config["LoopDetection"];
        YAML::Node PoseGraphOpt    = config["PoseGraphOptimization"];
        YAML::Node SlideWindow     = config["SlideWindowOptimization"];
        YAML::Node UISet           = config["UISetting"];

        //project info conf.
        mVersionMajor = projectInfoNode["versionMajor"].as<unsigned char>();
        mVersionMinor = projectInfoNode["versionMinor"].as<unsigned char>();
        mVersionPatch = projectInfoNode["versionPatch"].as<unsigned char>();
        mAuthor       = QString::fromStdString(projectInfoNode["author"].as<string>());
        mDate         = QString::fromStdString(projectInfoNode["date"].as<string>());
        mFacility     = QString::fromStdString(projectInfoNode["facility"].as<string>());
        mStatus       = QString::fromStdString(projectInfoNode["status"].as<string>());
        mLicense      = QString::fromStdString(projectInfoNode["license"].as<string>());
        for (auto item: projectInfoNode["contributionList"]) {
            QString     temp = QString::fromStdString(item.as<string>());
            QStringList tt   = temp.split(',');
            mContributionList.insert(mContributionList.end(), tt.at(0).trimmed());
            mContributeEmail.insert(mContributeEmail.end(), tt.at(1).trimmed());
        }
        //sensor camera conf.
        mFx = SensorCamera["fx"].as<float>();
        mFy = SensorCamera["fy"].as<float>();
        mCx = SensorCamera["cx"].as<float>();
        mCy = SensorCamera["cy"].as<float>();
        mK1 = SensorCamera["k1"].as<float>();
        mK2 = SensorCamera["k2"].as<float>();
        mP1 = SensorCamera["p1"].as<float>();
        mP2 = SensorCamera["p2"].as<float>();

        //sensor imu conf.
        mImuFrequency = SensorIMU["frequency"].as<unsigned int>();
        //ui settings conf.

        //tracker conf.
        mFastThreshold            = TrackerSet["fastThreshold"].as<unsigned char>();
        mScaleFactor              = TrackerSet["scaleFactor"].as<float>();
        mNumPyramid               = TrackerSet["numPyramid"].as<unsigned char>();
        mFailIfFeatureLessThan    = TrackerSet["failIfFeatureLessThan"].as<unsigned char>();
        mLowKeyPointThreshold     = TrackerSet["lowKeyPointThreshold"].as<unsigned char>();
        mLowKeyPointThreshold     = TrackerSet["lowKeyPointFrame"].as<unsigned char>();
        mMaxFeatureDescriptorDist = TrackerSet["maxFeatureDescriptorDist"].as<float>();
        mNumCamera                = TrackerSet["numCamera"].as<unsigned char>();
        mGravity                  = TrackerSet["gravity"].as<float>();
        QString kernelTemp = QString::fromStdString(TrackerSet["robustKernel"].as<string>()).toLower();
        if (kernelTemp == "huber")mRobustKernel = RobustKernel::Huber;
        else mRobustKernel = RobustKernel::NoKernel;
        mInitTrans         = Vector3d({TrackerSet["firstImagePose"]["x"].as<double>(),
                                       TrackerSet["firstImagePose"]["y"].as<double>(),
                                       TrackerSet["firstImagePose"]["z"].as<double>()});
        mInitRot           = {TrackerSet["firstImagePose"]["qw"].as<double>(),
                              TrackerSet["firstImagePose"]["qx"].as<double>(),
                              TrackerSet["firstImagePose"]["qy"].as<double>(),
                              TrackerSet["firstImagePose"]["qz"].as<double>()};

    }

    unsigned char ConfMap::getMFastThreshold() {
        return mFastThreshold;
    }

    void ConfMap::setMFastThreshold(unsigned char mFastThreshold) {
        ConfMap::mFastThreshold = mFastThreshold;
    }

    float ConfMap::getMScaleFactor() {
        return mScaleFactor;
    }

    void ConfMap::setMScaleFactor(float mScaleFactor) {
        ConfMap::mScaleFactor = mScaleFactor;
    }

    unsigned char ConfMap::getMNumPyramid() {
        return mNumPyramid;
    }

    void ConfMap::setMNumPyramid(unsigned char mNumPyramid) {
        ConfMap::mNumPyramid = mNumPyramid;
    }

    unsigned char ConfMap::getMFailIfFeatureLessThan() {
        return mFailIfFeatureLessThan;
    }

    void ConfMap::setMFailIfFeatureLessThan(unsigned char mFailIfFeatureLessThan) {
        ConfMap::mFailIfFeatureLessThan = mFailIfFeatureLessThan;
    }

    unsigned char ConfMap::getMLowKeyPointThreshold() {
        return mLowKeyPointThreshold;
    }

    void ConfMap::setMLowKeyPointThreshold(unsigned char mLowKeyPointThreshold) {
        ConfMap::mLowKeyPointThreshold = mLowKeyPointThreshold;
    }

    RobustKernel ConfMap::getMRobustKernel() {
        return mRobustKernel;
    }

    void ConfMap::setMRobustKernel(RobustKernel mRobustKernel) {
        ConfMap::mRobustKernel = mRobustKernel;
    }

    unsigned char ConfMap::getMNumCamera() {
        return mNumCamera;
    }

    void ConfMap::setMNumCamera(unsigned char mNumCamera) {
        ConfMap::mNumCamera = mNumCamera;
    }

    float ConfMap::getMGravity() {
        return mGravity;
    }

    void ConfMap::setMGravity(float mGravity) {
        ConfMap::mGravity = mGravity;
    }

    const QString &ConfMap::getMVendor() {
        return mVendor;
    }

    void ConfMap::setMVendor(const QString &mVendor) {
        ConfMap::mVendor = mVendor;
    }

    const QString &ConfMap::getMSeries() {
        return mSeries;
    }

    void ConfMap::setMSeries(const QString &mSeries) {
        ConfMap::mSeries = mSeries;
    }

    CameraType ConfMap::getMCameraType() {
        return mCameraType;
    }

    void ConfMap::setMCameraType(CameraType mCameraType) {
        ConfMap::mCameraType = mCameraType;
    }

    unsigned char ConfMap::getMVersionMajor() {
        return mVersionMajor;
    }

    void ConfMap::setMVersionMajor(unsigned char mVersionMajor) {
        ConfMap::mVersionMajor = mVersionMajor;
    }

    unsigned char ConfMap::getMVersionMinor() {
        return mVersionMinor;
    }

    void ConfMap::setMVersionMinor(unsigned char mVersionMinor) {
        ConfMap::mVersionMinor = mVersionMinor;
    }

    unsigned char ConfMap::getMVersionPatch() {
        return mVersionPatch;
    }

    void ConfMap::setMVersionPatch(unsigned char mVersionPatch) {
        ConfMap::mVersionPatch = mVersionPatch;
    }

    const QString &ConfMap::getMAuthor() {
        return mAuthor;
    }

    void ConfMap::setMAuthor(const QString &mAuthor) {
        ConfMap::mAuthor = mAuthor;
    }

    const QString &ConfMap::getMDate() {
        return mDate;
    }

    void ConfMap::setMDate(const QString &mDate) {
        ConfMap::mDate = mDate;
    }

    const QString &ConfMap::getMFacility() {
        return mFacility;
    }

    void ConfMap::setMFacility(const QString &mFacility) {
        ConfMap::mFacility = mFacility;
    }

    const QString &ConfMap::getMLicense() {
        return mLicense;
    }

    void ConfMap::setMLicense(const QString &mLicense) {
        ConfMap::mLicense = mLicense;
    }

    const QString &ConfMap::getMStatus() {
        return mStatus;
    }

    void ConfMap::setMStatus(const QString &mStatus) {
        ConfMap::mStatus = mStatus;
    }

    const QStringList &ConfMap::getMContributionList() {
        return mContributionList;
    }

    void ConfMap::setMContributionList(const QStringList &mContributionList) {
        ConfMap::mContributionList = mContributionList;
    }

    const QStringList &ConfMap::getMContributeEmail() {
        return mContributeEmail;
    }

    void ConfMap::setMContributeEmail(const QStringList &mContributeEmail) {
        ConfMap::mContributeEmail = mContributeEmail;
    }

    unsigned char ConfMap::getMLowKeyPointFrame() {
        return mLowKeyPointFrame;
    }

    void ConfMap::setMLowKeyPointFrame(unsigned char mLowKeyPointFrame) {
        ConfMap::mLowKeyPointFrame = mLowKeyPointFrame;
    }

    float ConfMap::getMMaxFeatureDescriptorDist() {
        return mMaxFeatureDescriptorDist;
    }

    void ConfMap::setMMaxFeatureDescriptorDist(float mMaxFeatureDescriptorDist) {
        ConfMap::mMaxFeatureDescriptorDist = mMaxFeatureDescriptorDist;
    }

    const Vector3d &ConfMap::getMInitTrans() {
        return mInitTrans;
    }

    void ConfMap::setMInitTrans(const Vector3d &mInitTrans) {
        ConfMap::mInitTrans = mInitTrans;
    }

    const Quaternion &ConfMap::getMInitRot() {
        return mInitRot;
    }

    void ConfMap::setMInitRot(const Quaternion &mInitRot) {
        ConfMap::mInitRot = mInitRot;
    }

}