#include <fstream>
#include <renderer.h>
#include <iostream>
#include <shader.h>

std::string load_file(std::string filepath)
{
    std::string temp;
    std::string file_contents;
    std::ifstream File(filepath);
    while (getline(File, temp))
    {
        file_contents += temp + "\n";
    }
    return file_contents;
}

    int Shader::LoadShader(unsigned int type, std::string filepath)
    {
        switch (type)
        {
        case GL_VERTEX_SHADER:
            VertexShaderCode = load_file(filepath);
            break;
        case GL_FRAGMENT_SHADER:
            FragmentShaderCode = load_file(filepath);
            break;
        default:
            ASSERT((bool)0);
            std::cout << "failed to load shader : invalid filename" << std::endl;
            return -1;
        }
        return 0;
    }
    unsigned int Shader::compileShader(unsigned int type)
    {
        const char *src;
        if (type == GL_FRAGMENT_SHADER)
        {
            src = FragmentShaderCode.c_str();
        }
        else if (type == GL_VERTEX_SHADER)
        {
            src = VertexShaderCode.c_str();
        }
        else
        {
            return 0;
        }
        unsigned int id = glCreateShader(type);

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            if (type == GL_VERTEX_SHADER)
            {
                std::cout << "failed to compile vertex shader" << std::endl;
            }
            if (type == GL_FRAGMENT_SHADER)
            {
                std::cout << "failed to compile fragment shader" << std::endl;
            }
            std::cout << message << std::endl;

            return 0;
        }
        return id;
    }
    void Shader::CreateShader()
    {
        ShaderProgramID = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER);

        glAttachShader(ShaderProgramID, vs);
        glAttachShader(ShaderProgramID, fs);
        glLinkProgram(ShaderProgramID);
        glValidateProgram(ShaderProgramID);
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    void Shader::Bind(){
        GLDebug(glUseProgram(ShaderProgramID));
    }
