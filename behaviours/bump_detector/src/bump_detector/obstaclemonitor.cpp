#include <bump_detector/obstacle_monitor.h>

ObstacleMonitorNode::ObstacleMonitorNode() :
    Node("obstacle_monitor"),
    tf_buffer_(),
    tf_listener_(tf_buffer_)
{
    marker_pub_ = create_publisher<visualization_msgs::msg::Marker>(
        "obstacle_marker", 1);
    timer_ = create_wall_timer(
        500ms, std::bind(&ObstacleMonitorNode::control_cycle, this));
}

void ObstacleMonitorNode::control_cycle() {

    geometry_msgs::msg::TransformStamped robot2obstacle;

    try {
        robot2obstacle = tf_buffer_.lookupTransform(
            "base_footprint", "detected_obstacle", tf2::TimePointZero);
    }
    catch (tf2::TransformException & ex) {
        RCLCPP_WARN(get_logger(), "Obstacle transform not fount %s", ex.what());
    }

    double x = robot2obstacle.transform.translation.x;
    double y = robot2obstacle.transform.translation.y;
    double z = robot2obstacle.transform.translation.z;
    double theta = atan2(y, x);

    RCLCPP_INFO(get_logger(), "obstacle detected %1f %1f %1f  %1f rads", x, y, z, theta);


    visualization_msgs::msg::Marker obstacle_marker;
    obstacle_marker.header.frame_id = "base_footprint";
    obstacle_marker.header.stamp = now();
    obstacle_marker.type = visualization_msgs::msg::Marker::ARROW;
    obstacle_marker.action = visualization_msgs::msg::Marker::ADD;
    obstacle_marker.lifetime = rclcpp::Duration(1s);

    geometry_msgs::msg::Point start;
    geometry_msgs::msg::Point end;
    start.x = start.y = start.z = 0.0;
    end.x = x;
    end.y = y;
    end.z = z;

    obstacle_marker.points = { start,end };
    obstacle_marker.color.r = 1.0;
    obstacle_marker.scale.x = 0.02;
    obstacle_marker.scale.y = 0.1;
    obstacle_marker.scale.z = 0.1;

    marker_pub_->publish(obstacle_marker);

}