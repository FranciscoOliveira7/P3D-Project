#pragma region includes

// Libraries

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

// Others

#include "shader_util.h"
#include "renderer.h"

#pragma endregion

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(void);
void display(void);

// Porgram
GLuint program;

// Models
Model goofy_table;

// Renderer
Renderer renderer;

// Camera
Camera camera;

// Projection
float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 100.0f;

float zoom = 10.0f;

// Table rotation behaviour

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

// Camera zoom behaviour

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset == 1) zoom -= fabs(zoom) * 0.1f;
    else if (yoffset == -1) zoom += fabs(zoom) * 0.1f;
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

    init();

    while (!glfwWindowShouldClose(window)) {

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init(void) {
    glEnable(GL_DEPTH_TEST);

    // Shaders type and locations
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "shaders/triangles.vert" },
        { GL_FRAGMENT_SHADER, "shaders/triangles.frag" },
        { GL_NONE, NULL }
    };

    // Compile and Load shaders to program (código feito pelo stor)
    program = LoadShaders(shaders);
    if (!program) exit(EXIT_FAILURE);
    glUseProgram(program);

    renderer.BindModel(&goofy_table);
    goofy_table.program_ = program;

    renderer.Install();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.SetCameraPosition(0.0f, 0.0f, zoom);

    renderer.Render(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, rotation, 0.0f));
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}