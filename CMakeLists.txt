#cmake
cmake_minimum_required(VERSION 3.15)
project(glwrap LANGUAGES CXX)



# shared library
add_library(${PROJECT_NAME} SHARED 
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





add_executable(multi_renderer examples/multirender.cpp)
target_include_directories(multi_renderer PUBLIC "include/")
target_link_libraries(multi_renderer PUBLIC glfw GL GLEW glm glwrap)





