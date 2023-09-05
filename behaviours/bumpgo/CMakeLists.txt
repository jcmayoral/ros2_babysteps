cmake_minimum_required(VERSION 3.5)
project(bumpgo)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set (dependencies 
  std_msgs
  sensor_msgs
  geometry_msgs
)

include_directories(
  include
)

add_library(${PROJECT_NAME} src/bumpgo.cpp)
add_executable(talker src/go_node.cpp)
ament_target_dependencies(talker rclcpp std_msgs ${dependencies})

install(TARGETS talker DESTINATION lib/${PROJECT_NAME})

ament_package()
