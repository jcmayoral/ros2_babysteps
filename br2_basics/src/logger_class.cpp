#include <rclcpp/rclcpp.hpp>

class LoggerClass : public rclpp::Node{
    public:
    LoggerClass() : Node("logger_node"){
        counter_ = 0;
        timer_ = create_wall(500ms, 
            std::bind(&LoggerClass::timer_callback, this));
    }
    void timer_callback(){
        RCLCPP_INFO(get_logger(), "Hello %d", counter_++);
    }
    private:
    int counter_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv){
    rclcpp::init(argv, argv);
    std::shared_ptr<LoggerNode> node = std::make_shared<LoggerNode?>

    rclcpp::spin(node);
    rclcpp::shutdown();
    return;
}