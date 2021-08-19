cmake_minimum_required(VERSION 3.0.2)
project(prophesee_dev)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    cv_bridge
    std_msgs
    image_transport
    prophesee_event_msgs
)
find_package(OpenCV REQUIRED)
find_package(MetavisionSDK COMPONENTS driver REQUIRED)

catkin_package()

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

link_directories()

add_executable(receiver src/receiver.cpp)
target_link_libraries(receiver MetavisionSDK::driver ${catkin_LIBRARIES})