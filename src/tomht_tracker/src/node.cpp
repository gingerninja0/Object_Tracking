#include "node.h"

#include <iostream>

// Correct target estimate
Node::Node(Eigen::Vector3d y_, Target_Hypothesis target_, uint32_t target_id_, uint32_t measurement_id_, std::shared_ptr<Node> prev_)
    : target_id(target_id_), measurement_id(measurement_id_), prev(prev_)
{
    next.push_back(nullptr);
    // Correct the target estiamte with the measurement, or given a measurement it will add the node below the current node with the corrected state, not sure, up to future me

    target.correct(y_, target_); // This will probably turn into target.correct(y_)
}

// Generate new target estimate, this is the root node of a target hypothesis tree tree
Node::Node(Eigen::Vector3d y_, uint32_t target_id_, uint32_t measurement_id_, std::nullptr_t prev_)
    : target_id(target_id_), measurement_id(measurement_id_), prev(prev_)
{
    next.push_back(nullptr);

    // Initialise a target from the measurement
    target.init(y_);
}

Node::~Node()
{
}


uint32_t Node::get_target_id(void)
{
    return target_id;
}

void Node::correct(Eigen::Vector3d y, uint32_t measurement_id_)
{
    correct_recursive(y, measurement_id_);
}

void Node::correct_recursive(Eigen::Vector3d y, uint32_t measurement_id_)
{
    measurement_id = measurement_id+0; // to prevent a warning (for now, can remove once measurement_id is used somewhere)

    if (next.size() == 1)
    {
        std::cout << "correct_recursion_0" << std::endl;

        self = shared_from_this(); // Issue

        std::cout << "correct_recursion_1" << std::endl;

        auto node = std::make_shared<Node>(y, target, target_id, measurement_id_, self);

        std::cout << "correct_recursion_2" << std::endl;

        next.push_back(std::move(node));
        return;
    }

    for (size_t i = 0; i < next.size(); i++)
    {
        next[i]->correct_recursive(y, measurement_id_);
    }
    
    
}