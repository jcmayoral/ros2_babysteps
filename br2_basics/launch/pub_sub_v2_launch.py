from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
        Node(
            package='br2_basics',
            executable='publisher_class',
            output='screen'
        ),
        Node(
            package='br2_basics',
            executable='subscription_class',
            output='screen'
        )
    ])