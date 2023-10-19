#include "target_hypothesis.h"

Target_Hypothesis::Target_Hypothesis()
{

}

Target_Hypothesis::~Target_Hypothesis()
{
}

void Target_Hypothesis::init(Eigen::Vector3d y_)
{
    x.resize(6); // Assuming 6 states for the Gaussian Model: [eta; nu] ([position; velocity])

    x << y_, 0, 0, 0;
}

void Target_Hypothesis::correct(Eigen::Vector3d y_, Target_Hypothesis target_)
{
    x = target_.get_state();
    correct(y_);
}

void Target_Hypothesis::correct(Eigen::Vector3d y_)
{
    x << y_, 0, 0, 0; // At the moment we will just update the state instead of correcting it properly
}

Eigen::VectorXd Target_Hypothesis::get_state(void)
{
    return x;
}