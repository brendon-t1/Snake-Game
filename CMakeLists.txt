cmake_minimum_required(VERSION 3.7)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_definitions(-std=c++17)

#set(CXX_FLAGS "-Wall")


project(snake_game)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
