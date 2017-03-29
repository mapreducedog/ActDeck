cmake_minimum_required(VERSION 2.6)
project(actdeck)

add_executable(actdeck main.cpp)

install(TARGETS actdeck RUNTIME DESTINATION bin)
