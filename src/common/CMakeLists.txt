# search cpp files in current directory
# aux_source_directory(. COMMON_SRCS)

set(COMMON_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/GridGraph.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/node.cpp"
)
# raise staric link lib
add_library(COMMON OBJECT "${COMMON_SRCS}")

# include responding .h file
target_include_directories(COMMON PUBLIC "${CMAKE_SOURCE_DIR}/include/boost/common")

# link to pch.h
target_link_libraries(COMMON PRIVATE PCH)