cmake_minimum_required(VERSION 3.20)

project(Learn_OpenGL LANGUAGES C CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libraries installed through Homebrew
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Collect C++ source files in the project root
file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Create executable
add_executable(Learn_OpenGL
    ${SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/glad.c"
)

# Include project and library headers
target_include_directories(Learn_OpenGL PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Libarys/include"
)

# Link libraries
target_link_libraries(Learn_OpenGL PRIVATE
    glfw
    glm::glm
    assimp::assimp
)

# macOS OpenGL configuration
find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)
target_link_libraries(Learn_OpenGL PRIVATE
    ${OPENGL_FRAMEWORK}
)

# Suppress OpenGL deprecation warnings on macOS
target_compile_definitions(Learn_OpenGL PRIVATE
    GL_SILENCE_DEPRECATION
)