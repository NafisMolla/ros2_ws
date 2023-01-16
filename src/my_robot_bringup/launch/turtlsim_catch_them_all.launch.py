from launch import LaunchDescription
from launch_ros.actions import Node

# ross will look for this function when trying to launch nodes with launch file


def generate_launch_description():
    ld = LaunchDescription()

    turtlesim = Node(
        package="turtlesim",
        executable="turtlesim_node"
    )

    turtle_spawner_node = Node(
        package="turtlesim_catch_them_all",
        executable="turtle_spawner",
        parameters=[
            {"spawn_frequency": 1}
        ]
    )

    turtle_controller_node = Node(
        package="turtlesim_catch_them_all",
        executable="turtle_controller",
        parameters=[
            {"get_closest": True}
        ]
    )

    ld.add_action(turtlesim)
    ld.add_action(turtle_spawner_node)
    ld.add_action(turtle_controller_node)


    return ld
