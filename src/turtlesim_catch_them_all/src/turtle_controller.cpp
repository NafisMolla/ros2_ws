
#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "my_robot_interfaces/srv/catch_turtle.hpp"

class TurtleControllerNode : public rclcpp::Node
{
public:
    TurtleControllerNode() : Node("turtle_controller"), name_("turtle1"), turtlesim_up_(false)
    {

        //getting the parameters
        this->declare_parameter("get_closest",true);
        get_closest = this->get_parameter("get_closest").as_bool();

        cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
            name_ + "/cmd_vel", 10);
        pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            name_ + "/pose", 10, std::bind(&TurtleControllerNode::callbackPose, this, std::placeholders::_1));
        turtles_to_catch_subscriber_ = this->create_subscription<my_robot_interfaces::msg::TurtleArray>(
            "alive_turtles", 10, std::bind(&TurtleControllerNode::callbackTurtlesToCatch, this, std::placeholders::_1));

        control_loop_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&TurtleControllerNode::controlLoop, this));
    }

private:
    void call_catch_turtle_server(std::string name)
    {

        // making the client
        auto client = this->create_client<my_robot_interfaces::srv::CatchTurtle>("catch_turtle");

        // waiting for the server to be up
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");
        }

        // since the server is up we make out request object
        auto request = std::make_shared<my_robot_interfaces::srv::CatchTurtle::Request>();
        request->name = name;

        // we send the request
        auto future = client->async_send_request(request);

        // if this is successful that means we have successfully spawned a new turtle
        // ALWAYS USE A TRY CATCH AND CHECK IF WE ACTUALLY GOT ANYTHING
        try
        {
            // wait to get a response
            auto response = future.get();

            // find the turtle we just killed
            if (response->success)
            {
                RCLCPP_INFO(this->get_logger(), "GOT TURTLE.");
            }
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
    }

    void callbackPose(const turtlesim::msg::Pose::SharedPtr pose)
    {
        pose_ = *pose.get();
        turtlesim_up_ = true;
    }

    void callbackTurtlesToCatch(const my_robot_interfaces::msg::TurtleArray::SharedPtr msg)
    {
        if (!msg->turtles.empty())
        {

            if (get_closest)
            {
                my_robot_interfaces::msg::Turtle tmpTurtle = msg->turtles.at(0);
                int closestDistance = 1000;
                for (int i = 1; i < (int)msg->turtles.size(); i++)
                {
                    double dist_x = msg->turtles.at(i).x - pose_.x;
                    double dist_y = msg->turtles.at(i).y - pose_.y;
                    double distance = std::sqrt(dist_x * dist_x + dist_y * dist_y);

                    if (distance < closestDistance)
                    {
                        closestDistance = distance;
                        tmpTurtle = msg->turtles.at(i);
                    }
                }
                turtle_to_catch_ = tmpTurtle;
            }

            else
            {
                turtle_to_catch_ = msg->turtles.at(0);
            }
        }
    }

    void publishCmdVel(double x, double theta)
    {
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = x;
        msg.angular.z = theta;
        cmd_vel_publisher_->publish(msg);
    }

    void controlLoop()
    {
        if (!turtlesim_up_ || turtle_to_catch_.name == "")
        {
            return;
        }

        double dist_x = turtle_to_catch_.x - pose_.x;
        double dist_y = turtle_to_catch_.y - pose_.y;
        double distance = std::sqrt(dist_x * dist_x + dist_y * dist_y);

        auto msg = geometry_msgs::msg::Twist();

        if (distance > 0.5)
        {
            // position
            msg.linear.x = 2 * distance;

            // orientation
            double steering_angle = std::atan2(dist_y, dist_x);
            double angle_diff = steering_angle - pose_.theta;
            if (angle_diff > M_PI)
            {
                angle_diff -= 2 * M_PI;
            }
            else if (angle_diff < -M_PI)
            {
                angle_diff += 2 * M_PI;
            }
            msg.angular.z = 6 * angle_diff;
        }
        else
        {
            // target reached!
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
            catch_turtle_threads.push_back(std::thread(std::bind(&TurtleControllerNode::call_catch_turtle_server, this, turtle_to_catch_.name)));
            turtle_to_catch_.name = "";
        }

        cmd_vel_publisher_->publish(msg);
    }

    std::string name_;
    turtlesim::msg::Pose pose_;
    bool turtlesim_up_;
    my_robot_interfaces::msg::Turtle turtle_to_catch_;
    std::vector<std::thread> catch_turtle_threads;

    bool get_closest;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::Subscription<my_robot_interfaces::msg::TurtleArray>::SharedPtr turtles_to_catch_subscriber_;
    rclcpp::TimerBase::SharedPtr control_loop_timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControllerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}