#pragma once 
class IndexBuffer{
    private:
    unsigned int m_RendererID;
    unsigned int m_Count;

    public:
    IndexBuffer(const unsigned int* size,unsigned int count);
    ~IndexBuffer();

    void Bind();
    void UnBind() ;
    inline unsigned int GetCount() const{
        return m_Count;
    }
};