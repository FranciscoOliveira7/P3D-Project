#pragma region includes

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>

#include <gl\GL.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "shader_util.h"

#pragma endregion

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(void);
void display(void);

#define NumBuffers 3 // Vértices, Cores, EBO

GLuint program;

GLuint VAO;
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 8; // 6 faces * 4 vértices
const GLuint NumIndices = 6 * 2 * 3; // 6 faces * 2 triângulos/face * 3 vértices/triângulo

GLfloat rotation = 0.0f;

GLfloat zoom = 20.0f;

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {

    if (yoffset == 1) zoom -= fabs(zoom) * 0.1f;
    else if (yoffset == -1) zoom += fabs(zoom) * 0.1f;

    std::cout << "Zoom = " << zoom << std::endl;
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(print_error);

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Bilhar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicia o gestor de extensões GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetScrollCallback(window, scrollCallBack);

    init();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, rotation += 0.005f, glm::vec3(0, 1, 0));
        model = glm::translate(model, glm::vec3(0, -2, 0));
        glm::mat4 view = lookAt(
            glm::vec3(0, 0, zoom),
            glm::vec3(0, 0, -1),
            glm::vec3(0, 1, 0)
        );

        glm::mat4 mvp = projection * view * model;

        GLint mpvId = glGetProgramResourceLocation(program, GL_UNIFORM, "MVP");
        glProgramUniformMatrix4fv(program, mpvId, 1, GL_FALSE, glm::value_ptr(mvp));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init(void) {
    glEnable(GL_DEPTH_TEST);

    // Mesa de Bilhar (fiz isto manualmente (not fun)) - Zes
    GLfloat vertices[NumVertices][3] = {
        {-9.0f,  0.5f,  5.5f }, { 9.0f,  0.5f,  5.5f },
        {-9.0f, -0.5f,  5.5f }, { 9.0f, -0.5f,  5.5f },

        {-9.0f,  0.5f, -5.5f }, { 9.0f,  0.5f, -5.5f },
        {-9.0f, -0.5f, -5.5f }, { 9.0f, -0.5f, -5.5f },
    };

    GLfloat cores[NumVertices][3] = {
        { 0.4f, 0.8f, 0.5f }, { 0.4f, 0.8f, 0.5f },
        { 0.4f, 0.8f, 0.5f }, { 0.4f, 0.8f, 0.5f },

        { 0.4f, 0.8f, 0.5f }, { 0.4f, 0.8f, 0.5f },
        { 0.4f, 0.8f, 0.5f }, { 0.4f, 0.8f, 0.5f },
    };

    GLuint indices[NumIndices] = {

        // Frente
        0, 1, 2, 1, 3, 2,
        // Direita
        1, 3, 7, 1, 5, 7,
        // Baixo
        2, 3, 6, 3, 6, 7,
        // Esquerda
        0, 2, 4, 2, 4, 6,
        // Trás
        4, 5, 6, 5, 6, 7,
        // Cima
        0, 1, 4, 1, 4, 5
    };

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBOs
    glGenBuffers(NumBuffers, Buffers);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices) /*2 * 6 * sizeof(float)*/, vertices, 0);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(cores) /*3 * 6 * sizeof(float)*/, cores, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[2]);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 0);


    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders(shaders);
    if (!program) exit(EXIT_FAILURE);
    glUseProgram(program);


    // Ligar os atributos aos shaders

    // Obtém a localização do atributo 'vPosition' no 'programa'.
    GLint coordsId = glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, "vPosition");
    GLint coresId = glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, "vColors");

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glVertexAttribPointer(coordsId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glVertexAttribPointer(coresId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(coordsId);
    glEnableVertexAttribArray(coresId);
}

void display(void) {
    //static const float black[] = {
    //    0.0f, 0.0f, 0.0f, 0.0f
    //};

    //glClearBufferfv(GL_COLOR, 0, black);

    // Vincula (torna ativo) o VAO
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, (void *)0);
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}