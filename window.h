#pragma once

#include "vertex.h"
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    inline bool should_close() { return glfwWindowShouldClose(window); }
    inline void swap_buffers() { glfwSwapBuffers(window); }
    inline Vec2i size() {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return {width, height};
    }
    inline int width() { return size().x; }
    inline int height() { return size().y; }
    void end_frame();

    GLFWwindow *window;
};
