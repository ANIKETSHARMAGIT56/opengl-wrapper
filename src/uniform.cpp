#include <shader.h>
#include <uniform.hpp>
#include <glm/vec4.hpp>
uniform::uniform(Shader & shad , std::string uniform_name){
    shader = shad;
    name = uniform_name;
}