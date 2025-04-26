cmake_minimum_required(VERSION 3.10)
# project name
project(MyGoogleTest)

# 获取上一级目录
get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}" DIRECTORY)
# 再获取上上一级目录
get_filename_component(GRANDPARENT_DIR "${PARENT_DIR}" DIRECTORY)
include_directories(${PROJECT_SOURCE_DIR}/include)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置第三方库glog路径
set(CMAKE_PREFIX_PATH "${GRANDPARENT_DIR}/thirdparty/glog/install")

set(GLOG_ROOT "${GRANDPARENT_DIR}/thirdparty/glog/install")
include_directories(${GLOG_ROOT}/include)
find_package(glog CONFIG REQUIRED)

add_subdirectory(
	"${CMAKE_SOURCE_DIR}/src/algorithm/test"
	${CMAKE_BINARY_DIR}/test_target
)
enable_testing()

add_executable(MyGoogleTest google_test.cpp)
target_link_libraries(MyGoogleTest PRIVATE GTest::gtest_main HELLO_WORLD PCH glog::glog)

include(GoogleTest)
gtest_discover_tests(MyGoogleTest)
