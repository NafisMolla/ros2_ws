#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/msg/turtle_array.hpp"
#include "my_robot_interfaces/srv/catch_turtle.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class TurtleSpawnerNode : public rclcpp::Node // MODIFY NAME
{

public:
    TurtleSpawnerNode() : Node("turtle_spawner"), turtle_counter_(0) // MODIFY NAME
    {
        //parameteres
        this->declare_parameter("spawn_frequency",1000);
        spawn_frequency = this->get_parameter("spawn_frequency").as_int();
        
        // have a default name
        turtle_name_prefix_ = "turtle";
        spawn_turtle_timer_ = this->create_wall_timer(std::chrono::milliseconds(spawn_frequency), std::bind(&TurtleSpawnerNode::spawnNewTurtle, this));

        alive_turtle_publisher_ = this->create_publisher<my_robot_interfaces::msg::TurtleArray>("alive_turtles", 10);

        publish_alive_turtles_timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&TurtleSpawnerNode::publish_alive_turtles, this));

        //make a service for when a turtle gets catched this will be the server
        catch_turtle_service_ = this->create_service<my_robot_interfaces::srv::CatchTurtle>("catch_turtle",std::bind(&TurtleSpawnerNode::callbackCatchTurtle,this,_1,_2));
    }

private:

    void callbackCatchTurtle(const my_robot_interfaces::srv::CatchTurtle::Request::SharedPtr request, 
    const my_robot_interfaces::srv::CatchTurtle::Response::SharedPtr response){
        
        kill_turtle_threads_.push_back(std::thread(std::bind(&TurtleSpawnerNode::call_kill_server,this,request->name)));
        // this->call_kill_server(request->name);
        response->success = true;

    }

    void call_kill_server(std::string name){

        // making the client
        auto client = this->create_client<turtlesim::srv::Kill>("kill");

        // waiting for the server to be up
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");
        }

        // since the server is up we make out request object
        auto request = std::make_shared<turtlesim::srv::Kill::Request>();
        request->name = name;
        

        // we send the request
        auto future = client->async_send_request(request);

        // if this is successful that means we have successfully spawned a new turtle
        //ALWAYS USE A TRY CATCH AND CHECK IF WE ACTUALLY GOT ANYTHING 
        try
        {
            //wait to get a response
            auto response = future.get();
            
            //find the turtle we just killed
            for(int i =0; i<(int)alive_turtles_.size();i++){
                if(alive_turtles_.at(i).name == name){
                    alive_turtles_.erase(alive_turtles_.begin() + i);
                    //update the list on the topic
                    publish_alive_turtles();
                    break;
                }
            }
            
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
        
    }


    // get a randome number in between 0 and 1
    double randomDouble()
    {
        return double(std::rand()) / (double(RAND_MAX) + 1.0);
    }

    void spawnNewTurtle()
    {

        turtle_counter_++;

        auto name = turtle_name_prefix_ + std::to_string(turtle_counter_);

        double x = randomDouble() * 10.0;
        double y = randomDouble() * 10.0;
        double theta = randomDouble() * 2 * M_PI;

        spawn_turtle_threads_.push_back(std::thread(std::bind(&TurtleSpawnerNode::call_spawn_server, this, x, y, theta, name)));
    }

    void call_spawn_server(double x, double y, double theta, std::string name)
    {
        // making the client
        auto client = this->create_client<turtlesim::srv::Spawn>("spawn");

        // waiting for the server to be up
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");
        }

        // since the server is up we make out request object
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
        request->x = x;
        request->y = y;
        request->theta = theta;
        request->name = name;

        // we send the request
        auto future = client->async_send_request(request);

        // if this is successful that means we have successfully spawned a new turtle
        //ALWAYS USE A TRY CATCH AND CHECK IF WE ACTUALLY GOT ANYTHING 
        try
        {
            auto response = future.get();
            if (response->name != "")//IMPORTANT LINE, WE ARE CHECKING IF WE ACTUALLY GOT ANYYTHING
            {
                auto new_turtle = my_robot_interfaces::msg::Turtle();
                new_turtle.name = response->name;
                new_turtle.x = x;
                new_turtle.y = y;
                new_turtle.theta = theta;
                alive_turtles_.push_back(new_turtle);
                publish_alive_turtles();
                RCLCPP_INFO(this->get_logger(), "Turtle %s is now alive.", response->name.c_str());
            }
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
    }

    // this function will publish the cordinates of the turtles
    void publish_alive_turtles()
    {
        auto msg = my_robot_interfaces::msg::TurtleArray();
        msg.turtles = alive_turtles_;
        alive_turtle_publisher_->publish(msg);
    }

    std::string turtle_name_prefix_;
    // how many turtles are active
    int turtle_counter_;
    // for the wall timer
    rclcpp::TimerBase::SharedPtr spawn_turtle_timer_;
    // vector with all our threads
    std::vector<std::thread> spawn_turtle_threads_;
    std::vector<std::thread> kill_turtle_threads_;
    //spawn freqeuncy
    int spawn_frequency;

    // publisher
    rclcpp::Publisher<my_robot_interfaces::msg::TurtleArray>::SharedPtr alive_turtle_publisher_;
    // this holds the coordintes for all the alive turtles
    std::vector<my_robot_interfaces::msg::Turtle> alive_turtles_;

    rclcpp::TimerBase::SharedPtr publish_alive_turtles_timer_;

    rclcpp::Service<my_robot_interfaces::srv::CatchTurtle>::SharedPtr catch_turtle_service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawnerNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
