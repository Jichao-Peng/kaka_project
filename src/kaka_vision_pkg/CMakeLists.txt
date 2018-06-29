cmake_minimum_required(VERSION 2.8.3)
project(kaka_vision_pkg)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(cv_bridge_DIR /usr/local/share/cv_bridge/cmake)

find_package(catkin REQUIRED COMPONENTS
        pcl_conversions
        pcl_ros
        roscpp
        std_msgs
        sensor_msgs
        cv_bridge
        message_generation
        )

find_package(OpenCV REQUIRED)

find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
        FILES
        VisionMsg.msg
)

generate_messages(
        DEPENDENCIES
        std_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_vision_node src/KakaVision.cpp src/KakaVision.h src/KakaCloudMethod.cpp src/KakaCloudMethod.h src/KakaCloudTransform.cpp src/KakaCloudTransform.h src/KakaCoordinate.cpp src/KakaCoordinate.h)

target_link_libraries(kaka_vision_node ${catkin_LIBRARIES} ${OpenCV_LIBS})