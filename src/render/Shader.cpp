#include "Shader.h"

#include <cstdio>

#include "../Platform.h"

namespace null {

bool CreateShader(GLenum type, const char* source, GLuint* shaderOut) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint success;
  GLchar info_log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
    platform.LogError("Shader error: %s", info_log);
    return false;
  }

  *shaderOut = shader;
  return true;
}

bool CreateProgram(GLuint vertexShader, GLuint fragmentShader, GLuint* programOut) {
  GLuint program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint success;
  GLchar info_log[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  if (!success) {
    glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
    platform.LogError("Program link error: %s", info_log);
    return false;
  }

  *programOut = program;
  return true;
}

bool ShaderProgram::Initialize(const char* vertex_code, const char* fragment_code) {
  GLuint vertex_shader, fragment_shader;

  if (!CreateShader(GL_VERTEX_SHADER, vertex_code, &vertex_shader)) {
    return false;
  }

  if (!CreateShader(GL_FRAGMENT_SHADER, fragment_code, &fragment_shader)) {
    glDeleteShader(vertex_shader);
    return false;
  }

  return CreateProgram(vertex_shader, fragment_shader, &program);
}

void ShaderProgram::Use() {
  glUseProgram(program);
}

void ShaderProgram::Cleanup() {
  if (program != -1) {
    glDeleteProgram(program);
    program = -1;
  }
}

}  // namespace null
