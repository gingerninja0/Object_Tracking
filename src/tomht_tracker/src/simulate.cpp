#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <vector>

#include "simulate.h"
#include "tomht.h"
#include "settings.h"

template <typename T>
void print_vec(std::vector<T> vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << "Vec: " << i << std::endl << vec[i] << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    double time = 0.0; // Tracks the time since the thread was started
    double rate = FREQUENCY; // Frequency of the tracker/main loop
    rclcpp::Rate node_rate(rate);

    TOMHT tomht;

    std::vector<Eigen::Vector3d> y_vec;

    // Test 0
    y_vec.push_back(Eigen::Vector3d(1, 0, 0));

    std::cout << "\n\nUpdate 1\n" << std::endl << std::endl;
    tomht.update(y_vec);

    std::cout << "\n\nUpdate 2\n" << std::endl << std::endl;
    tomht.update(y_vec);

    std::cout << "\n\nSecond Measurement!!!\n\n" << std::endl;

    y_vec.push_back(Eigen::Vector3d(1, 1, 0)); // Add a second measurement

    std::cout << "\n\nUpdate 3\n" << std::endl << std::endl;

    tomht.update(y_vec);

    std::cout << "\n\nUpdate 4\n" << std::endl << std::endl;

    tomht.update(y_vec);
    
    std::cout << "\n\nUpdate 5\n" << std::endl << std::endl;

    tomht.update(y_vec);

    // Test 1
    // y_vec.push_back(Eigen::Vector3d(1, 0, 0));
    // y_vec.push_back(Eigen::Vector3d(1, 1, 0));

    // tomht.update(y_vec);
    // y_vec.clear();

    // y_vec.push_back(Eigen::Vector3d(1, 0, 0));
    // y_vec.push_back(Eigen::Vector3d(1, 1, 0));

    // tomht.update(y_vec);
    
    // Test 2
    // while (rclcpp::ok())
    // {
    //     // Simulate measurements
    //     y_vec.push_back(Eigen::Vector3d(sin(time*0.05), 0, 0));
    //     y_vec.push_back(Eigen::Vector3d(1, cos(time*0.1), 0));

    //     std::cout << time << std::endl;
    //     tomht.update(y_vec);
        
    //     time += 1.0/rate;
    //     node_rate.sleep();
    //     y_vec.clear();
    // }
    

    return 0;
}



