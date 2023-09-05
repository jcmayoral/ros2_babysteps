#include <bumpgo/bumpogo.hpp>

BumpGo::BumpGo() : Node("bump_go")
{
    laser_sub_ = create_subscription<sensor_msgs::msg::LaserScan>("input_scan", rclcpp::SensorDataQos(),
        std::bind(&BumpGo::scan_callback, this, _1));
    vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);
    timer_ = create_wall_time(50ms, std::bind(&BumpGo::control_cycle, this));

}

BumpGo::~BumpGo(){
    
}

void BumpGo::scan_callback(cost sensor_msgs::msg::LaserScan::UniquePtr msg){

}

void BumpGo::control_cycle(){
    
}