#pragma once

#include <memory>
#include "node.h"

class Tree
{
private:
    std::vector<std::unique_ptr<Node>> node; // A vector of nodes, each node is the root node of a target's hypthesis tree

    uint32_t node_id_counter;

    uint32_t depth;

public:
    Tree();
    ~Tree();


};


