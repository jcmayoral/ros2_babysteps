#include <bumpgo/bumpgo.h>

BumpGo::BumpGo() : Node("bump_go"), state_{FORWARD}
{
    laser_sub_ = create_subscription<sensor_msgs::msg::LaserScan>("input_scan", rclcpp::SensorDataQoS(),
                                                                  std::bind(&BumpGo::scan_callback, this, std::placeholders::_1));
    twist_pub_ = create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);
    timer_ = create_wall_timer(50ms, std::bind(&BumpGo::control_cycle, this));
    state_ts_ = now();
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
    if (last_scan_ == nullptr)
        return;

    geometry_msgs::msg::Twist out_vel;

    switch (state_)
    {
    case FORWARD:
        out_vel.linear.x = SPEED_LINEAR;
    
        if (check_forward_2_stop())
            go_state(STOP);
        if (check_forward_2_back())
            go_state(BACK);
        break;

    case BACK:
      out_vel.linear.x = -SPEED_LINEAR;

      if (check_back_2_turn()) {
        go_state(TURN);
      }

      break;
    case TURN:
      out_vel.angular.z = SPEED_ANGULAR;
      struct obstacles obst;
      check_sides(obst);

      if (obst.right> obst.left){
        out_vel.angular.z = -SPEED_ANGULAR;
      }

      if (check_turn_2_forward()) {
        go_state(FORWARD);
      }

      break;
    case STOP:
      if (check_stop_2_forward()) {
        go_state(FORWARD);
      }
      break;
    }

    twist_pub_->publish(out_vel);
}

void BumpGo::go_state(int new_state)
{
    state_ = new_state;
    state_ts_ = now();
}


bool BumpGo::check_forward_2_back()
{
    size_t pos = last_scan_ -> ranges.size() /2;
    return last_scan_ -> ranges[pos] < OBSTACLE_DISTANCE;
}

bool BumpGo::check_forward_2_stop()
{
    auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
    return elapsed > SCAN_TIMEOUT;
}

bool BumpGo::check_stop_2_forward()
{
  auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
  return elapsed < SCAN_TIMEOUT;
}

bool BumpGo::check_back_2_turn()
{
    return (now() - state_ts_) > BACKING_TIME;

}

bool BumpGo::check_turn_2_forward()
{
  return (now() - state_ts_) > TURNING_TIME;
}

void BumpGo::check_sides(struct obstacles& obstacles){
  auto ranges = last_scan_ -> ranges;
  obstacles.left = ranges[0];
  obstacles.right = ranges[ranges.size()-1];

  RCLCPP_INFO(get_logger(), "R1 %f ", ranges[ranges.size()-1]);
  RCLCPP_WARN(get_logger(), "R2 %f ", last_scan_ -> ranges[-2]);

}
