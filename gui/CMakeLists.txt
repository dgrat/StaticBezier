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
find_package(Qt5 COMPONENTS OpenGL REQUIRED)

qt5_add_resources(RESSOURCES 
    shaders.qrc
    textures.qrc
)

set(ffd_src main.cpp App.cpp Renderer.cpp FFDGui.cpp GeometryEngine.cpp)

add_executable(ffd_gui ${ffd_src} ${RESSOURCES})
target_link_libraries(ffd_gui Qt5::Widgets Qt5::OpenGL)

install(TARGETS ffd_gui RUNTIME DESTINATION bin)
