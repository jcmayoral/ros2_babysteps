#include<rclcpp/rclcpp.h>

int main(int argc, char** argv){
    rclcpp::init(argc, argv);

    auto node = rrclcpp::Node::make_shared("simple_node");
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}