cmake_minimum_required(VERSION 3.6.3 FATAL_ERROR)
project(DataSetBagRecord)

set(CMAKE_CXX_STANDARD 11)
set( CMAKE_EXPORT_COMPILE_COMMANDS on)
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
#Yaml
find_package( yaml-cpp REQUIRED )
include_directories(${YAML_CPP_SOURCE_DIR}/src)
include_directories(${YAML_CPP_SOURCE_DIR}/test)
#pcl
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARIES_DIRS})
#找到ros库
find_package(roscpp REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS})

find_package(sensor_msgs REQUIRED)
include_directories(${sensor_msgs_INCLUDE_DIRS})

find_package(rosbag REQUIRED)
include_directories(${rosbag_INCLUDE_DIRS})

find_package(std_msgs REQUIRED)
include_directories(${std_msgs_INCLUDE_DIRS})

find_package(nav_msgs REQUIRED)
include_directories(${nav_msgs_INCLUDE_DIRS})

find_package(geometry_msgs REQUIRED)
include_directories(${geometry_msgs_INCLUDE_DIRS})
find_package(tf_conversions REQUIRED)
include_directories(${tf_conversions_INCLUDE_DIRS})

find_package(cv_bridge REQUIRED)
include_directories(${cv_bridge_INCLUDE_DIRS})
include_directories( src include ${libpointmatcher_INCLUDE_DIRS})
#pose graph 相关的库
FIND_PACKAGE( CSparse )
find_package( G2O REQUIRED )
find_package( Eigen3  REQUIRED)
find_package( Cholmod REQUIRED )
find_package(OpenCV REQUIRED)
include_directories( ${G2O_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR})
#sophus
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS}
        ${CSPARSE_INCLUDE_DIR}
        include
        )
ADD_LIBRARY(Sophus SHARED include/sophus/se3.cpp
        include/sophus/so3.cpp
        include/sophus/so3.h
        include/sophus/se3.h)
#g2o
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})

ADD_LIBRARY(poseIO SHARED include/g2oIO/PoseGraphIO.h include/g2oIO/PoseGraphIO.cpp)
target_link_libraries(poseIO g2o_core g2o_stuff g2o_types_slam3d ${CHOLMOD_LIBRARIES})

add_library(readbag
        include/GPS/gpsTools.cpp include/GPS/gpsTools.h
        include/DataIO/ReadBag.cpp include/DataIO/ReadBag.h
        include/tools/util.cpp
        include/tools/util.h
        include/CSV/CSVio.cpp
        include/CSV/CSVio.h)

target_link_libraries(readbag
        poseIO
        ${roscpp_LIBRARIES} ${std_msgs_LIBRARIES}
        ${rosbag_LIBRARIES} ${nav_msgs_LIBRARIES}
        ${geometry_msgs_LIBRARIES} ${sensor_msgs_LIBRARIES}
        yaml-cpp ${PCL_LIBRARIES}         ${tf_conversions_LIBRARIES}
        ${cv_bridge_LIBRARIES} Sophus g2o_core g2o_stuff g2o_types_slam3d ${CHOLMOD_LIBRARIES})

add_executable(DataSetBagRecord main.cpp)
target_link_libraries(DataSetBagRecord
        readbag
        yaml-cpp
        ${roscpp_LIBRARIES})