# Creates a binary target
add_executable(main detect_color1.cpp)
target_link_libraries(main ${OpenCV_LIBS})
