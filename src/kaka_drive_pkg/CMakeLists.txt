cmake_minimum_required(VERSION 2.8.3)
project(kaka_drive_pkg)

find_package(catkin REQUIRED COMPONENTS
    actionlib
    control_msgs
    moveit_msgs
    roscpp
    rospy
    std_msgs
    std_srvs
    tf
    trajectory_msgs
    message_generation
    sensor_msgs
)
find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
    FILES
    JointMsg.msg
)

generate_messages(
    DEPENDENCIES
    std_msgs
    actionlib_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_drive_node src/KakaDrive.cpp src/KakaDrive.h)

target_link_libraries(kaka_drive_node ${catkin_LIBRARIES})
