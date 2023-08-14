from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    params_cmd = Node(
        package="br2_basics",
        executable="param_reader",
        output="screen",
        parameters= [{
            'particles' : 300,
            'topics' : ['scan', 'image'],
            'topics_types' : ['sensor_msgs/msgs/LaserScan',
                             'sensor_msgs/msg/Image']
        }]
    )

    ld = LaunchDescription()
    ld.add_action(params_cmd)

    return ld
