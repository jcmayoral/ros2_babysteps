#include <bump_detector/improved_obstacle_detector.h>

ObstacleImprovedDetectorNode::ObstacleImprovedDetectorNode() : Node("obstacle_detector"), tf_buffer_(),
    tf_listener_(tf_buffer_) {
    laser_sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
        "input_scan", rclcpp::SensorDataQoS(),
        std::bind(&ObstacleImprovedDetectorNode::scan_callback, this,
            std::placeholders::_1));
}


void ObstacleImprovedDetectorNode::scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg) {
    double dist = msg->ranges[msg->ranges.size() / 2];

    if (!std::isinf(dist)) {

        geometry_msgs::msg::TransformStamped odom2laser_msg;
        tf2::Stamped<tf2::Transform> odom2laser;

        try {
            odom2laser_msg = tf_buffer_.lookupTransform("odom", "base_laser_link",
                tf2::TimePointZero);
                //msg->header.stamp, rclcpp::Duration(200ms));
            tf2::fromMsg(odom2laser_msg, odom2laser);
        }
        catch (tf2::TransformException& ex) {
            RCLCPP_WARN(get_logger(), "Obstacle transform not found %s", ex.what());
        }

        //obstacle pose from laser link perspective
        tf2::Transform  laser2object;
        laser2object.setOrigin(tf2::Vector3(dist, 0.0, 0.0));
        laser2object.setRotation(tf2::Quaternion(0.0, 0.0, 0.0, 1.0));

        //obstacle in odom coordinates
        tf2::Transform odom2object = odom2laser * laser2object;

        geometry_msgs::msg::TransformStamped odom2object_msg;
        odom2object_msg.transform = tf2::toMsg(odom2object);
        odom2object_msg.header.stamp = msg->header.stamp;
        odom2object_msg.header.frame_id  = "odom";
        odom2object_msg.child_frame_id = "detected_obstacle";
        tf_broadcaster_->sendTransform(odom2object_msg);
    }
}
