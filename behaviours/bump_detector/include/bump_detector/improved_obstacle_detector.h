#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>


using namespace std::chrono_literals;

class ObstacleImprovedDetectorNode : public rclcpp::Node {
    public:
        ObstacleImprovedDetectorNode();

    private:
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_broadcaster_;
        tf2::BufferCore tf_buffer_;
        tf2_ros::TransformListener tf_listener_;

};