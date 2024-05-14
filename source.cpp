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
#include "camera.h"
#include "model.h"

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

// Models
//Model models;
Model goofy_table;

// ------

Camera camera(20.0f, 45.0f);

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset == 1) camera.zoom_ -= fabs(camera.zoom_) * 0.1f;
    else if (yoffset == -1) camera.zoom_ += fabs(camera.zoom_) * 0.1f;
}

GLfloat rotation = 0.0f;
bool isPressing = false;
double prevXpos = 0.0;
double prevYpos = 0.0;
double xPos = 0.0;

float mouse_sensitivity = 3.0f;

void cursorCallBack(GLFWwindow* window, double xpos, double ypos) {
    xPos = xpos;
    if (isPressing) {
        double deltaX = xpos - prevXpos;
        rotation += static_cast<float>(deltaX) / WIDTH * mouse_sensitivity;
        prevXpos = xpos;
    }
}

void mouseCallBack(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isPressing = true;
            prevXpos = xPos;
        }
        else if (action == GLFW_RELEASE) isPressing = false;
    }
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

    //TODO Input Manager
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetCursorPosCallback(window, cursorCallBack);
    glfwSetMouseButtonCallback(window, mouseCallBack);

    Model goofy_table(3);

    init();

    glm::mat4 projection = camera.UpdateProjectionMatrix((float)(WIDTH / HEIGHT));

    while (!glfwWindowShouldClose(window)) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));
        model = glm::translate(model, glm::vec3(0, -2, 0));
        glm::mat4 view = camera.UpdateViewMatrix(glm::vec3(0, 0, camera.zoom_), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

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
        { 0.5f, 0.85f, 0.6f }, { 0.35f, 0.7f, 0.45f },
        { 0.3f, 0.6f, 0.4f }, { 0.4f, 0.8f, 0.5f },

        { 0.45f, 0.8f, 0.55f }, { 0.4f, 0.8f, 0.5f },
        { 0.4f, 0.8f, 0.5f }, { 0.2f, 0.4f, 0.3f },
    };

    GLuint indices[NumIndices] = {
        // Frente
        0, 1, 2, 1, 3, 2,
        // Direita
        1, 3, 7, 1, 5, 7,
        // Baixo
        2, 3, 6, 3, 6, 7,
        // Esquerda
        0, 2, 4, 2, 6, 4,
        // Trás
        4, 5, 6, 5, 7, 6,
        // Cima
        0, 4, 1, 4, 5, 1
    };

    goofy_table.InitializeComponents(3);

    goofy_table.BufferStorage(GL_ARRAY_BUFFER, 0, vertices, sizeof(vertices));
    goofy_table.BufferStorage(GL_ARRAY_BUFFER, 1, cores, sizeof(cores));
    goofy_table.BufferStorage(GL_ELEMENT_ARRAY_BUFFER, 2, indices, sizeof(indices));

    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "shaders/triangles.vert" },
        { GL_FRAGMENT_SHADER, "shaders/triangles.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders(shaders);
    if (!program) exit(EXIT_FAILURE);
    glUseProgram(program);

    //// Ligar os atributos aos shaders

    GLint coordsId = goofy_table.GetInputLocation(program, "vPosition");
    GLint coresId  = goofy_table.GetInputLocation(program, "vColors");

    goofy_table.AttribPointer(0, coordsId, 3);
    goofy_table.AttribPointer(1, coresId, 3);
}

void display(void) {
    goofy_table.Draw();
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}