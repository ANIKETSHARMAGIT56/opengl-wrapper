// #include "vertexarray.h"
#include <gldebug.h>
#include <GL/glew.h>
#include <iostream>
#include <csignal>
#include <shader.h>
#include <indexbuffer.h>
#include <renderer.h>
void GLClearErrors(){
    while (glGetError() != GL_NO_ERROR);
}
bool GLCheckError(){
    while (GLenum errorcode = glGetError())
    {
        std::cout<<"GL error: " << errorcode <<std::endl;
        return false;
    }
    return true;
    
}

void GLFWErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}
void GLwrap::Renderer::Draw(VertexArray &va ,IndexBuffer& ib, Shader & shader){
    va.Bind();
    ib.Bind();
    shader.Bind();
    GLDebug(glDrawElements(GL_TRIANGLES,ib.GetCount(),GL_UNSIGNED_INT,nullptr));
}
void GLwrap::Renderer::Clear(){
    GLDebug(glClear(GL_COLOR_BUFFER_BIT));
}