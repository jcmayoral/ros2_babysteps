cmake_minimum_required(VERSION 3.5)
project(action_tutorial)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
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
find_package(visualization_msgs REQUIRED)

find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/Fibonacci.action"
)

set (dependencies 
  std_msgs
  sensor_msgs
  geometry_msgs
  visualization_msgs
)

include_directories(
  include/
)

add_library(${PROJECT_NAME}_node SHARED
  src/action_node.cpp)

target_include_directories(${PROJECT_NAME}_node PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_definitions(${PROJECT_NAME}_node
  PRIVATE "ACTION_TUTORIALS_CPP_BUILDING_DLL")


add_dependencies(${PROJECT_NAME}_node ${PROJECT_NAME})

rosidl_target_interfaces(${PROJECT_NAME}_node
      ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_target_dependencies(${PROJECT_NAME}_node
  "rclcpp"
  "rclcpp_action"
  "rclcpp_components")

rclcpp_components_register_node(${PROJECT_NAME}_node PLUGIN "action_tutorials_cpp::FibonacciActionServer" EXECUTABLE fibonacci_action_server)

install(TARGETS
  ${PROJECT_NAME}_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)


ament_package()
