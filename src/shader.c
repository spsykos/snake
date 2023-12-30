#include "shader.h"

char* GetShaderSource(const char* fileName)
{
    FILE *fp;
    long size = 0;
    char* shaderContent;
    
    /* Read File to get size */
    fp = fopen(fileName, "rb");
    if(fp == NULL) {
        return "";
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fclose(fp);

    /* Read File for Content */
    fp = fopen(fileName, "r");
    shaderContent = memset(malloc(size), '\0', size);
    fread(shaderContent, 1, size-1, fp);
    fclose(fp);

    return shaderContent;
}

unsigned int CompileShader(unsigned int type, char* src) {
    const char* const* tmp = (const char* const*)&src;
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, tmp, NULL);
    glCompileShader(id);
    return id;
}

void CreateShader(ShaderProgram *sh, char* vertexShader, char* fragmentShader) {
    sh->m_programID = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(sh->m_programID, vs);
    glAttachShader(sh->m_programID, fs);
    glLinkProgram(sh->m_programID);
    glValidateProgram(sh->m_programID);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Bind(ShaderProgram *sh) {
    glUseProgram(sh->m_programID);
}

void Unbind() {
    glUseProgram(0);
}