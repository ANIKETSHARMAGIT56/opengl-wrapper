#pragma once
#include <vertexbuffer.h>
#include <vertexbufferlayout.h>
namespace GLwrap {

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& Layout) const;
    void Bind() const;
    void Unbind() const;
};
}