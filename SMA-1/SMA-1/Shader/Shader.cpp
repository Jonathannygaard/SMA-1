//
// Created by jonat on 08/04/2024.
//
#include "Shader.h"
#include <sstream>
#include <fstream>
#include <glad/glad.h>

ShaderSource Shader::ReadShaderFromFile(const char *filepathVert, const char *filepathFrag) {
    ShaderSource currentSource;
    std::ifstream InFileVert(filepathVert);
    std::ifstream InFileFrag(filepathFrag);
    std::stringstream ssVert;
    std::stringstream ssFrag;
    if(InFileVert.is_open()&&InFileFrag.is_open())
    {
        ssVert << InFileVert.rdbuf();
        ssFrag << InFileFrag.rdbuf();
        currentSource.vertexSource = ssVert.str();
        currentSource.fragmentSource = ssFrag.str();
        return currentSource;
    }
    return {};
}

GLuint Shader::Program;

void Shader::CreateProgram() {
    ShaderSource source = ReadShaderFromFile("Core/Shader/VertexShader.vert", "Core/Shader/Fragmentshader.frag");
    Program = glCreateProgram();
    const char* VertexSource = source.vertexSource.c_str();
    const char* FragmentSource = source.fragmentSource.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &VertexSource, nullptr);
    glCompileShader(vs);
    glShaderSource(fs, 1, &FragmentSource, nullptr);
    glCompileShader(fs);
    glAttachShader(Program, vs);
    glAttachShader(Program, fs);
    glLinkProgram(Program);
    glDeleteShader(vs);
    glDeleteShader(fs);
}
