#include "gldebug.h"
#include <renderer.h>
#include <GL/glew.h>
#include <vertexbuffer.h>
GLwrap::VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLDebug(glGenBuffers(1, &m_RendererID));
    
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}
GLwrap::VertexBuffer::~VertexBuffer(){
    GLDebug(glDeleteBuffers(1,&m_RendererID));
}
void GLwrap::VertexBuffer::Bind() const
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
}
void GLwrap::VertexBuffer::UnBind() const
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER,0));
}
void GLwrap::VertexBuffer::Update(const void *data, unsigned int size) const{
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
} 
int GLwrap::VertexBuffer::GetID(){
    return m_RendererID;
}