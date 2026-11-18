#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <iostream>
#include <memory>
#include <termios.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("node_pub1_3");

    auto publisher =
        node->create_publisher<geometry_msgs::msg::Twist>(
            "/turtle1/cmd_vel", 10);

    // 터미널 키보드 입력 설정 저장
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Enter 없이 한 글자씩 입력받기
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    geometry_msgs::msg::Twist message;
    char key;

    std::cout << "===== Turtle Control =====" << std::endl;
    std::cout << "f: 전진" << std::endl;
    std::cout << "b: 후진" << std::endl;
    std::cout << "l: 좌회전" << std::endl;
    std::cout << "r: 우회전" << std::endl;
    std::cout << "s: 정지" << std::endl;
    std::cout << "Ctrl+C: 종료" << std::endl;

    while (rclcpp::ok())
    {
        if (read(STDIN_FILENO, &key, 1) <= 0)
        {
            continue;
        }

        // 모든 속도를 초기화
        message.linear.x = 0.0;
        message.linear.y = 0.0;
        message.linear.z = 0.0;

        message.angular.x = 0.0;
        message.angular.y = 0.0;
        message.angular.z = 0.0;

        switch (key)
        {
            case 'f':
                message.linear.x = 2.0;
                std::cout << "\n전진" << std::endl;
                break;

            case 'b':
                message.linear.x = -2.0;
                std::cout << "\n후진" << std::endl;
                break;

            case 'l':
                message.angular.z = 2.0;
                std::cout << "\n좌회전" << std::endl;
                break;

            case 'r':
                message.angular.z = -2.0;
                std::cout << "\n우회전" << std::endl;
                break;

            case 's':
                std::cout << "\n정지" << std::endl;
                break;

            default:
                std::cout << "\n지원하지 않는 키입니다." << std::endl;
                break;
        }

        publisher->publish(message);
    }

    // 터미널 설정 복구
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    rclcpp::shutdown();
    return 0;
}