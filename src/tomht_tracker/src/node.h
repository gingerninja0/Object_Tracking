#pragma once

#include <cstddef>
#include <stdint.h>
#include <Eigen/Core>
#include <vector>

#include "target_hypothesis.h"

class Node
{
private:

    uint32_t target_id;
    uint32_t measurement_id;

    Eigen::Vector3d measurement;
    bool clutter; // Set to true if a clutter measurement, this will skip the measurement correction

    Target_Hypothesis target;

    std::vector<Node *> next; // Vector of nodes that attach to this node
    Node * prev;





public:
    Node(Eigen::Vector3d, uint32_t, uint32_t, Node *);
    ~Node();
};

