#define GLEW_DLL
#define GLFW_DLL

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "GL/glew.h"
#include "GL/glfw3.h"
#include "Shader.h"


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "MainWindow", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    float points[] = {
        1.0f, 0.0f, 0.0f,
        0.5f, 0.866f, 0.0f,
        -0.5f, 0.866f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.866f, 0.0f,
        0.5f, -0.866f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    GLuint Vertex_shader[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 1,
        1, 2, 5
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex_shader), Vertex_shader, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        shader.use();
        shader.setUniform1f("timeValue", timeValue);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}