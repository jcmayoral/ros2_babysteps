from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    print(FindPackageShare("br2_basics"))

    config = os.path.join(
        get_package_share_directory('br2_basics'),
        'config',
        'params.yaml'
    )
    print (config)
    params_cmd = Node(
        package="br2_basics",
        executable="param_reader",
        output="screen",
        parameters= [config]
    )

    ld = LaunchDescription()
    ld.add_action(params_cmd)

    return ld
