#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include "tf2_ros/static_transform_broadcaster.h"

using namespace std::chrono_literals;

class ObstacleDetectorNode : public rclcpp::Node {
    public:
        ObstacleDetectorNode();
 
    private:
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_broadcaster_;
};