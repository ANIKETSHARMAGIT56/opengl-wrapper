#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <csignal>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

#include <glwrap.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>


// error handling for newer versions of openGL
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

int main(void) {
  // glfw init stuff
  GLFWwindow *window;
  glfwSetErrorCallback(GLFWErrorCallback);
  if (!glfwInit()) {
    std::cout << "glfw failed to initialize" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    std::cout << "failed to create window" << std::endl;
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  std::cout << "openGL version:" << glGetString(GL_VERSION) << std::endl;
  glfwSwapInterval(1);

  if (!(glewInit() == GLEW_OK)) {
    return -1;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  Renderer renderer;
  while (!glfwWindowShouldClose(window)) {


    renderer.Clear();
  {
  std::vector<float> positions{
      -10.5f, -10.5f, 0.0f, 0.0f, // 1
      10.5f,  -10.5f, 1.0f, 0.0f, // 2
      10.5f,  10.5f,  1.0f, 1.0f, // 3
      -10.5f, 10.5f,  0.0f, 1.0f  // 4
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  // initialise the vertex buffer
  VertexBuffer vertexbuffer(positions.data(), positions.size() * sizeof(float));
  vertexbuffer.Bind();

  // initialise the index buffer
  IndexBuffer indexbuffer(indices, 6);
  indexbuffer.Bind();

  // initialize the layout of vertex buffer
  VertexBufferLayout layout;
  layout.Push(2);
  layout.Push(2);

  // initialize the vertex array (takes vertex buffer and layout as parameters)
  VertexArray vertexarray;
  vertexarray.Bind();
  vertexarray.AddVertexBuffer(vertexbuffer, layout);

  // initialize the shader
  Shader shaderCode;
  shaderCode.LoadShader(GL_VERTEX_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.vert");
  shaderCode.LoadShader(GL_FRAGMENT_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.frag");
  shaderCode.CreateShader();
  shaderCode.Bind();

  glm::mat4 proj =
      glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 100, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj * view * model ;
  // initialize texture
  Texture texture("/home/aniket/code/opengl-wrapper/sample.jpg");
  texture.Bind(0);
  shaderCode.setuniform("u_texture", 0);
  shaderCode.setuniform("u_mvp",mvp);
  
  renderer.Draw(vertexarray, indexbuffer, shaderCode);
  }




    {
  std::vector<float> positions{
      -10.5f, -10.5f, 0.0f, 0.0f, // 1
      10.5f,  -10.5f, 1.0f, 0.0f, // 2
      10.5f,  10.5f,  1.0f, 1.0f, // 3
      -10.5f, 10.5f,  0.0f, 1.0f  // 4
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  // initialise the vertex buffer
  VertexBuffer vertexbuffer(positions.data(), positions.size() * sizeof(float));
  vertexbuffer.Bind();

  // initialise the index buffer
  IndexBuffer indexbuffer(indices, 6);
  indexbuffer.Bind();

  // initialize the layout of vertex buffer
  VertexBufferLayout layout;
  layout.Push(2);
  layout.Push(2);

  // initialize the vertex array (takes vertex buffer and layout as parameters)
  VertexArray vertexarray;
  vertexarray.Bind();
  vertexarray.AddVertexBuffer(vertexbuffer, layout);

  // initialize the shader
  Shader shaderCode;
  shaderCode.LoadShader(GL_VERTEX_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.vert");
  shaderCode.LoadShader(GL_FRAGMENT_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.frag");
  shaderCode.CreateShader();
  shaderCode.Bind();

  glm::mat4 proj =
      glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj * view * model ;
  // initialize texture
  Texture texture("/home/aniket/code/opengl-wrapper/sample.jpg");
  texture.Bind(0);
  shaderCode.setuniform("u_texture", 0);
  shaderCode.setuniform("u_mvp",mvp);
  
  renderer.Draw(vertexarray, indexbuffer, shaderCode);
  }


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}