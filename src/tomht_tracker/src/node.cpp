#include "node.h"

// Correct target estimate
Node::Node(Eigen::Vector3d y_, uint32_t target_id_, uint32_t measurement_id_, std::shared_ptr<Node> prev_)
    : target_id(target_id_), measurement_id(measurement_id_), target(y_), prev(prev_)
{
    next.push_back(nullptr);
    // Correct the target estiamte with the measurement, or given a measurement it will add the node below the current node with the corrected state, not sure, up to future me
}

// Generate new target estimate
Node::Node(Eigen::Vector3d y_, uint32_t target_id_, uint32_t measurement_id_, std::nullptr_t prev_)
    : target_id(target_id_), measurement_id(measurement_id_), target(y_), prev(prev_)
{
    next.push_back(nullptr);
    // Initialise a target from the measurement
}

Node::~Node()
{
}


uint32_t Node::get_target_id(void)
{
    return target_id;
}