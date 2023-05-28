#include <renderer.h>
#include <GL/glew.h>
#include <vertexbuffer.h>
VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLDebug(glGenBuffers(1, &m_RendererID));
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}
VertexBuffer::~VertexBuffer(){
    GLDebug(glDeleteBuffers(1,&m_RendererID));
}
void VertexBuffer::Bind() const
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
}
void VertexBuffer::UnBind() const
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER,0));
}