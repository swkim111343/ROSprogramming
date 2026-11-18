#ifndef IMAGE_PSUB1_3__SUB_HPP_
#define IMAGE_PSUB1_3__SUB_HPP_

#include <memory>
#include <string>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"

#if __has_include("cv_bridge/cv_bridge.hpp")
  #include "cv_bridge/cv_bridge.hpp"
#else
  #include "cv_bridge/cv_bridge.h"
#endif

class ImageSubscriber : public rclcpp::Node
{
public:
  explicit ImageSubscriber(const std::string & output_filename);
  ~ImageSubscriber();

private:
  void sub_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
  void watchdog_callback();

  rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_;
  rclcpp::TimerBase::SharedPtr watchdog_timer_;
  cv::VideoWriter writer_;
  bool is_writer_init_;
  std::string output_filename_;
  double fps_;
  std::chrono::steady_clock::time_point last_msg_time_;
};

#endif  // IMAGE_PSUB1_3__SUB_HPP_