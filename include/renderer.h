// #ifndef RENDERER
#pragma once
// #define RENDERER
// #include "shader.h"
#include <csignal>
#include <vertexarray.h>
#include <shader.h>


void GLFWErrorCallback(int, const char* err_str);

#include <indexbuffer.h>
class Shader;
class Renderer{
public:
    void Clear();
    void Draw(VertexArray & va,IndexBuffer & ib, Shader &shader) ;

};
// #endif // !RENDERER