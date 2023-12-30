#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBuffer.h"
#include "shader.h"

#define SPEED 0.05;

void readKeyboard(GLFWwindow *window, float *x_direction, float *y_direction);

int main()
{
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(720, 480, "window", NULL, NULL);
    if(!window) {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGL()) {
        exit(EXIT_FAILURE);
    }

    // vertices & indices
    float vertices[] = {
        -0.5, -0.5, // 0 -> bottom left
        -0.5, 0.5, // 1 -> top left
        0.5, 0.5, // 2 -> top right 
        0.5, -0.5 // 3 -> bottom right
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    char* vertexSrc = GetShaderSource("./resources/vertex.shader");
    char* fragSrc = GetShaderSource("./resources/fragment.shader");

    ShaderProgram sh;
    CreateShader(&sh, vertexSrc, fragSrc);
    Bind(&sh);

    unsigned int VAO, VBO, EBO;

    VertexBuffer vb;
    GenerateVBO(&vb.m_RendererID, vertices, sizeof(vertices));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);
    glEnableVertexAttribArray(0);

    float x_dir = 0.0f, y_dir = 0.0f;

        while(!glfwWindowShouldClose(window)) {
        glClearColor(0.9451, 0.9451, 0.9451, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        readKeyboard(window, &x_dir, &y_dir);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            printf("OpenGL error: %d\n", err);
            break;
        }

        glUniform1f(glGetUniformLocation(sh.m_programID, "x_dir"), x_dir);
        glUniform1f(glGetUniformLocation(sh.m_programID, "y_dir"), y_dir);

        // draw
        glBindVertexArray(vb.m_RendererID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(sh.m_programID);

    glfwTerminate();
    return 0;
}

void readKeyboard(GLFWwindow *window, float *x_direction, float *y_direction)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *y_direction += SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *y_direction -= SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        *x_direction -= SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        *x_direction += SPEED;
    }
}