#include "ConfMap.h"
#include <filesystem>
#include "../Util/Logger.h"

namespace gf {

    float        ConfMap::mGravity      = 9.8f;
    float        ConfMap::mFx           = 364.032f;
    float        ConfMap::mFy           = 364.032f;
    float        ConfMap::mCx           = 258.891f;
    float        ConfMap::mCy           = 209.32f;
    float        ConfMap::mK1           = -1.0f;
    float        ConfMap::mK2           = -1.0f;
    float        ConfMap::mP1           = -1.0f;
    float        ConfMap::mP2           = -1.0f;
    unsigned int ConfMap::mImuFrequency = 100;

    float        ConfMap::mAccelerationNoise          = 0.04f;
    float        ConfMap::mAccelerationBiasNoise      = 0.0004f;
    float        ConfMap::mGyroscopeNoise             = 0.004f;
    float        ConfMap::mGyroscopeBiasNoise         = 2.0e-5;
    float        ConfMap::mInitExcitationAccThreshold = 0.25f;
    unsigned int ConfMap::mImuCameraExtrinsicFlag     = 2;

    Vector3d              ConfMap::mImuCameraExtrinsicTranslation = Vector3d::Zero();
    Quaternion            ConfMap::mImuCameraExtrinsicQuaternion = Quaternion(1,0,0,0);
    InterpolationStrategy ConfMap::mInterpolationMethod = InterpolationStrategy::MidPoint;

    QString         ConfMap::mRootDir          = "";
    unsigned char   ConfMap::mVersionMajor     = 0;
    unsigned char   ConfMap::mVersionMinor     = 0;
    unsigned char   ConfMap::mVersionPatch     = 0;
    QString         ConfMap::mAuthor           = "";
    QString         ConfMap::mDate             = "";
    QString         ConfMap::mFacility         = "";
    QString         ConfMap::mLicense          = "";
    QString         ConfMap::mStatus           = "";
    QStringList     ConfMap::mContributionList = QStringList();

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
        YAML::Node projectInfoNode = config["projectInfo"];
        YAML::Node SensorCamera    = config["sensorCamera"];
        YAML::Node SensorIMU       = config["sensorIMU"];
        YAML::Node TrackerSet      = config["tracker"];
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
            mContributionList.insert(mContributionList.end(), QString::fromStdString(item.as<string>()));
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
        mGravity = TrackerSet["gravity"].as<float>();

    }

}