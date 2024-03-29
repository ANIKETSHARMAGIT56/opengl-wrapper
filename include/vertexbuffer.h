#pragma once
namespace GLwrap{
class VertexBuffer{
    private:
    unsigned int m_RendererID;

    public:
    VertexBuffer(const void* data,unsigned int size);
    ~VertexBuffer();

    void Bind() const ;
    void UnBind() const;
    void Update(const void *data, unsigned int size) const;
    int GetID();
};

}