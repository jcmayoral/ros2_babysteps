from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    pub_cmd = Node(
        package="br2_basics",
        executable="publisher_class",
        output="screen"
    )

    sub_cmd = Node(
        package="br2_basics",
        executable="subscription_class",
        output="screen"
    )

    ld = LaunchDescription()
    ld.add_action(pub_cmd)
    ld.add_action(sub_cmd)

    return ld
