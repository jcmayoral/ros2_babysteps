#include <rclcpp/rclcpp.hpp>
#include <bump_detector/improved_obstacle_detector.h>
#include <bump_detector/obstacle_monitor.h>

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto detector_node = std::make_shared<ObstacleImprovedDetectorNode>();
    auto monitor_node = std::make_shared<ObstacleMonitorNode>();

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(detector_node);//->get_node_base_interface());
    executor.add_node(monitor_node);//->get_node_base_interface());
    executor.spin();
    rclcpp::shutdown();

    return 0;
}