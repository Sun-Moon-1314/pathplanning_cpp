# search cpp files in current directory
# aux_source_directory(./a_star.cpp A_STAR_SRCS)

# 此文件位于 src/algorithm/a_star 目录下
# 确保目标 A_STAR 未被定义
set(A_STAR_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/a_star.cpp")
add_library(A_STAR STATIC "${A_STAR_SRCS}" $<TARGET_OBJECTS:COMMON> $<TARGET_OBJECTS:UTILS>)
target_include_directories(A_STAR PUBLIC "${CMAKE_SOURCE_DIR}/include/boost/algorithm/a_star")
# 链接到 PCH 库
target_link_libraries(A_STAR PRIVATE PCH glog::glog)