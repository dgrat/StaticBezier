cmake_minimum_required(VERSION 3.1)
project(simple_ffd)

#C++17 stuff
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(simple_ffd_SRCS main.cpp)

add_executable(simple_ffd ${simple_ffd_SRCS})
target_link_libraries(simple_ffd Qt5::Widgets)

install(TARGETS simple_ffd RUNTIME DESTINATION bin)
