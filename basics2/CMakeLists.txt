cmake_minimum_required(VERSION 3.5)
project(basics2)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)


set(dependencies
  rclcpp
  std_msgs
)


add_executable(logger src/logger.cpp)
ament_target_dependencies(logger ${dependencies})

add_executable(logger_class src/logger_class.cpp)
ament_target_dependencies(logger_class ${dependencies})

add_executable(publisher_class src/publisher_class.cpp)
ament_target_dependencies(publisher_class ${dependencies})

add_executable(subscription_class src/subscription_class.cpp)
ament_target_dependencies(subscription_class ${dependencies})

add_executable(param_reader src/param_reader.cpp)
ament_target_dependencies(param_reader ${dependencies})

add_executable(executors src/executors.cpp)
ament_target_dependencies(executors ${dependencies})

install(TARGETS
  logger 
  logger_class
  publisher_class
  subscription_class
  param_reader
  executors

  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
 DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
