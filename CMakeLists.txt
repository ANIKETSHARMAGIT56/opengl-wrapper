#cmake
cmake_minimum_required(VERSION 3.15)
project(glfw_tut LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/renderer.cpp
                               src/vertexbuffer.cpp
                               src/indexbuffer.cpp
                               src/vertexarray.cpp
                               src/shader.cpp
                               src/stb_image.cpp
                               src/texture.cpp
                               src/uniform.cpp
                               )
                               
find_package(glm REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC "include/")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL GLEW glm)


