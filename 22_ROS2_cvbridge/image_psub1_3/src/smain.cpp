#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "image_psub1_3/sub.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::string output_path = "/home/seonwookim/simulation/output.mp4";
  auto node = std::make_shared<ImageSubscriber>(output_path);

  rclcpp::spin(node);

  if (rclcpp::ok()) {
    rclcpp::shutdown();
  }
  return 0;
}