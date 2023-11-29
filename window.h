#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  Window(int width, int height, const std::string &title);
  ~Window();

  bool inline should_close() { return glfwWindowShouldClose(window); }

  GLFWwindow *window;
};
