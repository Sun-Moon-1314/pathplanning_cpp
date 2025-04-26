cmake_minimum_required(VERSION 3.10) # 确保版本支持 CMP0135  # cmake -G " Makefiles" ..

cmake_policy(SET CMP0135 NEW)
# 设置策略 CMP0079 为 NEW，允许跨目录链接
if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

project(PathPlanning)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加全局预编译头文件
set(BUILD_SHARED_LIBS OFF)
add_library(PCH STATIC ${CMAKE_SOURCE_DIR}/src/pch.cpp)
target_include_directories(PCH PUBLIC ${CMAKE_SOURCE_DIR}/include)
# 添加预编译头文件
target_precompile_headers(PCH PUBLIC ${CMAKE_SOURCE_DIR}/include/pch.h)
target_compile_definitions(PCH PRIVATE GLOG_NO_ABBREVIATED_SEVERITIES)

# 在CMake中全局定义
# add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES)


# 设置第三方库路径
set(THIRD_PARTY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(CMAKE_PREFIX_PATH "${THIRD_PARTY_ROOT}/glog/install")
set(GLOG_ROOT "${THIRD_PARTY_ROOT}/glog/install")
include_directories(${GLOG_ROOT}/include)
find_package(glog CONFIG REQUIRED)
# message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
# 拉取 GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/a866428a78ab02b7072f96c8de15802ffd451a7f.zip # Release 1.16.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

# 添加子目录
add_subdirectory(src/algorithm/a_star)
add_subdirectory(src/algorithm/dijkstra)
add_subdirectory(src/algorithm/floyd)
add_subdirectory(src/common)
add_subdirectory(src/utils)

add_subdirectory(
    tests/google_test
    ${CMAKE_BINARY_DIR}/tests/google_test
)
add_subdirectory(
    tests/a_star_test
    ${CMAKE_BINARY_DIR}/tests/a_star_test
)
# 定义一个 INTERFACE 库，用来聚合公共依赖
add_library(MyCommonLib INTERFACE)

# 添加所有公共依赖
target_link_libraries(MyCommonLib INTERFACE COMMON UTILS PCH glog::glog)

# 主程序入口
set(MAIN_SRCS ${CMAKE_SOURCE_DIR}/tests/test_main.cpp)
# 生成可执行文件
add_executable(PathPlanning ${MAIN_SRCS})
target_link_libraries(PathPlanning A_STAR DIJKSTRA FLOYD MyCommonLib)

# 复制 DLL (仅 Windows)
if(WIN32)
    add_custom_command(TARGET PathPlanning POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLOG_ROOT}/bin/glogd.dll"
            $<TARGET_FILE_DIR:PathPlanning>)
endif()