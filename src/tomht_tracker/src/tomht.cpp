#include <iostream>

#include "tomht.h"

TOMHT::TOMHT(/* args */)
{
    hypothesis_tree = std::make_unique<Tree>();
}

TOMHT::~TOMHT()
{
}

    
void TOMHT::update(std::vector<Eigen::Vector3d> y_vec_)
{
    y_vec = y_vec_;
    std::cout << "TOMHT Spin!" << std::endl;

    hypothesis_generation();

    // Steps required and some prerequisite code/classes
    /*
    0.5. Gate measurements, I tihnk I will do this inside of the hypothesis generation
        Mahalanobis distance and gating 

    1. Hypothesis Generation
        Tree
        There will a tree for each target estimate where each leaf is a different measurement association at the current time step and each branch is a different hypothesis of associations

    3. Measurement update
        Use 

    4. Calculate the global hypothesis

    5. Prune unlikely branches

    6. Prediction update
    
    
    */
    

}

void TOMHT::hypothesis_generation(void)
{
    // Use measurements to correct any existing target estimates
    std::vector<uint32_t> associated_measurements;
    hypothesis_tree->correct(y_vec, associated_measurements);
    // std::cout << "Size of used ids vector (after correction): " << used_target_ids.size() << std::endl;
    
    // Find which measurements are unassociated 
    
    std::vector<uint32_t> measurement_indices(y_vec.size());
    std::iota(measurement_indices.begin(), measurement_indices.end(), 0);
    std::sort(associated_measurements.begin(), associated_measurements.end());

    std::vector<uint32_t> unassociated_measurements;

    std::set_difference(measurement_indices.begin(), measurement_indices.end(), associated_measurements.begin(), associated_measurements.end(), std::back_inserter(unassociated_measurements));
    

    // Make new target estimates from measurements that werent associated, or were ou
    for (size_t i = 0; i < unassociated_measurements.size(); i++)
    {
        std::cout << "Add a target estimate" << std::endl;
        hypothesis_tree->add_target(y_vec[unassociated_measurements[i]], get_new_target_id(), unassociated_measurements[i]);
    }
    // std::cout << "unassociated_measurements.size(): " << unassociated_measurements.size() << std::endl;
    // std::cout << "Size of used ids vector (after spawning): " << used_target_ids.size() << std::endl;

    hypothesis_tree->predict();

    hypothesis_tree->print_size();

}



uint32_t TOMHT::get_new_target_id(void)
{
    uint32_t id_candidate = 0;
    // While the new id_candidate is within the used_ids list, find generate a new id_candidate
    while (true)
    {
        bool success = true;
        for (size_t i = 0; i < used_target_ids.size(); i++)
        {
            if (id_candidate == used_target_ids[i])
            {
                success = false;
                break;
            }
        }

        if (success)
        {
            break;
        }

        id_candidate++;
    }

    // Add id_candidate to used_ids list and return the new id (id_candidate)
    used_target_ids.push_back(id_candidate);
    return id_candidate;
}