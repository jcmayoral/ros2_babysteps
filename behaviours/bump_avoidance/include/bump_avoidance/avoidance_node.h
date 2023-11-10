#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

struct VFFVectors
    {
        std::vector<float> attractive;
        std::vector<float> repulsive;
        std::vector<float> result;
    };
    

class AvoidanceNode : public rclcpp::Node {
    protected:
        VFFVectors get_vff(const sensor_msgs::msg::LaserScan & scan);
    
    private:
  
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        rclcpp::TimerBase::SharedPtr timer_;

        sensor_msgs::msg::LaserScan::UniquePtr last_scan_;  
        
    public:
        AvoidanceNode();
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        void control_cycle();

};