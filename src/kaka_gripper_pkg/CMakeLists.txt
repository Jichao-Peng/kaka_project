cmake_minimum_required(VERSION 2.8.3)
project(kaka_gripper_pkg)


find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_gripper_node src/KakaGripper.cpp src/KakaGripper.h)

target_link_libraries(kaka_gripper_node ${catkin_LIBRARIES})
