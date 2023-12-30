#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

typedef struct ShaderProgram {
    unsigned int m_programID;
} ShaderProgram;

char* GetShaderSource(const char* filepath);
unsigned int CompileShader(unsigned int type, char* src);
void CreateShader(ShaderProgram *sh, char* vShader, char* fShader);
void Bind(ShaderProgram *sh);
void Unbind();


#endif // SHADER_H