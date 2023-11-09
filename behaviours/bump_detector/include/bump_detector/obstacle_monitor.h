#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker.hpp>

using namespace std::chrono_literals;

class ObstacleMonitorNode : public rclcpp::Node {
public:
    ObstacleMonitorNode();

private:
    void control_cycle();
    rclcpp::TimerBase::SharedPtr timer_;
    tf2::BufferCore tf_buffer_;
    tf2_ros::TransformListener tf_listener_;

    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
};