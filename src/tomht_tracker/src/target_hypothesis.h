#pragma once

#include <stdint.h>
#include <Eigen/Core>

/*
* 
* Stores the state of the target that has been corrected by the measurement in the same node.
*
*/

class Target_Hypothesis
{
private:
        
    Eigen::VectorXd x;
    
public:
    Target_Hypothesis(Eigen::Vector3d);
    ~Target_Hypothesis();
    // Will need functions for correction, prediction (this is the model of the target, ie Gaussian, Missile, Vehicle, etc), and some to query and set the state.
};


