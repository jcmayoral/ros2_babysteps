cmake_minimum_required(VERSION 3.5)
project(bump_detector)

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
find_package(tf2_ros REQUIRED)

set (dependencies 
  std_msgs
  sensor_msgs
  geometry_msgs
  tf2_ros
)

include_directories(
  include/
)

add_library(${PROJECT_NAME} SHARED 
  src/${PROJECT_NAME}/obstacledetector.cpp
  #src/${PROJECT_NAME}/obstaclemonitor.cpp
  #src/${PROJECT_NAME}/obstacledetectorimproved.cpp
)
ament_target_dependencies(${PROJECT_NAME} rclcpp ${dependencies})

add_executable(detector src/detector_main.cpp)
ament_target_dependencies(detector rclcpp ${dependencies})
target_link_libraries(detector ${PROJECT_NAME} )


#add_executable(detector_improved src/detector_improved_main.cpp)
#ament_target_dependencies(detector_improved rclcpp ${dependencies})
#target_link_libraries(detector_improved ${PROJECT_NAME})

#ament_target_dependencies(${PROJECT_NAME}_node)

install(TARGETS
  ${PROJECT_NAME}
  detector
 # detector_improved
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
