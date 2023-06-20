cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE "Release")
set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(hikrobot_infrared_camera)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  camera_info_manager
)

catkin_package()

include_directories(${OpenCV_INCLUDE_DIRS} 
  ${catkin_INCLUDE_DIRS} 
  "${PROJ_DIR}/include" 
  "/usr/include/X11" 
  "/usr/include")

link_directories("${PROJ_DIR}/lib/64")
link_libraries("${PROJ_DIR}/lib/64/libMvCameraControl.so")
add_compile_options(-std=c++11)


add_executable(infrared src/main.cpp)
add_library(camera_class SHARED src/camera_class.cpp)


target_link_libraries(infrared ${OpenCV_LIBS} 
   -lX11
   libMvCameraControl.so
   camera_class
   ${catkin_LIBRARIES})
