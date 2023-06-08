#pragma once
#include <shader.h>
#include <glm/fwd.hpp>

class uniform
{
public:
    Shader shader; 
    std::string name;
    uniform(Shader & shad , std::string uniform_name);
    template<typename T>
    void operator=(const T & vec){
        shader.setuniform(name,vec);
    };
};

