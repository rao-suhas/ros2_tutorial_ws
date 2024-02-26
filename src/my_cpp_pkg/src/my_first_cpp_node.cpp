#include "rclcpp/rclcpp.hpp"


class MyNode: public rclcpp::Node
{

    private:

        rclcpp::TimerBase::SharedPtr timer_;
        int counter_;

        void timerCallback()
        {
            RCLCPP_INFO(this->get_logger(), "Hello from timer: %s", std::to_string(counter_).c_str());
            counter_ ++;
        }

    public:
        MyNode() : Node("cpp_test"), counter_(0)
        {
            RCLCPP_INFO(this->get_logger(), "Hello CPP Node!");
            timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timerCallback, this));
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);
//     auto node = std::make_shared<rclcpp::Node>("cpp_test");
//     RCLCPP_INFO(node->get_logger(), "Hello CPP Node!");
//     // int i = 1;
//     // while (true)
//     // {
//     //     RCLCPP_INFO(node->get_logger(), "Hello cpp Node %s", std::to_string(i).c_str());
//     //     i +=1;
//     //     rclcpp::shutdown();
//     // }
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }