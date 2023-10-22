#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <Eigen/Core>

#include "tree.h"

class TOMHT
{
private:
    std::unique_ptr<Tree> hypothesis_tree;

    std::vector<Eigen::Vector3d> y_vec;

    void hypothesis_generation(void);

    uint32_t get_new_target_id(void);
    std::vector<uint32_t> used_target_ids;


public:
    TOMHT(/* args */);
    ~TOMHT();
    void update(std::vector<Eigen::Vector3d>);
};




