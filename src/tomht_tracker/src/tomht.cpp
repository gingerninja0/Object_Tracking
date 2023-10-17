#include <iostream>

#include "tomht.h"

TOMHT::TOMHT(/* args */)
{
}

TOMHT::~TOMHT()
{
}

    
void TOMHT::update(std::vector<Eigen::Vector3d> y_vec_)
{
    y_vec = y_vec_;
    std::cout << "TOMHT Spin!" << std::endl;

    gating();

    // Steps required and some prerequisite code/classes
    /*
    1. Gate measurements
        Mahalanobis distance and gating 

    2. Hypothesis Generation
        Tree
        There will a tree for each target estimate where each leaf is a different measurement association at the current time step and each branch is a different hypothesis of associations

    3. Measurement update
        Use 

    4. Calculate the global hypothesis

    5. Prune unlikely branches

    6. Prediction update
    
    
    */
    

}

void TOMHT::gating(void)
{
    // Recursive function to find the Mahalnobis distance to each target hypothesis. This will add the Mahalnobis distance and the associated measurement into each leaf node of the tree.

}




