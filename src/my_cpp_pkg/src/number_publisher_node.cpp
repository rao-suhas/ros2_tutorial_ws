#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberPublisher: public rclcpp::Node
{
    private:
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;

        void publishNumber()
        {

        }

    public:

        NumberPublisher(): Node("number_publisher")
        {
            publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
            timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumberPublisher::publishNumber, this));
            
        }

};