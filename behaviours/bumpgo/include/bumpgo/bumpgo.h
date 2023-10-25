#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class BumpGo : public rclcpp::Node {
    private:
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        void control_cycle();

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        rclcpp::TimerBase::SharedPtr timer_;

        sensor_msgs::msg::LaserScan::UniquePtr last_scan_;

        static const int FORWARD = 0;
        static const int BACK = 1;
        static const int LEFT = 2;
        static const int RIGHT = 3;
        int state_;
        rclcpp::Time state_ts;
        
    public:
        BumpGo();
        ~BumpGo();

};