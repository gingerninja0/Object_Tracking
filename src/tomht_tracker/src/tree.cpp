#include "tree.h"

#include <iostream>

Tree::Tree(Eigen::Vector3d y)
{
    node_id_counter = 0;
    depth = 0;

    layer.resize(MAX_TREE_DEPTH);

    layer[0].nodes.push_back(Node(y, node_id_counter, depth));

    depth++; // Next node will be at depth 1
    node_id_counter++; // First node always has id = 0
}

Tree::~Tree()
{
}



void Tree::expand(std::vector<Eigen::Vector3d> y_vec, std::vector<uint32_t> & associated_measurements)
{
    Layer & layer_current = layer[depth];

    // NExt need to add the nodes to the current lowest layer (at depth value) then I need to 
    
}

