#include <rclcpp/rclcpp.hpp>
#include <iostream>

#include "simulate.h"
#include "tomht.h"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    double time = 0.0; // Tracks the time since the thread was started
    double rate = 30.0; // Frequency of the tracker/main loop
    rclcpp::Rate node_rate(rate);

    tomht::spin();


    while (rclcpp::ok())
    {
        
        std::cout << time << std::endl;
        
        time += 1.0/rate;
        node_rate.sleep();
    }
    

    return 0;
}


