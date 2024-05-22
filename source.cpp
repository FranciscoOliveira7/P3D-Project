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

// Others

#include "shader.h"
#include "model.h"

#pragma endregion

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(std::vector<Model> &models);
void draw(std::vector<Model> &models);

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

    // Inicia o gestor de extens�es GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    //TODO Input Manager
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetCursorPosCallback(window, cursorCallBack);
    glfwSetMouseButtonCallback(window, mouseCallBack);

    std::vector<Model> models;
    Model goofy_table;
    Model ball;
    Model ball2;
    models.push_back(goofy_table);
    models.push_back(ball);

    init(models);

    while (!glfwWindowShouldClose(window)) {

        draw(models);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init(std::vector<Model> &models) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.25f, 1.0f);

    // Shaders type and locations
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "shaders/triangles.vert" },
        { GL_FRAGMENT_SHADER, "shaders/triangles.frag" },
        { GL_NONE, NULL }
    };

    // Shaders type and locations
    ShaderInfo shaders_ball[] = {
        { GL_VERTEX_SHADER,   "shaders/triangles_balls.vert" },
        { GL_FRAGMENT_SHADER, "shaders/triangles_balls.frag" },
        { GL_NONE, NULL }
    };

    Shader shader;
    Shader shader_balls;

    shader.Create(shaders);
    shader_balls.Create(shaders_ball);

    models[1].Load("PoolBalls\\Ball1.obj");
    models[2].Load("PoolBalls\\Ball2.obj");
    models[0].BindShader(shader);
    models[1].BindShader(shader_balls);

    // Load models to renderer
    for (int i = 0; i < models.size(); i++) {
        models[i].Install(i);
    }
}

void draw(std::vector<Model> &models) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw each object
    for (int i = 0; i < models.size(); i++) {

        models[i].SetCameraPosition(0.0f, 0.0f, zoom);
        models[i].Render(glm::vec3(0.0f, -5.0f + 1.5f * i, 2.0f * i), glm::vec3(0.0f, rotation, 0.0f));
    }
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}