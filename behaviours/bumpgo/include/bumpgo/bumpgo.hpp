#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/LaserScan.h>
#include <geometry_msgs/msg/Twist.h>

class BumpGo : public rclpp::Node {
    private:
        void scan_callback(cost sensor_msgs::msg::LaserScan::UniquePtr msg);
        void control_cycle();

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        rclcpp::TimeBase::SharedPtr timer_;
    public:
        BumpGo();
        ~BumpGo();

}