#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoIntsClientNode : public rclcpp::Node // MODIFY NAME
{

public:
    AddTwoIntsClientNode() : Node("add_two_int_client") // MODIFY NAME
    {   
        //we need to check if the service got a response back in a new thread so we dont block of the code
        thread1_ = std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsServoce,this,1,4));

    }

    void callAddTwoIntsServoce(int a, int b)
    {
        //making the client
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        
        //waiting for the server to be up
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");
        }

        //since the server is up we make out request object
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        //we send the request
        auto future = client->async_send_request(request);

        //this will wait untill the reponse is given
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "%d + %d = %d", request->a, request->b, future.get()->sum);


    }

private:
    std::thread thread1_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClientNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
