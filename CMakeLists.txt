cmake_minimum_required(VERSION 3.10)
project(ServiceHunter)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Use pkg-config to find libpqxx and libpq
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Specify include and library directories for libpq and libpqxx
if (APPLE)
    include_directories(${SFML_INCLUDE_DIR} ${PQXX_INCLUDE_DIRS} /usr/local/opt/libpq/include)
    link_directories(${PQXX_LIBRARY_DIRS} /usr/local/opt/libpq/lib)
elseif (WIN32)
    include_directories(${SFML_INCLUDE_DIR} ${PQXX_INCLUDE_DIRS} "C:/Program Files/PostgreSQL/pgxx/include")
    link_directories(${PQXX_LIBRARY_DIRS} "C:/Program Files/PostgreSQL/pgxx/lib")
elseif (UNIX)
    include_directories(${SFML_INCLUDE_DIR} ${PQXX_INCLUDE_DIRS} /usr/local/include)
    link_directories(${PQXX_LIBRARY_DIRS} /usr/local/lib)
endif()

# Add the executable
add_executable(ServiceHunter src/main.cpp src/MainWindow.cpp)

# Link SFML and libpqxx libraries
target_link_libraries(ServiceHunter sfml-graphics sfml-window sfml-system pqxx pq pthread)
