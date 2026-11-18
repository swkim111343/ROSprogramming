#ifndef IMAGE_PSUB1_3__PUB_HPP_
#define IMAGE_PSUB1_3__PUB_HPP_

#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"

#if __has_include("cv_bridge/cv_bridge.hpp")
  #include "cv_bridge/cv_bridge.hpp"
#else
  #include "cv_bridge/cv_bridge.h"
#endif

class ImagePublisher : public rclcpp::Node
{
public:
  explicit ImagePublisher(const std::string & video_path);
  ~ImagePublisher();

private:
  void timer_callback();

  rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
  std_msgs::msg::Header hdr_;
};

#endif  // IMAGE_PSUB1_3__PUB_HPP_