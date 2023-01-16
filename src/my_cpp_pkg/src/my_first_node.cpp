#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
//to run we type "ros2 run my_cpp_pkg cpp_node"

class MyNode : public rclcpp::Node
{
public:
    // we are using inheritence to get the node constructor
    MyNode() : Node("cpp_test")
    {
        /*
        RCLCPP_INFO will have "node" output "hello cpp node"
        */
        counter_ = 0;
        RCLCPP_INFO(this->get_logger(), "hello cPP Node");
        /*
        we need to pass in the function refrence and we need to specify which object this class belongs too
        WE NEED TO USE BIND WHEN WE WANT TO PASS A FUNCTION INTO ANYTHING
        */
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "%d",counter_);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{

    /*
    we always intialize the ros2 library other wise we will not be able to use any of the functions
    */
    rclcpp::init(argc, argv);

    /*
    we pass in the name of the node that we want to create
    when using smart pointers the information in the round brackets is what gets passed into the constructor
    */
    auto node = std::make_shared<MyNode>();

    /*
    the spin function will not end out program right away, it will keeping it spinning the node we specified untill ctl c is pressed
    this function will expect a shared node pointer as its paramter
    */
    rclcpp::spin(node);

    /*
    shutdown wil end out program and do the nessearry clean up
    */
    rclcpp::shutdown();

    return 0;
}


/*

QUESTIONS
- what does it mean to install a node
-what does a named bus mean? 
-whats the package.xml and cmakelist.txt
-how would i know to use `auto msg = example_interfaces::msg::Int64();`

*/