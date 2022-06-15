
#ifndef MONO_VIO_TYPEDEF_H
#define MONO_VIO_TYPEDEF_H

#include <memory>
#include <thread>
#include <map>
#include <vector>
#include <list>
#include <functional>
#include <Eigen/Dense>
#include <sophus/se3.hpp>

namespace gf {
    template<typename T>
    using UniqueRef = std::unique_ptr<T>;
    template<typename T>
    using SharedRef = std::shared_ptr<T>;

    ///@note here is cpp perfect forwarding.
    template<typename T, typename ... Args>
    constexpr SharedRef<T> createSharedRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename ... Args>
    constexpr UniqueRef<T> createUniqueRef(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename Ret, typename ... Args>
    using Function = std::function<Ret(Args...)>;

    template<unsigned char N>
    using ThreadPool = std::array<std::thread,N>;

    template<typename T>
    using Vector = std::vector<T>;
    template<typename key, typename value>
    using Map = std::map<key, value>;
    template<typename First, typename Second>
    using Pair = std::pair<First, Second>;
    using string = std::string;
    template<typename T>
    using List = std::list<T>;
#ifndef UChar
    using UChar = unsigned char;
#endif

    using OctreeIDType = unsigned int;
    using OctreeIndexType = unsigned int;
    using OctreeType = unsigned int;
    using OctreeDataIndexType = unsigned int;

    using FeatureIDType = unsigned int;
    using ImageFrameIDType = unsigned int;
    using TimeStampType = uint64_t;
    using KeyFrameFlagType = bool;
    using Vector2f = Eigen::Vector2f;
    using Vector2d = Eigen::Vector2d;
    using Vector2i = Eigen::Vector2i;
    using Vector3f = Eigen::Vector3f;
    using Vector3d = Eigen::Vector3d;
    using Vector3i = Eigen::Vector3i;
    using Vector4f = Eigen::Vector4f;
    using Vector4i = Eigen::Vector4i;
    using Vector6f = Eigen::Array<float, 6, 1>;
    using Vector6d = Eigen::Array<double, 6, 1>;
    using Vector6i = Eigen::Array<int, 6, 1>;
    using Quaternion = Eigen::Quaterniond;
    using Translation = Eigen::Vector3f;
    using RigidTransform = Eigen::Isometry3d;
    using LieGroupSE3 = Sophus::SE3d;
    using LieGroupSO3 = Sophus::SO3d;
    using LieAlgebrase3 = Sophus::Vector6d;
    using LieAlgebraso3 = Sophus::Vector3d;
    using RigidTransformDeltaType = Sophus::Vector6d;
    using RotationMat = Eigen::Matrix3d;
    template<unsigned int N>
    using DeltaType = Eigen::Matrix<double, N, 1>;
    template<unsigned int Row, unsigned int Col>
    using JacobianType = Eigen::Matrix<double, Row, Col>;
    template<unsigned int N>
    using CovarianceType = Eigen::Matrix<double, N, N>;
    template<unsigned int N>
    using SquareMatrixType = Eigen::Matrix<double, N, N>;
    using IntrinsicType = Eigen::Matrix3d;
    template<unsigned int N>
    using VectorNd = Eigen::Matrix<double, N, 1>;

    using PoseWithTimeType = Eigen::Matrix<double, 8, 1>;
    ///@note you have to use c++17 or above to use vector<Eigen> like this.
    ///@see https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html and
    ///@see https://eigen.tuxfamily.org/dox/group__TopicStlContainers.html
    using TrajectoryType = std::vector<PoseWithTimeType>;


}

#endif //MONO_VIO_TYPEDEF_H
