cmake_minimum_required(VERSION 2.6)
#set(CMAKE_CXX_FLAGS "-std=gnu++11 -I${PROJECT_SOURCE_DIR} -pthread -lX11")
file(GLOB_RECURSE sources src/*.cpp src/main/*.h)
message(STATUS "SOURCES: " ${sources})
#include_directories(${PROJECT_SOURCE_DIR})
set(EXECUTABLE_NAME "ActDeckExe")

project(${EXECUTABLE_NAME})
#add_library(src_lib ${sources})
add_executable(${EXECUTABLE_NAME} ${sources})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=gnu++11)

#allow relative include
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR})


#SFML
set(SFML_STATIC_LIBS FALSE CACHE BOOL "Choose whether SFML is linked statically or shared.")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
include_directories(/usr/include)
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
 message(${SFML_INCLUDE_DIR})
 message(${SFML_LIBRARIES})
 include_directories(${SFML_INCLUDE_DIR})
 target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

if (SFML_STATIC_LIBS)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()


install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
