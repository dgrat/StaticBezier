cmake_minimum_required(VERSION 3.1)
project(mesh_gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS 3DQuickExtras REQUIRED)

qt5_add_resources(QML_RES
    wireframe.qrc
)

set(MESH_SRC main.cpp)

add_executable(mesh_edit ${MESH_SRC} ${QML_RES})
qt5_use_modules(mesh_edit 3DQuickExtras)

install(TARGETS mesh_edit RUNTIME DESTINATION bin)
