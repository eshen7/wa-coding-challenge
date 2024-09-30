cmake_minimum_required(VERSION 3.22.1)

project(wa_coding_challenge)

add_executable(${PROJECT_NAME} main.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)