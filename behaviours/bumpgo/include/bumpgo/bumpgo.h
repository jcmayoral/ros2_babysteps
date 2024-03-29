#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class BumpGo : public rclcpp::Node {
    struct obstacles
    {
        float left;
        float right;
    };
    protected:
        rclcpp::Duration ROTATION_TIME;
    
    private:
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        void control_cycle();
        void go_state(int new_state);
        bool check_forward_2_back();
        bool check_forward_2_stop();
        bool check_stop_2_forward();
        bool check_back_2_turn();
        bool check_turn_2_forward();
        void check_sides(struct obstacles& obstacles);
        void calc_rotation();

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
        rclcpp::TimerBase::SharedPtr timer_;

        sensor_msgs::msg::LaserScan::UniquePtr last_scan_;

        static const int FORWARD = 0;
        static const int BACK = 1;
        static const int TURN = 2;
        static const int STOP = 3;

        const rclcpp::Duration TURNING_TIME {2s};
        const rclcpp::Duration BACKING_TIME {2s};
        const rclcpp::Duration SCAN_TIMEOUT {1s};
    
        static constexpr float SPEED_LINEAR = 0.3f;
        static constexpr float SPEED_ANGULAR = 0.3f;
        static constexpr float OBSTACLE_DISTANCE = 1.0f;
        float ROTATION_SPEED;
        int state_;
        rclcpp::Time state_ts_;
        
    public:
        BumpGo();
        ~BumpGo();

};