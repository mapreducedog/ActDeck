cmake_minimum_required(VERSION 2.6)
set(EXECUTABLE_NAME "ActDeck")
add_subdirectory(src)
project(actdeck)

add_executable(actdeck /src/main.cpp)

install(TARGETS actdeck RUNTIME DESTINATION bin)
