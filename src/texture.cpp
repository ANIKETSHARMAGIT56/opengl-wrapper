#include <cassert>
#include <cstddef>
#include <cstdio>
#include <texture.h>
#include <stb_image.h>
#include <renderer.h>
#include <GL/glew.h>
#include <iostream>
Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(1);
    auto m_texturebuffer = stbi_load(path.c_str(),&m_width,&m_height, &m_bits_per_pixel, 4);
    GLDebug(glGenTextures(1, &m_RendererID));
    GLDebug(glBindTexture(GL_TEXTURE_2D,m_RendererID));
    GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLDebug(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_texturebuffer));
    
    if(m_texturebuffer){
        stbi_image_free(m_texturebuffer);
    }
}

Texture::~Texture()
{
    GLDebug(glDeleteTextures(1,&m_RendererID));
}
void Texture::Bind(unsigned int slot)
{
    GLDebug(glBindTextureUnit(1,m_RendererID));
}