cmake_minimum_required(VERSION 3.24)
project(cnova_xo C)

set(CMAKE_C_STANDARD 11)


add_executable(cnova_xo main.c)

target_link_libraries(cnova_xo PUBLIC
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        winMM.Lib)
