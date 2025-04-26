# search cpp files in current directory
# aux_source_directory(. UTILS_SRCS)

set(UTILS_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp"
)
# raise staric link lib
add_library(UTILS STATIC ${UTILS_SRCS})
# include responding .h file
target_include_directories(UTILS PUBLIC ${CMAKE_SOURCE_DIR}/include/boost/utils)

# link to pch.h
target_link_libraries(UTILS PRIVATE PCH)