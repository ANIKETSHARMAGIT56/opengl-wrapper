#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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


#define path_to_texture_1 "/home/aniket/code/flappy-bird/assets/flappy-bird.png" //add path to texture
#define path_to_texture_2 "/home/aniket/code/flappy-bird/assets/background.jpg" //add path to texture


#ifndef path_to_texture_1 

#error "define path_to_texture_1 on line no. 22"

#endif // !path_to_texture_1


#ifndef path_to_texture_2 

#error "define path_to_texture_1 on line no. 23"

#endif // !path_to_texture_1


// error handling for newer versions of openGL
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

static float camerax=0.0f;
static float cameray=0.0f;
int main(void) {
  // glfw init stuff
  GLFWwindow *window;
  if (!glfwInit()) {
    std::cout << "glfw failed to initialize" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(400, 400, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    std::cout << "failed to create window" << std::endl;
    return -1;
  }
  // glfwSwapInterval(1);



  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  std::cout << "openGL version:" << glGetString(GL_VERSION) << std::endl;
  glfwSwapInterval(1);

  // imgui init
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char *glsl_version = "#version 130";
  ImGui_ImplOpenGL3_Init(glsl_version);

  if (!(glewInit() == GLEW_OK)) {
    return -1;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  float positions[] = {
      -10.5f, -10.5f, /**/ 0.0f, 0.0f, /**/ 0.0f, 0.0f ,1.0f ,1.0f, 0.0f,// 1
       10.5f, -10.5f, /**/ 1.0f, 0.0f, /**/ 1.0f, 0.0f ,0.0f ,1.0f, 0.0f,// 2
       10.5f,  10.5f, /**/ 1.0f, 1.0f, /**/ 0.0f, 1.0f ,1.0f ,1.0f, 0.0f,// 3
      -10.5f,  10.5f, /**/ 0.0f, 1.0f, /**/ 1.0f, 1.0f ,0.0f ,1.0f, 0.0f,// 4

       10.5f, -10.5f, /**/ 0.0f, 0.0f, /**/ 1.0f, 1.0f ,0.0f ,1.0f ,1.0f,// 1
       30.5f, -10.5f, /**/ 1.0f, 0.0f, /**/ 1.0f, 1.0f ,0.0f ,1.0f ,1.0f,// 2
       30.5f,  10.5f, /**/ 1.0f, 1.0f, /**/ 1.0f, 1.0f ,0.0f ,1.0f ,1.0f,// 3
       10.5f,  10.5f, /**/ 0.0f, 1.0f, /**/ 1.0f, 1.0f ,0.0f ,1.0f , 1.0f// 4
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0,
                            4 ,5 ,6 ,6, 7, 4};

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  // initialise the vertex buffer
  GLwrap::VertexBuffer vertexbuffer(positions, sizeof(positions) * sizeof(float));
  vertexbuffer.Bind();

  // initialise the index buffer
  GLwrap::IndexBuffer indexbuffer(indices, 12);
  indexbuffer.Bind();

  // initialize the layout of vertex buffer
  GLwrap::VertexBufferLayout layout;
  layout.Push(2);
  layout.Push(2);
  layout.Push(4);
  layout.Push(1);


  // initialize the vertex array (takes vertex buffer and layout as parameters)
  GLwrap::VertexArray vertexarray;
  vertexarray.Bind();
  vertexarray.AddVertexBuffer(vertexbuffer, layout);

  // initialize the shader
  GLwrap::Shader shaderCode;
  shaderCode.LoadShader(GL_VERTEX_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.vert");
  shaderCode.LoadShader(GL_FRAGMENT_SHADER,
                        "/home/aniket/code/opengl-wrapper/shaders/shader.frag");
  shaderCode.CreateShader();
  shaderCode.Bind();

  float transform_x = 0;
  float transform_y = 0;

  glm::mat4 proj;
  glm::mat4 view;
  glm::mat4 model;
  glm::vec3 model_translate(0.0f, 0.0f, 0.0f);
  glm::vec3 model2_translate(0.0f, 0.0f, 0.0f);

  proj = glm::perspective(glm::radians(90.0f), 1.0f, 0.0f, 1000.f);
  view = glm::translate(glm::mat4(1.0f), model_translate);
  model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  // initialize texture

  GLwrap::Shader::uniform u_mvp(shaderCode, "u_mvp");
  u_mvp = proj * view * model;
  
  int texturearray[]={1,2};
  shaderCode.setuniform("u_texture",2,&texturearray[0]);

  // initialize the renderer
  GLwrap::Renderer renderer;

  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /*
    bind everything (optional) the Renderer::Draw automatically binds vertex
    array , index buffer and shader
    */
    vertexarray.Bind();
    indexbuffer.Bind();
    shaderCode.Bind();

    // draw
      view = glm::translate(glm::mat4(1.0f), model_translate);
      u_mvp = proj * view * model;
      renderer.Draw(vertexarray, indexbuffer, shaderCode);


    {

      ImGui::Begin("debug window"); // Create a window called "Hello, world!"
                                    // and append into it.

      ImGui::Text("view transform"); // Display some text (you can use a format
                                     // strings too

      ImGui::SliderFloat3("transform x 1", &model_translate.x, -100.0f, 100.0f);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    renderer.Clear();
  }

  glfwTerminate();
  return 0;
}