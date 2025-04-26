cmake_minimum_required(VERSION 3.10)  # cmake -G " Makefiles" ..
# project name
project(AStarTest)

# 获取上一级目录
get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}" DIRECTORY)
# 再获取上上一级目录
get_filename_component(GRANDPARENT_DIR "${PARENT_DIR}" DIRECTORY)
# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置第三方库glog路径
set(CMAKE_PREFIX_PATH "${GRANDPARENT_DIR}/thirdparty/glog/install")

set(GLOG_ROOT "${GRANDPARENT_DIR}/thirdparty/glog/install")
include_directories(${GLOG_ROOT}/include)
# link_directories(${GLOG_ROOT}/lib)
find_package(glog CONFIG REQUIRED)

enable_testing()

# 添加测试子目录（假设测试代码在子目录中)

add_executable(AStarTest a_star_test.cpp)
target_link_libraries(AStarTest PRIVATE GTest::gtest_main A_STAR MyCommonLib)
# 自动拷贝 glogd.dll
add_custom_command(TARGET AStarTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/thirdparty/glog/install/bin/glogd.dll"
        $<TARGET_FILE_DIR:AStarTest>)

include(GoogleTest)
gtest_discover_tests(AStarTest)
