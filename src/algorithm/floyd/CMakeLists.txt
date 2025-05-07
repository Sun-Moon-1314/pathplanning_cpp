# search cpp files in current directory
aux_source_directory(. FLOYD_SRCS)

# file(GLOB ASTAR_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/a_star.cpp")

# include responding .h file
include_directories("${CMAKE_SOURCE_DIR}/include/boost/algorithm/floyd")

# raise staric link lib
add_library(FLOYD "${FLOYD_SRCS}")
# link to pch.h
target_link_libraries(FLOYD PRIVATE PCH)