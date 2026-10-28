#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <iostream>
#include <memory>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("node_pub1_2");

    auto publisher =
        node->create_publisher<geometry_msgs::msg::Vector3>(
            "topic_pub1_2", 10);

    geometry_msgs::msg::Vector3 message;

    while (rclcpp::ok())
    {
        std::cout << "실수 3개 입력 (x y z): ";

        if (!(std::cin >> message.x >> message.y >> message.z))
        {
            break;
        }

        publisher->publish(message);

        RCLCPP_INFO(
            node->get_logger(),
            "Published: x=%.2f, y=%.2f, z=%.2f",
            message.x, message.y, message.z);

        rclcpp::spin_some(node);
    }

    rclcpp::shutdown();
    return 0;
}