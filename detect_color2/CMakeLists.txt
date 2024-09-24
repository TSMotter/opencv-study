# Creates a binary target
add_executable(main detect_color2.cpp)
target_link_libraries(main ${OpenCV_LIBS})
