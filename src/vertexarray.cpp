#include<renderer.h>
#include <vertexarray.h>
VertexArray::VertexArray(){
    GLDebug(glGenVertexArrays(1,&m_RendererID));
}
VertexArray::~VertexArray(){
    GLDebug(glDeleteVertexArrays(1,&m_RendererID));
}
void VertexArray::AddVertexBuffer(const VertexBuffer& vb,const VertexBufferLayout& Layout) const
{
    // vb.Bind();
    unsigned int offset=0;
    const auto& elements = Layout.GetParamentersList();


     GLDebug(glEnableVertexAttribArray(0));
    GLDebug(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0));

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        auto & element =elements[i];
    GLDebug(glEnableVertexAttribArray(i));
    GLDebug(glVertexAttribPointer(i, element.count, GL_FLOAT, (bool)element.normalized, Layout.get_stride(), (const void*)offset));
    offset+=element.count*sizeof(GLfloat);
    }

}
void VertexArray::Bind()const
{
    GLDebug(glBindVertexArray(m_RendererID));
    
}
void VertexArray::Unbind()const
{
    GLDebug(glBindVertexArray(0));
}
