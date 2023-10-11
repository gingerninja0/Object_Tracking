#pragma once

#include <Eigen/Core>
#include <vector>

namespace sim
{

struct Target
{
    Eigen::Vector3d y;
    std::string label;
};

struct Measurement
{
    std::vector<Target> y_vec;
};



} // namespace sim