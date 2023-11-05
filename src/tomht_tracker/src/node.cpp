#include "node.h"

#include <iostream>

// Correct target estimate
Node::Node(Eigen::Vector3d y_, Target_Hypothesis target_, uint32_t target_id_, uint32_t measurement_id_)
    : target_id(target_id_), measurement_id(measurement_id_)
{
    // next.push_back(nullptr);
    // Correct the target estiamte with the measurement, or given a measurement it will add the node below the current node with the corrected state, not sure, up to future me
    clutter = false;

    target.correct(y_, target_);
}

// Generate new target estimate, this is the root node of a target hypothesis tree tree or a clutter measurement.
Node::Node(Eigen::Vector3d y_, uint32_t target_id_, uint32_t measurement_id_, bool clutter_)
    : target_id(target_id_), measurement_id(measurement_id_), clutter(clutter_)
{
    // next.push_back(nullptr);

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

uint32_t Node::tree_size(void)
{
    uint32_t sum = 1;
    tree_size_recursive(sum);
    return sum;
}

void Node::tree_size_recursive(uint32_t & sum)
{
    std::cout << "Size of Next vector: " << next.size() << std::endl;
    if (next.empty())
    {   
        // sum++;
        return;
    }
    
    for (size_t i = 0; i < next.size(); i++)
    {

        // std::cout << "Size of Next vector: " << next.size() << std::endl;
        sum++;
        next[i]->tree_size_recursive(sum);
    }

}

void Node::correct(Eigen::Vector3d y, uint32_t measurement_id_, std::vector<uint32_t> & associated_measurements)
{
    std::cout << "Recursive start" << std::endl;
    correct_recursive(y, measurement_id_, associated_measurements);
    std::cout << "Recursive end" << std::endl;

}

void Node::correct_recursive(Eigen::Vector3d y, uint32_t measurement_id_, std::vector<uint32_t> & associated_measurements)
{
    std::cout << "Recursive call, target_id: " << target_id << ", measurement_id: " << measurement_id_ << std::endl;
    measurement_id = measurement_id+0; // to prevent a warning (for now, can remove once measurement_id is used somewhere)

    if (next.empty())
    {
        // Add a leaf node, where the current target state is, perfom gating on this to determine which case to use
        uint32_t gate = gating(y);
        std::cout << "Gate: " << gate << std::endl;

        // This should be able to replace the above switch-case but it doesnt match, NEED TO INVESTIGATE AND FIX
        switch (gate)
        {
        case 1:
            associated_measurements.push_back(measurement_id_);
            add_node(y, target, target_id, measurement_id, false); // Target correction
            break;

        case 2:
            associated_measurements.push_back(measurement_id_);
            add_node(y, target, target_id, measurement_id, false); // Target correction
            add_node(y, target, target_id, measurement_id, true);  // Add clutter 
            break;
        
        case 3:
            add_node(y, target, target_id, measurement_id, false); // Target correction
            add_node(y, target, target_id, measurement_id, true);  // Add clutter 
            break;
        
        case 4:
            // Case 4 is spawn only, this involves not adding the measurement to the associated_measurements vector
            break;

        default:
            std::cerr << "Invalid gate case" << std::endl;
        }
        
        return;
        
    }

    for (size_t i = 0; i < next.size(); i++)
    {

        next[i]->correct_recursive(y, measurement_id_, associated_measurements);
        
    }
    
    
}

void Node::add_node(Eigen::Vector3d y, Target_Hypothesis target, uint32_t target_id, uint32_t measurement_id, bool clutter_flag)
{
    if (clutter_flag)
    {
        auto node = std::make_shared<Node>(y, target_id, measurement_id, clutter_flag); // If the current node is clutter, the target values will be spawned from this measurement
        next.push_back(std::move(node));
        return;
    }

    if (clutter)
    {
        // #NOTE1: This makes a new target from a previous clutter node
        auto node = std::make_shared<Node>(y, target_id, measurement_id, clutter_flag); // If the current node is clutter, the target values will be spawned from this measurement
        next.push_back(std::move(node));
    }
    else
    {
        auto node = std::make_shared<Node>(y, target, target_id, measurement_id); // If the node is not clutter, correct the target state
        next.push_back(std::move(node));
    }

}

void Node::predict(void)
{
    predict_recursive();
}

void Node::predict_recursive(void)
{
    if (next.size() == 1)
    {
        target.predict();
        
        return;
    }

    for (size_t i = 0; i < next.size(); i++)
    {
        if (next[i] != nullptr)
        {
            next[i]->predict();
        }
    }
}

/*
Case 1: Target correction only
Case 2: Target correction and Clutter
Case 3: Target correction, Clutter, Spawn
Case 4: Spawn only
*/
uint32_t Node::gating(Eigen::Vector3d y)
{
    double dist = target.mahalanobis_distance(y);

    // std::cout << "Target: \n" << target.get_pos() << std::endl;
    // std::cout << "y: \n" << y << std::endl;
    // std::cout << "mahalanobis_distance: " << dist << std::endl;

    // These dont work well, ill do my own >:)
    // if (dist >= GATE_997)
    // {
    //     return 1;
    // }
    // else if (dist >= GATE_95 && dist < GATE_997)
    // {
    //     return 2;
    // }
    // else if (dist >= GATE_68 && dist < GATE_95)
    // {
    //     return 3;
    // }
    // else
    // {
    //     return 4;
    // }

    if (dist < 0.2)
    {
        return 1;
    }
    else if (dist >= 0.2 && dist < 0.3)
    {
        return 2;
    }
    else if (dist >= 0.3 && dist < 0.5)
    {
        return 3;
    }
    else
    {
        return 4;
    }

}