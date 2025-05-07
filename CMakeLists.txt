cmake_minimum_required(VERSION 3.25...3.31) # 确保版本支持 CMP0135  # cmake -G " Makefiles" ..
project(PathPlanning VERSION 0.1.0)

# 定义一个开关，决定是否启用调试日志
option(ENABLE_TEST_MAIN "Enable open test main" OFF)

# 版本号设置
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/Version.h"
)

# 生成配置头文件
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/Config.h"
)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加全局预编译头文件
add_library(PCH INTERFACE)
# 所有 link 到 PCH 的目标都能找到 pch.h
target_include_directories(PCH INTERFACE "${CMAKE_SOURCE_DIR}/include")
# 让所有 link 到 PCH 的目标都尝试用pch.h 作为预编译头
target_precompile_headers(PCH INTERFACE "${CMAKE_SOURCE_DIR}/include/pch.h")
# 为所有依赖PCH的目标添加防止与glog库的宏名冲突，例如LOG(INFO)
target_compile_definitions(PCH INTERFACE GLOG_NO_ABBREVIATED_SEVERITIES)

# 设置第三方库路径
set(THIRD_PARTY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(CMAKE_PREFIX_PATH "${THIRD_PARTY_ROOT}/glog/install")
set(GLOG_ROOT "${THIRD_PARTY_ROOT}/glog/install")
# target_include_directories()
# include_directories("${GLOG_ROOT}/include")
find_package(glog REQUIRED)
# 2. 如果启用，则查找 glog 库，并设置宏
if(ENABLE_TEST_MAIN)
    set(TEST_MAIN 1)
else()
    set(TEST_MAIN 0)
endif()

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
add_subdirectory("src/algorithm/a_star")
add_subdirectory("src/algorithm/dijkstra")
add_subdirectory("src/algorithm/floyd")
add_subdirectory("src/common")
add_subdirectory("src/utils")

add_subdirectory(
    "tests/google_test"
    "${CMAKE_BINARY_DIR}/tests/google_test"
)

add_subdirectory(
    "tests/a_star_test"
    "${CMAKE_BINARY_DIR}/tests/a_star_test"
    EXCLUDE_FROM_ALL
    SYSTEM
)
# 定义一个 INTERFACE 库，用来聚合公共依赖
add_library(MyCommonLib INTERFACE)

# 添加所有公共依赖
target_link_libraries(PCH INTERFACE glog::glog)
target_link_libraries(MyCommonLib INTERFACE PCH)

# 主程序入口
set(MAIN_SRCS "${CMAKE_SOURCE_DIR}/tests/test_main.cpp")
# 生成可执行文件
add_executable(PathPlanning ${MAIN_SRCS})
target_link_libraries(PathPlanning PRIVATE A_STAR DIJKSTRA FLOYD MyCommonLib ${CMAKE_CURRENT_BINARY_DIR})

# 复制 DLL (仅 Windows)
if(WIN32)
    add_custom_command(TARGET PathPlanning POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLOG_ROOT}/bin/glogd.dll"
            "$<TARGET_FILE_DIR:PathPlanning>")
endif()