cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)

project(CustomButton LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(CustomButton
  main.cpp
  widget.cpp
  widget.h
  custombutton.cpp
  custombutton.h
)

target_link_libraries(CustomButton PRIVATE Qt5::Widgets)
