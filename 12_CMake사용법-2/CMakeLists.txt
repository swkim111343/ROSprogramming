# CMakeLists.txt
cmake_minimum_required(VERSION 3.16.3)
project(HelloCV)
find_package(OpenCV REQUIRED)
add_executable(HelloCV main.cpp)
target_include_directories(HelloCV PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(HelloCV PUBLIC ${OpenCV_LIBS})