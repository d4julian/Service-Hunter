cmake_minimum_required(VERSION 3.25)
project(ServiceHunter)

set(CMAKE_CXX_STANDARD 17)

add_executable(ServiceHunter main.cpp MainWindow.cpp MainWindow.h)

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/ServiceHunter/SFML/include/SFML)
target_link_libraries(ServiceHunter sfml-system sfml-window sfml-graphics sfml-audio)
