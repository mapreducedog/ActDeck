cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "-std=gnu++11 -pthread -lX11")

set(EXECUTABLE_NAME "ActDeck")
project(${EXECUTABLE_NAME})
add_subdirectory(src)

add_executable(${EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${EXECUTABLE_NAME} cards_lib)





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
