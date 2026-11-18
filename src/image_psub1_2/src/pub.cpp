#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <string>

#if __has_include("cv_bridge/cv_bridge.hpp")
  #include "cv_bridge/cv_bridge.hpp"
#else
  #include "cv_bridge/cv_bridge.h"
#endif

std::string src = "/home/seonwookim/simulation/5_lt_cw_100rpm_out.mp4";

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imagepub");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile);

    std_msgs::msg::Header hdr;
    sensor_msgs::msg::CompressedImage::SharedPtr msg;
    rclcpp::WallRate loop_rate(30.0);

    cv::VideoCapture cap(src);
    if (!cap.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Could not open video: %s", src.c_str());
        rclcpp::shutdown();
        return -1;
    }

    RCLCPP_INFO(node->get_logger(), "Publishing video started...");

    cv::Mat frame;
    while (rclcpp::ok())
    {
        cap >> frame;
        if (frame.empty()) {
            RCLCPP_INFO(node->get_logger(), "Video finished. Shutting down pub...");
            break;
        }

        hdr.stamp = node->now();
        msg = cv_bridge::CvImage(hdr, "bgr8", frame).toCompressedImageMsg();
        mypub->publish(*msg);
        loop_rate.sleep();
    }

    cap.release();
    rclcpp::shutdown();
    return 0;
}