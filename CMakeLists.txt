cmake_minimum_required(VERSION 3.25) 

set(CMAKE_CXX_STANDARD 11)

project(Compress)

add_subdirectory(Lib)

file(GLOB SRC src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC Lib/include include/)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_PROJECT_NAME}Lib)
