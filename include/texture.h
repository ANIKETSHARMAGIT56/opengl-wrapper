#pragma once
#include <renderer.h>
#include <string>


namespace GLwrap {

class Texture{
private:
    std::string m_filepath;
    unsigned char* m_texturebuffer;
public:
    int m_width,m_height,m_bits_per_pixel;
    unsigned int m_RendererID = 0;
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int slot);
};
}