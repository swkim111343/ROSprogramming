#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("pub2_3");

    // Publisher 생성
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>(
        "/turtle1/cmd_vel", 10);

    // 0.1초마다 메시지 발행
    auto timer = node->create_wall_timer(
        100ms,
        [pub, node]()
        {
            auto msg = geometry_msgs::msg::Twist();

            // 선속도
            msg.linear.x = 2.0;

            // 각속도
            msg.angular.z = 1.0;

            pub->publish(msg);

            RCLCPP_INFO(
                node->get_logger(),
                "Linear: %.2f, Angular: %.2f",
                msg.linear.x,
                msg.angular.z
            );
        }
    );

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}