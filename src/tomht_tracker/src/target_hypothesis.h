#pragma once

#include <stdint.h>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "settings.h"

/*
* 
* Stores the state of the target that has been corrected by the measurement in the same node.
*
*/

class Target_Hypothesis
{
private:
        
    Eigen::VectorXd mu;
    Eigen::MatrixXd cov;

    // For the random walk model
    Eigen::MatrixXd G, H, GT, HT, Q, R;
    
public:
    Target_Hypothesis();
    ~Target_Hypothesis();

    // Will need functions for correction, prediction (this is the model of the target, ie Gaussian, Missile, Vehicle, etc), and some to query and set the state.
    void init(Eigen::Vector3d);
    void correct(Eigen::Vector3d, Target_Hypothesis);
    void correct(Eigen::Vector3d);
    void predict(void);

    Eigen::VectorXd get_pos(void);
    Eigen::VectorXd get_mean(void);
    Eigen::MatrixXd get_cov(void);

    double mahalanobis_distance(Eigen::Vector3d);
};


