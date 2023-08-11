#include <rclcpp/rclcpp.h>
#include <std_msgs/msg/Int32.h>

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node{
    public: 
    PublisherNode(){
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("int_topic", 10);
        timer_ = this->create_wall_timer(500ms, boost::bind(&PublisherNode::timer_callback, this));
    }

    void timer_callback(){
        message_.data +=1;
        publisher_->publish(message_);
    }

    private:
    rclcpp::Publisher<std_msgs::msgs::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std_msgs::msgs::Int32 message_;


}