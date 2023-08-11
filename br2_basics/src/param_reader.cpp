#include <rclcpp/rclcpp.hpp>

class LocalizationNode : public rclcpp::Node {
    public:
    LocalizationNode() : Node("localization_node"){
        declare_parameter<int> ("number_particles", 200);
        declare_parameter<std::vector<std::string>> ("topics", {});
        declare_parameter<std::vector<std::string>> ("topics_types", {});

        RCLCPP_INFO(get_logger(), "inside node ");
        get_parameter("number_particles", number_particles_);
        RCLCPP_INFO_STREAM(get_logger(), " particles \t" << number_particles_);

        get_parameter("topics", topics_);
        get_parameter("topics_types", topics_types_);

        if (topics_.size() != topics_types_.size()){
            RCLCPP_ERROR(get_logger(), "number of topics %zu number of types %zu", topics_.size(), topics_types_.size());
        }
        else{
            for (size_t i = 0; i< topics_.size(); i++){
                RCLCPP_INFO_STREAM(get_logger(), "topic " << topics_[i] << " \t" << topics_types_[i]);
            }
        }
        
    }
    private:
    int number_particles_;
    std::vector<std::string> topics_;
    std::vector<std::string> topics_types_;
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    std::shared_ptr<LocalizationNode> node = std::make_shared<LocalizationNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
