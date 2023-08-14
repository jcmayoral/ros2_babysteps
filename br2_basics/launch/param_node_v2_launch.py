from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    params_file = "install/br2_basics/share/br2_basics/config/params.yaml"
    params_cmd = Node(
        package="br2_basics",
        executable="param_reader",
        output="screen",
        parameters= [params_file]
    )

    ld = LaunchDescription()
    ld.add_action(params_cmd)

    return ld
