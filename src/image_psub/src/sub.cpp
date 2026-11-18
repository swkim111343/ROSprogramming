#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "cv_bridge/cv_bridge.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>

void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    // 압축된 이미지 메시지를 OpenCV Mat(bgr8) 형식으로 변환
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    
    if (frame.empty()) {
        RCLCPP_WARN(node->get_logger(), "Received empty frame");
        return;
    }

    RCLCPP_INFO(node->get_logger(), "Received Image : %s, %d x %d", 
                msg->format.c_str(), frame.rows, frame.cols);

    // 영상 화면 출력
    cv::imshow("wsl", frame);
    cv::waitKey(1);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imagesub");
    
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); // TCP
    // auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort(); // UDP
    
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, std::placeholders::_1);
    
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>(
        "image/compressed", qos_profile, fn);
        
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
