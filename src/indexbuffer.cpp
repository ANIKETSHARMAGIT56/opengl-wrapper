#include <indexbuffer.h>
#include <renderer.h>
#include <GL/glew.h>
IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count)
:m_Count(count)
{
    GLDebug(glGenBuffers(1, &m_RendererID));
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
}
IndexBuffer::~IndexBuffer(){
    GLDebug(glDeleteBuffers(1,&m_RendererID));
}
void IndexBuffer::Bind()
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
}
void IndexBuffer::UnBind()
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
