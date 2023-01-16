#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node // MODIFY NAME
{

public:
    RobotNewsStationNode() : Node("Robot_news_station"), robot_name("R2D2") // MODIFY NAME
    {
        // we create/intitliasse the publisher with type String
        // we set the name and the size of the buffer
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&RobotNewsStationNode::publishNews, this));

        RCLCPP_INFO(this->get_logger(),"robot news station has been started.");
    }

private:
    // this is a published that publishes msg of type string, WE ALWAYS MAKE IT A SHARED POINTER
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;

    void publishNews()
    {
        // this is a shared pointer
        auto msg = example_interfaces::msg::String();
        // this is the actual msg
        msg.data = std::string("Hi, this is ") + robot_name;
        // this will actually publish the msg
        publisher_->publish(msg);
    }
    std::string robot_name;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
