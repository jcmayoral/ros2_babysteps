from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
        Node(
            package='br2_basics',
            executable='publisher',
            output='screen'
        ),
        Node(
            package='br2_basics',
            executable='subscriber_class',
            output='screen'
        )
    ])