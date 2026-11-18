#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "image_psub1_3/pub.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::string src = "/home/seonwookim/simulation/5_lt_cw_100rpm_out.mp4";
  auto node = std::make_shared<ImagePublisher>(src);

  if (rclcpp::ok()) {
    rclcpp::spin(node);
  }
  if (rclcpp::ok()) {
    rclcpp::shutdown();
  }
  return 0;
}