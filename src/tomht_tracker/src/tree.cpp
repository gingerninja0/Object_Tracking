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

void Tree::correct(std::vector<Eigen::Vector3d> y_vec)
{
    for (auto &tree : tree_vec)
    {
        for (size_t i = 0; i < y_vec.size(); i++)
        {
            tree->correct(y_vec[i], i);
        }
                
    }
    
}