cmake_minimum_required(VERSION 2.8.3)
project(kaka_brain_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)
find_package(catkin REQUIRED COMPONENTS moveit_ros_planning_interface)
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#find_package(Eigen3 REQUIRED)

find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_brain_node src/KakaBrain.cpp src/KakaBrain.h)

target_link_libraries(kaka_brain_node ${catkin_LIBRARIES})