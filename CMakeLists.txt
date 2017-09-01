cmake_minimum_required(VERSION 2.6)
project(simple_ffd)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(simple_ffd_SRCS main.cpp)

qt4_automoc(${simple_ffd_SRCS})
add_executable(simple_ffd ${simple_ffd_SRCS})
target_link_libraries(simple_ffd ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS simple_ffd RUNTIME DESTINATION bin)
