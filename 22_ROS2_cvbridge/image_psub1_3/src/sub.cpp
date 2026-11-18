#include "image_psub1_3/sub.hpp"

using namespace std::chrono_literals;

ImageSubscriber::ImageSubscriber(const std::string & output_filename)
: Node("imagesub"),
  is_writer_init_(false),
  output_filename_(output_filename),
  fps_(30.0),
  last_msg_time_(std::chrono::steady_clock::now())
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));

  sub_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
    "image/compressed", qos_profile,
    std::bind(&ImageSubscriber::sub_callback, this, std::placeholders::_1));

  watchdog_timer_ = this->create_wall_timer(
    500ms, std::bind(&ImageSubscriber::watchdog_callback, this));

  RCLCPP_INFO(this->get_logger(), "Waiting for video stream...");
}

ImageSubscriber::~ImageSubscriber()
{
  if (writer_.isOpened()) {
    writer_.release();
    RCLCPP_INFO(this->get_logger(), "Saved video to %s", output_filename_.c_str());
  }
  cv::destroyAllWindows();
}

void ImageSubscriber::sub_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
  last_msg_time_ = std::chrono::steady_clock::now();

  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  } catch (cv_bridge::Exception & e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
    return;
  }

  cv::Mat frame = cv_ptr->image;
  if (frame.empty()) {
    return;
  }

  if (!is_writer_init_) {
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    writer_.open(output_filename_, fourcc, fps_, frame.size(), true);

    if (!writer_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Could not open VideoWriter!");
      return;
    }
    is_writer_init_ = true;
    RCLCPP_INFO(
      this->get_logger(), "Recording started: %s (%dx%d)",
      output_filename_.c_str(), frame.cols, frame.rows);
  }

  writer_.write(frame);
  cv::imshow("Subscribed Video", frame);
  cv::waitKey(1);
}

void ImageSubscriber::watchdog_callback()
{
  if (is_writer_init_) {
    auto elapsed = std::chrono::steady_clock::now() - last_msg_time_;
    if (elapsed > 1000ms) {
      RCLCPP_INFO(this->get_logger(), "Stream ended. Saving and exiting...");
      watchdog_timer_->cancel();
      rclcpp::shutdown();
    }
  }
}