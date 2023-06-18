# minimal opengl wrapper for C++

## this is a minimal opengl wrapper for c++.

<br>

## just clone this repo in your project folder and add the following lines to your CMakeLists.txt


```cmake
add_subdirectory(opengl-wrapper/)
target_link_libraries(${PROJECT_NAME} glm imgui glwrap)
```
