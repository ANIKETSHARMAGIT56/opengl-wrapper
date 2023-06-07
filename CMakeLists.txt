#cmake
cmake_minimum_required(VERSION 3.15)
project(glwrap LANGUAGES CXX)
set(IMGUI_DIR ./imgui )

include_directories(include/
${IMGUI_DIR}/
${IMGUI_DIR}/backends/
)


# shared library
add_library(${PROJECT_NAME} SHARED 
src/renderer.cpp
src/vertexbuffer.cpp
src/indexbuffer.cpp
src/vertexarray.cpp
src/shader.cpp
src/stb_image.cpp
src/texture.cpp
)
find_package(glm REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC "include/")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GL GLEW glm)

add_library(imgui SHARED 
${IMGUI_DIR}/imgui.cpp 
${IMGUI_DIR}/imgui_demo.cpp 
${IMGUI_DIR}/imgui_draw.cpp 
${IMGUI_DIR}/imgui_tables.cpp 
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)





add_executable(single_render examples/single_render.cpp)
target_link_libraries(single_render PUBLIC glfw GL GLEW glm glwrap imgui)

add_executable(imgui_demo examples/imgui_demo.cpp)
target_link_libraries(imgui_demo PUBLIC glfw GL GLEW glm glwrap imgui)