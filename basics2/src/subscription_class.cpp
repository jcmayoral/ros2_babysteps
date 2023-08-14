#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

using namespace std::placeholders;

class SubscriptionNode : public rclcpp::Node{
    public: 
    SubscriptionNode(): Node("subscriber_node"){
        subscriber_ = this->create_subscription<std_msgs::msg::Int32>("int_topic", 10,
            std::bind(&SubscriptionNode::subscription_callback, this, _1));
    }

    void subscription_callback(const std_msgs::msg::Int32::SharedPtr msg){
        RCLCPP_INFO(get_logger(), "Hello %d", msg->data);
    }

    private:
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
    std_msgs::msg::Int32 message_;

};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    std::shared_ptr<SubscriptionNode> node = std::make_shared<SubscriptionNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
