#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SPEED 0.05;

void readKeyboard(GLFWwindow *window, float *x_direction, float *y_direction);

static char* GetShaderSource(const char* fileName)
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

static unsigned int CompileShader(unsigned int type, char* src) {
    const char* const* tmp = (const char* const*)&src;
    unsigned int id = glCreateShader(type);
    printf("created shader id: %d\n", id);
    glShaderSource(id, 1, tmp, NULL);
    glCompileShader(id);

    //glDeleteShader(id);
    return id;
}

static unsigned int CreateShader(char* vertexShader, char* fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int main()
{
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(720, 480, "test", NULL, NULL);
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

    unsigned int shader = CreateShader(vertexSrc, fragSrc);
    glUseProgram(shader);

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

        glUniform1f(glGetUniformLocation(shader, "x_dir"), x_dir);
        glUniform1f(glGetUniformLocation(shader, "y_dir"), y_dir);

        // draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);

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