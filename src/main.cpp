#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgram.h"

using namespace std;

// Вершины треугольника
GLfloat points[] = {
    0.0f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

// Цвета для каждой вершины
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, // Красный
    0.0f, 1.0f, 0.0f, // Зелёный
    0.0f, 0.0f, 1.0f  // Синий
};

// Вершинный шейдер
const char* vertexShaderSource = R"(
#version 460 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
out vec3 color;
void main() {
    color = vertexColor;
    gl_Position = vec4(vertexPosition, 1.0);
}
)";

// Фрагментный шейдер
const char* fragmentShaderSource = R"(
#version 460 core
in vec3 color;
out vec4 fragColor;
void main() {
    fragColor = vec4(color, 1.0);
}
)";

int WindowWidth = 640;
int WindowHeight = 480;

// Обработка изменения размера окна
void windowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowWidth = width;
    WindowHeight = height;
    glViewport(0, 0, WindowWidth, WindowHeight);
}

// Обработка нажатий клавиш
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Battle Tanks", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    if (!gladLoadGL()) {
        cerr << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return -1;
    }

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "OpenGL version (parsed): " << major << "." << minor << endl;
    cout << "Press Escape to exit" << endl;

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Жёлтый фон

    // Создание шейдерной программы
    Renderer::ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);

    if (!shaderProgram.isComplete()) {
        cerr << "Failed to create shader program" << endl;
        glfwTerminate();
        return -1;
    }

    // Создание VAO и VBO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint pointsVbo;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint colorsVbo;
    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0); // Отвязать VAO

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Очистка ресурсов
    glDeleteBuffers(1, &pointsVbo);
    glDeleteBuffers(1, &colorsVbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

