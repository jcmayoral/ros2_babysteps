#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class LoggerClass : public rclcpp::Node{
    public:
    LoggerClass() : Node("logger_node"){
        counter_ = 0;
        timer_ = create_wall_timer(500ms, 
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
    rclcpp::init(argc, argv);
    std::shared_ptr<LoggerClass> node = std::make_shared<LoggerClass>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}