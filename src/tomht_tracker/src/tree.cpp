#include "tree.h"

#include <iostream>

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::set_target_index_pointer(uint32_t i)
{
    target_index_pointer = i;
}

void Tree::add_target(Eigen::Vector3d y, uint32_t target_id, uint32_t measurement_id)
{
    tree_vec.push_back(std::make_unique<Node>(y, target_id, measurement_id, nullptr));
}