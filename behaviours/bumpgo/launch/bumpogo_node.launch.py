import os

from launch import LaunchDescription
from launch_ros.actions import Node



def generate_launch_description():

    params_cmd = Node(
        package="bumpgo",
        executable="bumpgo_node",
        output="screen",
        parameters= [{
            'use_sim_time' : True,
        }],
        remappings=[
            ('input_scan', '/scan_raw'),
            ('output_vel', '/nav_vel')
        ]
    )

    ld = LaunchDescription()
    ld.add_action(params_cmd)

    return ld