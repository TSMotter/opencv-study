# Creates a binary target
add_executable(main histogram1.cpp)
target_link_libraries(main ${OpenCV_LIBS})
