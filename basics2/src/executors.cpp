#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node{
    public: 
    PublisherNode(): Node("publisher_node"){
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("int_topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&PublisherNode::timer_callback, this));
    }

    void timer_callback(){
        message_.data +=1;
        publisher_->publish(message_);
    }

    private:
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std_msgs::msg::Int32 message_;

};

class SubscriptionNode : public rclcpp::Node{
    public: 
    SubscriptionNode(): Node("subscription_node"){
        subscriber_ = this->create_subscription<std_msgs::msg::Int32>("int_topic", 10,
            std::bind(&SubscriptionNode::subscription_callback, this, std::placeholders::_1));
    }

    void subscription_callback(const std_msgs::msg::Int32::SharedPtr msg){
        RCLCPP_INFO(get_logger(), "Hello world %d", msg->data);
    }

    private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
    std_msgs::msg::Int32 message_;

};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node_pub = std::make_shared<PublisherNode>();
    auto node_sub = std::make_shared<SubscriptionNode>();

    //Difference Single Thread or Multi to optimize management
    //rclcpp::executors::SingleThreadedExecutor executor;
    rclcpp::executors::MultiThreadedExecutor executor(
        rclcpp::executor::ExecutorArgs(), 8
    );

    executor.add_node(node_pub);
    executor.add_node(node_sub);

    executor.spin();

}