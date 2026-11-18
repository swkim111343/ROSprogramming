#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <string>
#include <chrono>

#if __has_include("cv_bridge/cv_bridge.hpp")
  #include "cv_bridge/cv_bridge.hpp"
#else
  #include "cv_bridge/cv_bridge.h"
#endif

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("imagesub");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));

    cv::VideoWriter writer;
    bool is_writer_init = false;
    std::string output_filename = "/home/seonwookim/simulation/output.mp4";
    double fps = 30.0;
    auto last_msg_time = std::chrono::steady_clock::now();

    auto callback = [&](const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
        last_msg_time = std::chrono::steady_clock::now();

        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        } catch (cv_bridge::Exception & e) {
            RCLCPP_ERROR(node->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        cv::Mat frame = cv_ptr->image;
        if (frame.empty()) {
            return;
        }

        if (!is_writer_init) {
            int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
            writer.open(output_filename, fourcc, fps, frame.size(), true);

            if (!writer.isOpened()) {
                RCLCPP_ERROR(node->get_logger(), "Could not open VideoWriter!");
                return;
            }
            is_writer_init = true;
            RCLCPP_INFO(node->get_logger(), "Recording started: %s (%dx%d)",
                        output_filename.c_str(), frame.cols, frame.rows);
        }

        writer.write(frame);
        cv::imshow("Subscribed Video", frame);
        cv::waitKey(1);
    };

    auto watchdog_timer = node->create_wall_timer(500ms, [&]() {
        if (is_writer_init) {
            auto elapsed = std::chrono::steady_clock::now() - last_msg_time;
            if (elapsed > 1000ms) {
                RCLCPP_INFO(node->get_logger(), "Stream ended. Saving and exiting...");
                rclcpp::shutdown();
            }
        }
    });

    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>(
        "image/compressed", qos_profile, callback);

    RCLCPP_INFO(node->get_logger(), "Waiting for video stream...");
    rclcpp::spin(node);

    if (writer.isOpened()) {
        writer.release();
        RCLCPP_INFO(node->get_logger(), "Saved video to %s", output_filename.c_str());
    }
    cv::destroyAllWindows();

    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
    return 0;
}