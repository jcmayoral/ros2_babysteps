#include <rclcpp/rclcpp.hpp>
#include <bumpgo/bumpgo.h>

int main(int argc, char ** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BumpGo>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}