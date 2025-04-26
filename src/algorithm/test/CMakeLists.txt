# search cpp files in current directory
aux_source_directory(. HELLO_WORLD_SRCS)

# file(GLOB ASTAR_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/a_star.cpp")

# include responding .h file
# include_directories(${CMAKE_SOURCE_DIR}/include/boost/algorithm/test)

# raise staric link lib
add_library(HELLO_WORLD ${HELLO_WORLD_SRCS})
target_include_directories(HELLO_WORLD PUBLIC "${CMAKE_SOURCE_DIR}/include/boost/algorithm/test")

# link to pch.h
target_link_libraries(HELLO_WORLD PRIVATE PCH)