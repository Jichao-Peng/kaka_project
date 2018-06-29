cmake_minimum_required(VERSION 2.8.3)
project(kaka_serial_pkg)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  serial
)

find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_dependencies(${catkin_EXPORTED_TARGETS})

add_executable(kaka_serial_node src/KakaSerial.cpp src/KakaSerial.h src/KakaProtocal.cpp src/KakaProtocal.h)

target_link_libraries(kaka_serial_node ${catkin_LIBRARIES})
