cmake_minimum_required(VERSION 3.5)
project(bump_avoidance)

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

set (dependencies 
  std_msgs
  sensor_msgs
  geometry_msgs
)

include_directories(
  include/
)

add_library(${PROJECT_NAME} SHARED src/avoidance_node.cpp )
ament_target_dependencies(${PROJECT_NAME} rclcpp ${dependencies})

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
ament_target_dependencies(${PROJECT_NAME}_node rclcpp)
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME})

#ament_target_dependencies(${PROJECT_NAME}_node)

install(TARGETS
  ${PROJECT_NAME}_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch
 DESTINATION share/${PROJECT_NAME}
)
#install(TARGETS myStaticLib DESTINATION lib/myproject)
#install(TARGETS myPlugin DESTINATION lib)


ament_package()
