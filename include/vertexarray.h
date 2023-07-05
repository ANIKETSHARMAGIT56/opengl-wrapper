#pragma once
#include <vertexbuffer.h>
#include <vertexbufferlayout.h>
class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    void AddVertexBuffer(const glwrap::VertexBuffer& vb, const VertexBufferLayout& Layout) const;
    void Bind() const;
    void Unbind() const;
};