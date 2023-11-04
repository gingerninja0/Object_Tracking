#include "tree.h"

#include <iostream>

Tree::Tree()
{
    node_id_counter = 0;
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
    tree_vec.push_back(std::make_unique<Node>(y, target_id, measurement_id, false));
}

void Tree::correct(std::vector<Eigen::Vector3d> y_vec, std::vector<uint32_t> & associated_measurements)
{
    for (auto &tree : tree_vec)
    {
        for (size_t i = 0; i < y_vec.size(); i++)
        {
            tree->correct(y_vec[i], i, associated_measurements);
            
        }
                
    }
    
}

void Tree::predict(void)
{
    for (auto &tree : tree_vec)
    {
        tree->predict();
    }
    
}

void Tree::print_size(void)
{
    uint32_t i = 0;
    for (auto &tree : tree_vec)
    {
        
        std::cout << "Tree: " << i << std::endl;
        uint32_t depth = tree->tree_size(); 
        std::cout << "Total number of nodes: " << depth << std::endl;

        i++;
    }
}

