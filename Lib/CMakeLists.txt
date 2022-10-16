file(GLOB SRC src/*.cpp)

add_library(${CMAKE_PROJECT_NAME}Lib STATIC ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME}Lib PUBLIC include)
