#pragma once
#include <renderer.h>
#include <string>
class Texture{
private:
    unsigned int m_RendererID = 0;
    std::string m_filepath;
    unsigned char* m_texturebuffer;
    int m_width,m_height,m_bits_per_pixel;
public:
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int slot);
    void Unbind();
};