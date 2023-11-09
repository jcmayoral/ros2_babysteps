#include <rclcpp/rclcpp.hpp>
#include <bump_detector/obtacle_detector.h>

int main(int argc, char ** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObstacleDetectorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}