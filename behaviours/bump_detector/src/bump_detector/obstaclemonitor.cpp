#include <bump_detector/obstacle_monitor.h>

ObstacleMonitorNode::ObstacleMonitorNode() :
    Node("obstacle_monitor"),
    tf_buffer_(),
    tf_listener_(tf_buffer_)
{
    marker_pub_ = create_publisher<visualization_msgs::msg::Marker>(
        "obstacle_marker", 1);
    timer_ = create_wall_timer(
        500ms, std::bind(&ObstacleMonitor::control_cycle, this));
}

ObstacleMonitorNode::control_cycle(){
    
    geometry_msgs::msg::TransformStamped robot2obstacle;

    try{
        robot2obstacle = tf_buffer_.lookupTransform(
            "base_footprint", "detected_obstacle", 
            tf2::TimePointZero();
        )
    }
    catch{
        RCLCPP_WARN(get_logger(x))
    }
    
}