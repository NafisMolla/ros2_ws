#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class NumberCounterNode : public rclcpp::Node // MODIFY NAME
{

public:
    NumberCounterNode() : Node("number_counter"), counter(0) // MODIFY NAME
    {
        // setup subscirber
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10,
                                                                                std::bind(&NumberCounterNode::subscriber_callback, this, std::placeholders::_1));

        // setup publisher
        publisher_ = create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        // timer_ = this->create_wall_timer(std::chrono::seconds(1),std::bind(&NumberCounterNode::publisher_callback,this));
        server_ = this->create_service<example_interfaces::srv::SetBool>("reset_count" ,std::bind(&NumberCounterNode::callBoolService,this,_1,_2));
        RCLCPP_INFO(this->get_logger(),"service server has been started");
        

    }

    void callBoolService(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                              const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if(request->data){
            counter = 0;
            response->message = "counter has been reset";
            response->success = true;
        }

        else{
            response->message = "counter has been NOT reset";
            response->success = false;
        }

    }

    ////////////////////////////////////////////////

private:
    // callback for subsciber
    void subscriber_callback(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        this->counter++;
        auto msg_ = example_interfaces::msg::Int64();
        msg_.data = counter;
        this->publisher_->publish(msg_);
    }
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
    

    // subsciber object
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;

    // publisher object
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;

    // timer object
    rclcpp::TimerBase::SharedPtr timer_;

    // count variable
    int counter;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
