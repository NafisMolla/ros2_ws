#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberPublisherNode : public rclcpp::Node // MODIFY NAME
{

public:
    NumberPublisherNode() : Node("number_publisher") // MODIFY NAME
    {
        //this is how we set a parameter
        this->declare_parameter("number_to_publish",2);
        number_ = this->get_parameter("number_to_publish").as_int();
        
        publisher_ = create_publisher<example_interfaces::msg::Int64>("number",10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumberPublisherNode::publish_callback, this));

        RCLCPP_INFO(this->get_logger(),"Number publisher has been started.");

    }
private:

    //publisher object
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;

    void publish_callback(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = number_;
        this->publisher_->publish(msg);

    }
    rclcpp::TimerBase::SharedPtr timer_;
    int number_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
