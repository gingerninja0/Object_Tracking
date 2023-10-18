#pragma once

#include <cstddef>
#include <stdint.h>
#include <Eigen/Core>
#include <vector>
#include <memory>

#include "target_hypothesis.h"

class Node
{
private:

    uint32_t target_id;
    uint32_t measurement_id;

    Eigen::Vector3d measurement;
    bool clutter; // Set to true if a clutter measurement, this will skip the measurement correction

    Target_Hypothesis target;

    std::vector<std::unique_ptr<Node>> next; // Vector of nodes that attach to this node, unique because each element in the vector is a single node (no double ups)
    std::shared_ptr<Node> prev; // shared because each next node will point back to the same previous node





public:
    Node(Eigen::Vector3d, uint32_t, uint32_t, std::shared_ptr<Node>);   // For interior and leaf nodes
    Node(Eigen::Vector3d, uint32_t, uint32_t, std::nullptr_t);          // For root nodes
    ~Node();

    uint32_t get_target_id(void);
};

