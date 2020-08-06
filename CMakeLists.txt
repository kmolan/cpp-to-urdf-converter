cmake_minimum_required(VERSION 3.15)
project(cpp_to_urdf)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)

include_directories(
        ${eigen_INCLUDE_DIRS}
)

add_executable(cpp_to_urdf run_conversion.cpp)
#target_link_libraries(cpp_to_urdf ${PROJECT_NAME} ${catkin_LIBRARIES})