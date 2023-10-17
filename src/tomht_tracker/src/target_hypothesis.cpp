#include "target_hypothesis.h"

Target_Hypothesis::Target_Hypothesis(Eigen::Vector3d y_)
{
    x.resize(6); // Assuming 6 states for the Gaussian Model: [eta; nu] ([position; velocity])

    x << y_, 0, 0, 0;
}

Target_Hypothesis::~Target_Hypothesis()
{
}