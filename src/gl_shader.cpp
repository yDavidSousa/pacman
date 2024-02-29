#include "include/gl_shader.h"

#include <GL/glew.h>

#include <iostream>

gl_shader::gl_shader()
{
    program_id = glCreateProgram();
}

gl_shader::~gl_shader()
{
    glDeleteProgram(program_id);
}

void gl_shader::create(const char *vertex_src, const char *fragment_src)
{
    int success;
    char infoLog[512];

    //Vertex Shader
    vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vertex_src, NULL);
    glCompileShader(vertex_id);

    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment Shader
    fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &fragment_src, NULL);
    glCompileShader(fragment_id);

    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void gl_shader::link()
{
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);

    int success;
    char infoLog[512];
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void gl_shader::bind()
{
    glUseProgram(program_id);
}

void gl_shader::set_uniform_mat4(const char *name, glm::mat4 value)
{
    unsigned int location = glGetUniformLocation(program_id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}