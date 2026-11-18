#include "image_psub1_3/pub.hpp"
#include <chrono>

using namespace std::chrono_literals;

ImagePublisher::ImagePublisher(const std::string & video_path)
: Node("imagepub")
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  pub_ = this->create_publisher<sensor_msgs::msg::CompressedImage>("image/compressed", qos_profile);

  cap_.open(video_path);
  if (!cap_.isOpened()) {
    RCLCPP_ERROR(this->get_logger(), "Could not open video: %s", video_path.c_str());
    rclcpp::shutdown();
    return;
  }

  RCLCPP_INFO(this->get_logger(), "Publishing video started...");
  timer_ = this->create_wall_timer(33ms, std::bind(&ImagePublisher::timer_callback, this));
}

ImagePublisher::~ImagePublisher()
{
  if (cap_.isOpened()) {
    cap_.release();
  }
}

void ImagePublisher::timer_callback()
{
  cv::Mat frame;
  cap_ >> frame;
  if (frame.empty()) {
    RCLCPP_INFO(this->get_logger(), "Video finished. Shutting down pub...");
    timer_->cancel();
    rclcpp::shutdown();
    return;
  }

  hdr_.stamp = this->now();
  auto msg = cv_bridge::CvImage(hdr_, "bgr8", frame).toCompressedImageMsg();
  pub_->publish(*msg);
}