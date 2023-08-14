from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
        Node(
            package='basics2',
            executable='publisher_class',
            output='screen'
        ),
        Node(
            package='basics2',
            executable='subscription_class',
            output='screen'
        )
    ])