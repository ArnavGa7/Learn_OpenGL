cmake_minimum_required(VERSION 3.20)

project(Learn_OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All project source files
add_executable(Learn_OpenGL
    Main.cpp
    Camera.cpp
    Cube.cpp
    EBO.cpp
    Mesh.cpp
    Model.cpp
    Object.cpp
    Plane.cpp
    ShaderClass.cpp
    Texture.cpp
    VAO.cpp
    VBO.cpp
    Window.cpp
    stb_image.cpp
    glad.c
)

# Header directories
target_include_directories(Learn_OpenGL PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Libarys/include"
)

# GLFW
find_package(glfw3 REQUIRED)

# Assimp
find_package(assimp REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(Learn_OpenGL PRIVATE
    glfw
    assimp::assimp
    OpenGL::GL
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)