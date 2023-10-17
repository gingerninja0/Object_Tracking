#pragma once

#include <vector>
#include <Eigen/Core>

#include "tree.h"

class TOMHT
{
private:
    Tree hypothesis_tree;

    std::vector<Eigen::Vector3d> y_vec;

    void gating(void);

public:
    TOMHT(/* args */);
    ~TOMHT();
    void update(std::vector<Eigen::Vector3d>);
};




