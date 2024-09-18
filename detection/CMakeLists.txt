# Creates a binary target
add_executable(main detection.cpp)
target_link_libraries(main ${OpenCV_LIBS})
