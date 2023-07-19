#pragma once
// #include <renderer.h>
#include <GL/glew.h>
#include <csignal>
#include <gldebug.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <glm/gtc/type_ptr.hpp>


namespace GLwrap{

class Shader {

private:
  std::string VertexShaderCode;
  std::string FragmentShaderCode;

public:
  unsigned int ShaderProgramID;
  int LoadShader(unsigned int type, std::string filepath);
  unsigned int compileShader(unsigned int type);
  void CreateShader();
  void Bind();

  int get_location(std::string name){
    int location = glGetUniformLocation(ShaderProgramID, name.c_str());
    if (location == -1) {
      std::cout << "cannot find location of" <<name << std::endl;
    }
    return location;
  }
  void setuniform(std::string name ,glm::vec4 vec){
    int location = get_location(name); 
      GLDebug(glUniform4f(location,  vec[0],  vec[1], vec[2], vec[3]));
  }
  void setuniform(std::string name ,glm::vec3 vec){
    int location = get_location(name); 
      GLDebug(glUniform3f(location,  vec[0],  vec[1], vec[2]));
  }
  void setuniform(std::string name ,glm::vec2 vec){
    int location = get_location(name); 
    GLDebug(glUniform2f(location,  vec[0],  vec[1]));
  }
  void setuniform(std::string name ,float vec){
    int location = get_location(name); 
      GLDebug(glUniform1f(location,  vec));
  }
    void setuniform(std::string name ,int vec){
    int location = get_location(name); 
      GLDebug(glUniform1i(location,  vec));
  }
  void setuniform(std::string name ,glm::mat4 vec){
    int location = get_location(name); 
    GLDebug(glUniformMatrix4fv(location, 1 ,GL_FALSE, glm::value_ptr(vec)));
  }
    void setuniform(std::string name ,int size,int *vec){
    int location = get_location(name); 
      GLDebug(glUniform1iv(location,size,vec));
  }
  class uniform
  {
  public:
      Shader *shader; 
      std::string name;
      uniform(Shader & shad , std::string uniform_name);
      template<typename T>
      void operator=(const T & vec){
          shader->setuniform(name,vec);
      };
  };
};

}