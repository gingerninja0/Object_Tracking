#pragma once

#include <memory>
#include "node.h"

#define MAX_TREE_DEPTH 5

struct Layer
{
    std::vector<Node> nodes;
};


class Tree
{
private:
    std::vector<std::unique_ptr<Node>> node; // A vector of nodes, each node is the root node of a target's hypthesis tree

    uint32_t node_id_counter;

    uint32_t depth;

    std::vector<Layer> layer;

public:
    Tree(Eigen::Vector3d);
    ~Tree();

    void expand(std::vector<Eigen::Vector3d>, std::vector<uint32_t> &);

};


