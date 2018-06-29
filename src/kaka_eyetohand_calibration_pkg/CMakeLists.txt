cmake_minimum_required(VERSION 2.8.3)
project(kaka_eyetohand_calibration_pkg)

set(cv_bridge_DIR /usr/local/share/cv_bridge/cmake)

find_package(catkin REQUIRED COMPONENTS
        pcl_conversions
        pcl_ros
        roscpp
        sensor_msgs
        cv_bridge
        image_transport
        moveit_ros_planning_interface
        )

find_package(OpenCV REQUIRED)

find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_eyetohand_calibration_node src/KakaCalibration.cpp src/KakaCalibration.h src/KakaCalibMethod.cpp src/KakaCalibMethod.h)

target_link_libraries(kaka_eyetohand_calibration_node ${catkin_LIBRARIES} ${OpenCV_LIBS})
