#pragma once

#include <cstddef>
#include <stdint.h>
#include <Eigen/Core>
#include <vector>
#include <memory>

#include "target_hypothesis.h"

// These are for gating the mahalnobis distance, from chi2inv in MATLAB
#define GATE_997 13.9314 // chi2inv(0.997, 3)
#define GATE_95 7.8147   // chi2inv(0.95, 3)
#define GATE_68 3.5059   // chi2inv(0.68, 3)

class Node : public std::enable_shared_from_this<Node>
{
private:

    uint32_t target_id;
    uint32_t measurement_id;

    Eigen::Vector3d measurement;

    uint32_t depth;    

    Target_Hypothesis target;

    std::vector<std::shared_ptr<Node>> next; // Vector of nodes that attach to this node
    std::shared_ptr<Node> prev; // shared because each next node will point back to the same previous node

    std::shared_ptr<Node> self;

    void correct_recursive(Eigen::Vector3d, uint32_t, std::vector<uint32_t> &); // The recursive function call to do the measurement correction
    void predict_recursive(void);

    void tree_size_recursive(uint32_t &);

public:
    Node(Eigen::Vector3d, Target_Hypothesis, uint32_t, uint32_t);   // For interior and leaf nodes
    Node(Eigen::Vector3d, uint32_t, uint32_t, bool);          // For root nodes (Defined as clutter and stored in the tree vector)

    void add_node(Eigen::Vector3d, Target_Hypothesis, uint32_t, uint32_t, bool);

    ~Node();

    uint32_t get_target_id(void);

    void correct(Eigen::Vector3d, uint32_t, std::vector<uint32_t> &);
    void predict(void);

    uint32_t gating(Eigen::Vector3d); // Use the target

    bool clutter; // Set to true if a clutter measurement, this will skip the measurement correction

    uint32_t tree_size(void);



};
