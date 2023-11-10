#include <rclcpp/rclcpp.hpp>
#include <bump_avoidance/avoidance_node.h>

int main(int argc, char ** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AvoidanceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}