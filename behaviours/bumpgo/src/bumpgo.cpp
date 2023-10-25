#include <bumpgo/bumpgo.h>

BumpGo::BumpGo() : Node("bump_go"), state_{FORWARD}
{
    laser_sub_ = create_subscription<sensor_msgs::msg::LaserScan>("input_scan", rclcpp::SensorDataQoS(),
                                                                  std::bind(&BumpGo::scan_callback, this, std::placeholders::_1));
    twist_pub_ = create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);
    timer_ = create_wall_timer(50ms, std::bind(&BumpGo::control_cycle, this));
}

BumpGo::~BumpGo()
{
}

void BumpGo::scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
{
    last_scan_ = std::move(msg);
}

void BumpGo::control_cycle()
{
    if(last_scan_ == nullptr)
        return;
    twist_pub_->publish(geometry_msgs::msg::Twist());
}