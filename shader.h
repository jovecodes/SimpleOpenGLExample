#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string>

class Shader {
public:
  Shader(const char *vert_code, const char *frag_code) {
    vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &vert_code, NULL);
    glCompileShader(vertex);

    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &frag_code, NULL);
    glCompileShader(fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
  }
  void deinit() {
    if (deinited)
      return;
    glDeleteProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    deinited = true;
  }

  ~Shader() { deinit(); }

  unsigned int vertex;
  unsigned int fragment;
  unsigned int program;
  bool deinited = false;
};
