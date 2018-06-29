cmake_minimum_required(VERSION 2.8.3)
project(kaka_test_pkg)

find_package(catkin REQUIRED COMPONENTS
        pcl_conversions
        pcl_ros
        roscpp
        std_msgs
        sensor_msgs
        cv_bridge
        )

find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_test_node src/KakaTest.cpp src/KakaTest.h)

target_link_libraries(kaka_test_node ${catkin_LIBRARIES})