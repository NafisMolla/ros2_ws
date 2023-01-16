#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartPhoneNode : public rclcpp::Node // MODIFY NAME
{

public:
    SmartPhoneNode() : Node("smartPhone") // MODIFY NAME
    {   

        // since we are passing in a parameter into the callback we need to use placeholdres
        subscriber_ = this->create_subscription<example_interfaces::msg::String>("robot_news", 10, 
        std::bind(&SmartPhoneNode::callbackRobotnews, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(),"smartphone has been started");

    }

private:
    void callbackRobotnews(const example_interfaces::msg::String::SharedPtr msg)
    {
        // we hard to turn the std::msg::string into just a Std::string
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
