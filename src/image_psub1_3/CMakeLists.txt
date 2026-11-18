cmake_minimum_required(VERSION 3.8)
project(image_psub1_3)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(pub src/pmain.cpp src/pub.cpp)
ament_target_dependencies(pub rclcpp sensor_msgs cv_bridge OpenCV)

add_executable(sub src/smain.cpp src/sub.cpp)
ament_target_dependencies(sub rclcpp sensor_msgs cv_bridge OpenCV)

install(TARGETS
  pub
  sub
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()