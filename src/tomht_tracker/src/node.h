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

class Node
{
private:

    // Store the ids of the previous and subsequent (next) nodes
    uint32_t prev;
    std::vector<uint32_t> next;

    uint32_t depth;
    uint32_t id;

    Target_Hypothesis target;

public:
    Node(Eigen::Vector3d, uint32_t, uint32_t);
    Node(Node, Eigen::Vector3d, uint32_t, uint32_t);
    ~Node();

    Target_Hypothesis get_target(void);

    uint32_t get_id(void);
    void add_prev(uint32_t);
    void add_next(uint32_t);

    uint32_t & get_prev(void);
    std::vector<uint32_t> & get_next(void);
};
