#include "target_hypothesis.h"

Target_Hypothesis::Target_Hypothesis()
{
    // Setup G and H matrices for the Kalman filter
    G.resize(6,6);
    H.resize(3,6);

    double dt = 1/double(FREQUENCY); 

    G << 1.0f, 0.0f, 0.0f, dt  , 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f, dt,   0.0f,
         0.0f, 0.0f, 1.0f, 0.0f, 0.0f, dt,
         0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f;
        
    H << 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f;
    
    // Transpose of G and H used in predict and correct
    GT = G.transpose();
    HT = H.transpose();
    
    // Define Q and R
    // TODO: Make this neater and better later
    Eigen::VectorXd Q_diag(6);
	Q_diag << 0.0, 0.0, 0.0, 0.1, 0.1, 0.1;
    double pos, vel, acc;
    double dt2, dt3;
    double tune = 0.15;
    dt2 = dt*dt;
    dt3 = dt2*dt;
    pos = 1.0/3.0 * dt3 * tune;
    vel = 1.0/2.0 * dt2 * tune;
    acc = dt * tune;
    Q.resize(6,6);
    Q << pos, 0, 0, vel, 0, 0,
          0, pos, 0, 0, vel, 0,
          0, 0, pos, 0, 0, vel,
          vel, 0, 0, acc, 0, 0,
          0, vel, 0, 0, acc, 0,
          0, 0, vel, 0, 0, acc;

    Eigen::VectorXd R_diag(3);
    R_diag << 0.5, 0.5, 0.5;
	R = Eigen::MatrixXd(R_diag.asDiagonal());

}

Target_Hypothesis::~Target_Hypothesis()
{
}

void Target_Hypothesis::init(Eigen::Vector3d y)
{
    mu.resize(6); // Assuming 6 states for the Gaussian Model: [eta; nu] ([position; velocity])
    cov.resize(6,6);

    Eigen::VectorXd cov_init(6);

    cov_init << 1, 1, 1, 2, 2, 2;

    cov = Eigen::MatrixXd(cov_init.asDiagonal());

    mu << y, 0, 0, 0;
}

void Target_Hypothesis::correct(Eigen::Vector3d y, Target_Hypothesis target_)
{
    mu = target_.get_mean();
    cov = target_.get_cov();
    correct(y);
}

Eigen::VectorXd Target_Hypothesis::get_mean(void)
{
    return mu;
}

Eigen::MatrixXd Target_Hypothesis::get_cov(void)
{
    return cov;
}

Eigen::VectorXd Target_Hypothesis::get_pos(void)
{
    return mu.head(3);
}

void Target_Hypothesis::predict(void)
{
    mu = Eigen::VectorXd(G*mu);
    
    cov = G*cov*GT + Q;
}

void Target_Hypothesis::correct(Eigen::Vector3d y)
{
    Eigen::MatrixXd S, K, KT;

    S = H*cov*HT + R;

    assert(S.rows() == 3);
    assert(S.cols() == 3);

    K = cov*HT*S.inverse();
    
    assert(K.rows() == 6);
    assert(K.cols() == 3);

    KT = K.transpose();

    assert(KT.rows() == 3);
    assert(KT.cols() == 6);

    mu = mu + Eigen::VectorXd(K*(y - Eigen::Vector3d(H*mu)));
    cov = cov - K*S*KT;

    assert(mu.rows() == 6);
    assert(mu.cols() == 1);
    assert(cov.rows() == 6);
    assert(cov.cols() == 6);
}

double Target_Hypothesis::mahalanobis_distance(Eigen::Vector3d y)
{
    Eigen::MatrixXd S = H*cov*HT + R;
    return (y - H*mu).transpose() * S.inverse() * (y - H*mu);
}