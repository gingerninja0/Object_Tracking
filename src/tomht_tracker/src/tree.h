#pragma once

#include <memory>
#include "node.h"

class Tree
{
private:
    std::vector<std::unique_ptr<Node>> tree_vec; // A vector of nodes, each node is the root node of a target's hypthesis tree

    uint32_t target_index_pointer;

    uint32_t node_id_counter;

public:
    Tree(/* args */);
    ~Tree();

    // y, target_id, measurement_id
    void add_target(Eigen::Vector3d, uint32_t, uint32_t);

    void correct(std::vector<Eigen::Vector3d>, std::vector<uint32_t> &);

    void predict(void);

    void set_target_index_pointer(uint32_t);

    void print_size(void);

    
};


