#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "cv_bridge/cv_bridge.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>

void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    if (frame.empty()) {
        RCLCPP_WARN(node->get_logger(), "Received empty frame");
        return;
    }

    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

    cv::Mat binary_frame;
    cv::threshold(gray_frame, binary_frame, 128, 255, cv::THRESH_BINARY);

    RCLCPP_INFO(node->get_logger(), "Received Image : %s, %d x %d", 
                msg->format.c_str(), frame.rows, frame.cols);

    cv::imshow("1. Original", frame);
    cv::imshow("2. Gray", gray_frame);
    cv::imshow("3. Binary", binary_frame);
    cv::waitKey(1);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imagesub");
    
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, std::placeholders::_1);
    
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>(
        "image/compressed", qos_profile, fn);
        
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
