#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <csignal>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <indexbuffer.h>
#include <iostream>
#include <renderer.h>
#include <shader.h>
#include <stdio.h>
#include <texture.h>
#include <vector>
#include <vertexarray.h>
#include <vertexbuffer.h>
#include <vertexbufferlayout.h>
#include <uniform.hpp>
void GLAPIENTRY

MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                GLsizei length, const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

int a_pressed = 0;
int d_pressed = 0;
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_A) {
      a_pressed = !a_pressed;
    }
    if (key == GLFW_KEY_D) {
      d_pressed = !d_pressed;
    }
  }

  if (action == GLFW_RELEASE) {
    if (key == GLFW_KEY_A) {
      a_pressed = !a_pressed;
    }
    if (key == GLFW_KEY_D) {
      d_pressed = !d_pressed;
    }
  }
}
int main(void) {
  GLFWwindow *window;
  glfwSetErrorCallback(GLFWErrorCallback);
  /* Initialize the library */
  if (!glfwInit()) {
    std::cout << "glfw failed to initialize" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // GLDebug(glGetString(GL_VERSION));
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
  glfwSetKeyCallback(window, key_callback);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

  if (!(glewInit() == GLEW_OK)) {
    return -1;
  }
  std::vector<float> positions{20.5f, -20.5f, 0.0f,  0.0f,
                        20.5f, -20.5f, 1.0f,   0.0f,
                        20.5f, 20.5f, 1.0f,  1.0f,
                        -20.5f, 20.5f,  0.0f,  1.0f};

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  GLDebug(glEnable(GL_BLEND));
  GLDebug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

      // initialise the vertex buffer
  VertexBuffer vertexbuffer(positions.data(),16*sizeof(float));
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

  double transformz = 0;

  glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj * view ;
  // initialize the shader
  Shader shaderCode;
  shaderCode.LoadShader(GL_VERTEX_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.vert");
  shaderCode.LoadShader(GL_FRAGMENT_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.frag");
  shaderCode.CreateShader();
  shaderCode.Bind();

  Texture texture("/home/aniket/code/opengl-wrapper/sample.jpg");
  texture.Bind(0);

  //initialize a uniform
  uniform u_Color(shaderCode,"u_Color");
  //set the uniform
  u_Color =  glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);


  shaderCode.setuniform("u_texture", 0);

  uniform u_mvp(shaderCode,"u_mvp");
  u_mvp = mvp;


  auto end = std::chrono::high_resolution_clock::now();

  Renderer renderer;


  glfwSwapInterval(1);
  {
  using namespace std::chrono;
  float delta_time;
  while (!glfwWindowShouldClose(window)) {
    auto start = std::chrono::high_resolution_clock::now();
    /* Render here */

    if (a_pressed) {
      transformz= transformz + (delta_time*100);
    }
    if (d_pressed) {
      transformz = transformz - (delta_time*100);
    }
  // printf("%f \n",transformz);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3((float)transformz, 0, 0));

    glm::mat4 mvp = proj * view;
    // u_mvp = mvp;
    // shaderCode.setuniform("u_mvp", mvp);

    // draw
    renderer.Draw(vertexarray, indexbuffer, shaderCode);


    glfwSwapBuffers(window);
    glfwPollEvents();

    end = std::chrono::high_resolution_clock::now();
    delta_time = duration_cast<microseconds>(end - start).count()/1e+6;

    renderer.Clear();
    // printf("\r fps : %f deltatime %f",1/delta_time, delta_time);
  }
  }

  glfwTerminate();
  return 0;
}