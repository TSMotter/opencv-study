# Creates a binary target
add_executable(main simple_filter.cpp)
target_link_libraries(main ${OpenCV_LIBS})
