# Creates a binary target
add_executable(main convert_grayscale.cpp)
target_link_libraries(main ${OpenCV_LIBS})
