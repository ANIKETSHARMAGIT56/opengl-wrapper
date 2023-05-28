#pragma once
#include <renderer.h>
#include <vector>
#include <GL/glew.h>
struct VertexBufferParameters{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;
    // unsigned int stride;
    // const void* pointer;
};

class VertexBufferLayout{
    private:
    std::vector<VertexBufferParameters> m_parametersList;
    unsigned int m_Stride;

    public:
    VertexBufferLayout()
    :m_Stride(0){};
    void Push(unsigned int count){
        m_parametersList.push_back({GL_FLOAT,count,GL_FALSE});
        m_Stride+=sizeof(GLfloat)*count;
    }


    inline const std::vector<VertexBufferParameters> GetParamentersList () const {
        return m_parametersList;
    }
    inline unsigned int get_stride() const {
        return m_Stride;
    }

};