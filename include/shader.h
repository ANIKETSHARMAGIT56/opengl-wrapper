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
#define GL_VECTOR 1
#define GL_MATRIX 2
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
  void setuniform(std::string name ,glm::vec1 vec){
    int location = get_location(name); 
      GLDebug(glUniform1f(location,  vec[0]));
  }
  void setuniform(std::string name ,glm::mat4 vec){
    int location = get_location(name); 
    GLDebug(glUniformMatrix4fv(location, 1 ,GL_FALSE, glm::value_ptr(vec)));
  }
    void setuniform(std::string name ,int vec){
    int location = get_location(name); 
      GLDebug(glUniform1i(location,  vec));
  }
  // template<typename T>
  // void setuniform(std::string name ,T vec){
  //   int location = glGetUniformLocation(ShaderProgramID, name.c_str());
  //   if (location == -1) {
  //     std::cout << "cannot find location" << std::endl;
  //   }
  //   float * vecptr= (float *)glm::value_ptr(vec);
  //   if (typeid(T)==typeid(glm::vec4)){
  //     GLDebug(glUniform4f(location,  *vecptr,  *vecptr+1,  *vecptr+2, *vecptr+3));
  //   }
  //   else if (typeid(T)==typeid(glm::vec3)){
  //     GLDebug(glUniform3f(location,  *vecptr,  *vecptr+1,  *vecptr+2));
  //   }
  //   else if (typeid(T)==typeid(glm::vec2)){
  //     GLDebug(glUniform2f(location,  *vecptr,  *vecptr+1));
  //   }
  //   else if (typeid(T)==typeid(float)){

  //   }
  //   if (typeid(T) == typeid(glm::mat4)){
  //       GLDebug(glUniformMatrix4fv(location, 1 ,GL_FALSE,vecptr));
  //   }
  //   if (typeid(T) == typeid(glm::mat3)){
  //       GLDebug(glUniformMatrix3fv(location, 1 ,GL_FALSE,vecptr));
  //   }
  //   if (typeid(T) == typeid(glm::mat2)){
  //       GLDebug(glUniformMatrix2fv(location, 1 ,GL_FALSE,vecptr));
  //   }
  // }

  // void setuniform(std::string name ,float vec){
  //      int location = glGetUniformLocation(ShaderProgramID, name.c_str());
  //   if (location == -1) {
  //     std::cout << "cannot find location" << std::endl;
  //   }
  //     GLDebug(glUniform1f(location,  vec));
  // }  
  // void setuniform(std::string name ,int vec){
  //      int location = glGetUniformLocation(ShaderProgramID, name.c_str());
  //   if (location == -1) {
  //     std::cout << "cannot find location" << std::endl;
  //   }
  //     GLDebug(glUniform1i(location,  vec));
  // }
};
