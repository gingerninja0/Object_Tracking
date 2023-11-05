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



public:



};
