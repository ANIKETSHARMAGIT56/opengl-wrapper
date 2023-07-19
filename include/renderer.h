// #ifndef RENDERER
#pragma once


#include <vertexarray.h>
#include <shader.h>
#include <indexbuffer.h>

namespace GLwrap {


void GLFWErrorCallback(int, const char* err_str);

class Shader;
class Renderer{
public:
    void Clear();
    void Draw(VertexArray & va,IndexBuffer & ib, Shader &shader) ;

};
}
// #endif // !RENDERER