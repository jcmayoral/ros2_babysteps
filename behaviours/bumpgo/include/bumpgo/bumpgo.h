#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class BumpGo : public rclcpp::Node {
    private:
        void scan_callback(const sensor_msgs::msg::LaserScan::UniquePtr msg);
        void control_cycle();

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        rclcpp::TimerBase::SharedPtr timer_;
    public:
        BumpGo();
        ~BumpGo();

};