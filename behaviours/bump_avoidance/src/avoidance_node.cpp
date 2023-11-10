#include <bump_avoidance/avoidance_node.h>

AvoidanceNode::AvoidanceNode() : Node("bump_avoidance")
{
  laser_sub_ = create_subscription<sensor_msgs::msg::LaserScan>("input_scan", rclcpp::SensorDataQoS(), std::bind(&AvoidanceNode::scan_callback, this, std::placeholders::_1));
  twist_pub_ = create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);
  vff_debug_pub_ = create_publisher<visualization_msgs::msg::MarkerArray>("debug_array", 10);

  timer_ = create_wall_timer(50ms, std::bind(&AvoidanceNode::control_cycle, this));
}

void AvoidanceNode::scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
{
  last_scan_ = std::move(msg);
}

void AvoidanceNode::control_cycle()
{
  if (last_scan_ == nullptr || (now() - last_scan_->header.stamp) > 1s)
    return;

  const VFFVectors& vff = get_vff(*last_scan_);

  //result vecotr
  const auto& v = vff.result;
  double angle = atan2(v[1], v[0]);
  double module = sqrt(pow(v[0], 2) + pow(v[1], 2));

  geometry_msgs::msg::Twist out_vel;
  out_vel.linear.x = std::clamp(module, 0.0, 0.3);
  out_vel.angular.z = std::clamp(angle, -0.5, 0.5);

  twist_pub_->publish(out_vel);


  if (vff_debug_pub_->get_subscription_count() > 0) {
    vff_debug_pub_->publish(get_debug_vff(vff));
  }
}

visualization_msgs::msg::MarkerArray AvoidanceNode::get_debug_vff(const VFFVectors& vectors) {
  visualization_msgs::msg::MarkerArray marker_array;
  marker_array.markers.push_back(make_marker(vectors.attractive, BLUE));
  marker_array.markers.push_back(make_marker(vectors.repulsive, RED));
  marker_array.markers.push_back(make_marker(vectors.result, GREEN));
  return marker_array;
}

visualization_msgs::msg::Marker AvoidanceNode::make_marker(
  const std::vector<float> & vector, VFFColors vff_color) {
  visualization_msgs::msg::Marker marker;
  marker.header.frame_id = "base_footprint";
  marker.header.stamp = now();
  marker.type = visualization_msgs::msg::Marker::ARROW;
  marker.id = visualization_msgs::msg::Marker::ADD;

  geometry_msgs::msg::Point start;
  start.x = vector[0];
  start.y = vector[1];
  start.z = 0.0;
  geometry_msgs::msg::Point end;

  marker.points = { start, end };
  marker.scale.x = 0.05;
  marker.scale.y = 0.1;

  switch (vff_color) {
  case RED:
    marker.id = 0;
    marker.color.r = 1.0;
    break;
  case GREEN:
    marker.id = 1;
      marker.color.g = 1.0;
    break;
  case BLUE:
    marker.id = 2;
    marker.color.b = 1.0;
    break;
  }
  marker.color.a = 1.0;
  return marker;



}

VFFVectors AvoidanceNode::get_vff(const sensor_msgs::msg::LaserScan& scan) {
  const float OBSTACLE_DISTANCE = 1.0;

  //init
  VFFVectors vff_vector;
  vff_vector.attractive = { OBSTACLE_DISTANCE, 0.0 };
  vff_vector.repulsive = { 0.0, 0.0 };
  vff_vector.result = { 1.0,0.0 };

  //nearest obstacle
  int min_idx = std::min_element(scan.ranges.begin(), scan.ranges.end()) - scan.ranges.begin();

  float distance_min = scan.ranges[min_idx];

  if (distance_min < OBSTACLE_DISTANCE) {
    float angle = scan.angle.min + scan.angle_increment * min_idx;
    float oposite_angle = angle + M_PI;
    //Mdodule of vector is inversot of distance to obstacle
    float complementary_distance = OBSTACLE_DISTANCE - distance_min;
    vff_vector.repulsive[0] = cos(oposite_angle) * complementary_distance;
    vff_vector.repulsive[1] = sin(oposite_angle) * complementary_distance;
  }

  vff_vector.result[0] = vff_vector.repulsive[0] + vff_vector.attractive[0];
  vff_vector.result[1] = vff_vector.repulsive[1] + vff_vector.attractive[1];
  return vff_vector;
}