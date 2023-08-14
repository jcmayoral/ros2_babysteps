from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    config = os.path.join(
        get_package_share_directory('basics2'),
        'config',
        'params.yaml'
    )

    params_cmd = Node(
        package="basics2",
        executable="param_reader",
        output="screen",
        parameters= [config]
    )

    ld = LaunchDescription()
    ld.add_action(params_cmd)

    return ld
